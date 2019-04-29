//---------------------------------------------------------------
// プレイヤーコントロールクラス
//---------------------------------------------------------------
#include "PlayerControll.h"
#include "InputInfo.h"
#include "Sound.h"
#include <math.h>

//---------------------
// コンストラクタ
//---------------------
PlayerControll::PlayerControll()
{
	// ３Ｄモデルの読み込み
	m_modelHandle = MV1LoadModel("data/model/slime.mqo");

	m_pos = VGet(0, 0, 0);
	m_velocity = VGet(0, 0, 0);
	m_scale = VGet(0, 0, 0);
	m_floorPos = VGet(0, 0, 0);
	m_prevPos = VGet(0, 0, 0);
	m_shotVec = VGet(0, 0, 0);
}

//---------------------
// デストラクタ
//---------------------
PlayerControll::~PlayerControll()
{
	// モデルのアンロード.
	MV1DeleteModel(m_modelHandle);
}

//---------------------
// 初期化
//---------------------
void PlayerControll::Init()
{
	// 各変数初期化
	m_pos = VGet(0.f, -150.f, 120.f);
	m_velocity = VGet(0.f, 0.f, 0.f);
	m_scale = VGet(1.f, 1.f, 1.f);
	m_prevPos = VGet(0, 0, 0);
	m_shotVec = VGet(0, 0, 0);
	m_returnVec = VGet(0, 0, 0);

	m_angleY = 0.f;
	m_moveSpeed = 3.5f;
	m_grabity = 0.3f;
	m_jumpAccel = 4.f;
	m_radius = 12.f;

	m_isCanMove = false;
	m_isGround = false;
	m_isMove = false;
	m_isJump = false;
	m_isShot = false;
	m_isReturn = false;

	m_moveCnt = 0;
}

//---------------------
// 更新
//---------------------
void PlayerControll::Update()
{
	// 着地
	CheckGround();

	if (m_isCanMove)
	{
		// 移動
		MovePlayer();
	}
}

//---------------------
// 描画
//---------------------
void PlayerControll::Draw()
{
	// ３Ｄモデルのポジション設定
	MV1SetPosition(m_modelHandle, m_pos);

	// ３Ｄモデルの回転角設定
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, m_angleY / 180.0f * DX_PI_F, 0.0f));

	// ３Ｄモデルの拡大率設定
	MV1SetScale(m_modelHandle, VGet(m_scale.x, m_scale.y, m_scale.z));

	// ３Ｄモデルの描画
	MV1DrawModel(m_modelHandle);

}

//---------------------
// 関数群
//---------------------

// 移動管理処理
void PlayerControll::MovePlayer()
{
	// ショットフラグがtrueならショット処理
	if (m_isShot)
	{
		Shot();
	}
	else
	{
		// スティックや十字キーの入力があったら処理に入る
		if (GetJoyAxis().x != 0 || GetJoyAxis().y != 0)
		{
			m_isMove = true;
			m_moveCnt++;

			// 移動ベクトルを更新
			UpdateVelocity();

			// 回転角を計算
			CalculateAngleY(GetJoyAxis().x, -GetJoyAxis().y);

			// ポジションに移動ベクトルを加算
			m_pos = VAdd(m_pos, m_velocity);
		}
		// 入力がない場合は向きを固定する
		else
		{
			m_isMove = false;
			m_moveCnt = 0;

			// 向き固定処理
			FixedDirection();
		}

		// 拡大率更新
		CangeScale();

		// 当たり判定処理
		DetectionCollision();
	}

	// ショットできる状態でショットボタンが押されたら撃つ
	const bool isCanShot = !m_isMove && !m_isJump && !m_isShot;
	if (isCanShot && GetInput(SHOT) == PUSHDOWN)
	{
		m_isShot = true;
		m_prevPos = m_pos;
		playSound(SE_SHOT);
	}

	// 移動カウンタが２０を超えたらジャンプする
	if (m_moveCnt > 15 && !m_isJump)
	{
		m_isJump = true;
		m_jumpVec = m_jumpAccel;
		playSound(SE_JUMP);
	}

	// ジャンプ（移動中オートジャンプ）
	if (m_isJump)
	{
		Jump();
	}
}

// 着地処理
void PlayerControll::CheckGround()
{

	if (m_pos.y < m_floorPos.y)
	{
		m_pos.y = m_floorPos.y;
		m_isJump = false;
		m_isGround = true;
	}
	else if (m_isJump)
	{
		m_isGround = false;
	}
}

// 移動ベクトル更新処理
void PlayerControll::UpdateVelocity()
{
	m_velocity.x = GetJoyAxis().x;
	m_velocity.z = GetJoyAxis().y;

	m_velocity = VNorm(m_velocity);

	m_shotVec = VScale(m_velocity, 3.f);
	m_velocity = VScale(m_velocity, m_moveSpeed);
}

// 回転角計算処理
void PlayerControll::CalculateAngleY(float x, float y)
{
	VECTOR v = VGet(0, 0, 0);
	m_angleY = 0.f;
	v.x = x;
	v.z = y;
	v = VNorm(v);

	m_angleY = (float)atan2((double)v.z, (double)v.x) * 180.f / DX_PI_F;
	m_angleY -= 90.f;
}

// 向き固定処理
void PlayerControll::FixedDirection()
{
	// 現在位置に応じて向きを固定する
	const bool inBack = m_pos.x > -105 && m_pos.x < 105 && m_pos.z < 0;	// 手前にいる
	const bool inFront = m_pos.x > -105 && m_pos.x < 105 && m_pos.z > 0;// 奥にいる
	const bool inLeft = m_pos.z > -105 && m_pos.z < 105 && m_pos.x < 0; // 左にいる
	const bool inRight = m_pos.z > -105 && m_pos.z < 105 && m_pos.x > 0;// 右にいる
	if (inFront)
	{
		// 手前を向かせて、ショットベクトルを手前向きにする
		m_angleY = 0.0f;
		m_shotVec = VGet(0, 0, -3);
	}
	if (inBack)
	{
		// 奥を向かせて、ショットベクトルを奥向きにする
		m_angleY = 180.0f;
		m_shotVec = VGet(0, 0, 3);
	}
	if (inLeft)
	{
		// 右を向かせて、ショットベクトルを右向きにする
		m_angleY = -90.0f;
		m_shotVec = VGet(3, 0, 0);
	}
	if (inRight)
	{
		// 左を向かせて、ショットベクトルを左向きにする
		m_angleY = 90.0f;
		m_shotVec = VGet(-3, 0, 0);
	}
}

// ジャンプ処理
void PlayerControll::Jump()
{
	m_pos.y += m_jumpVec;
	m_jumpVec -= m_grabity;
}

// スケールを変更してぷよぷよさせる処理
void PlayerControll::CangeScale()
{
	// 非移動時には元の大きさに戻す
	if (!m_isMove && !m_isJump)
	{
		if (m_scale.x != 1.f)
		{
			m_scale.x = 1.f;
			m_scale.y = 1.f;
			m_scale.z = 1.f;
		}
	}

	// 移動時、ジャンプするまで縮める
	if (m_isMove && !m_isJump)
	{
		m_scale.x += 0.01f;
		m_scale.y -= 0.01f;
		m_scale.z += 0.01f;
	}

	// ジャンプ時
	if (m_isJump)
	{
		// 着地直前に全力で潰す
		if (m_jumpVec < 0 && m_pos.y < m_floorPos.y + 5)
		{
			m_scale.x += 0.2f;
			m_scale.y -= 0.2f;
			m_scale.z += 0.2f;
		}
		// 浮いている間、少しずつ元に戻す
		else if (m_scale.y < 1.f)
		{
			m_scale.x -= 0.1f;
			m_scale.y += 0.1f;
			m_scale.z -= 0.1f;
		}
	}
}

// ショット処理
void PlayerControll::Shot()
{
	// 元の位置から現在位置の距離を取得
	float length = pow((m_pos.x - m_prevPos.x) * (m_pos.x - m_prevPos.x) +
					   (m_pos.y - m_prevPos.y) * (m_pos.y - m_prevPos.y) +
					   (m_pos.z - m_prevPos.z) * (m_pos.z - m_prevPos.z), 0.5);

	if (!m_isReturn && length >= 12.f)
	{
		m_isReturn = true;
		// 戻り用ベクトルにショットベクトルの反対方向のベクトルを入れる
		m_returnVec = VScale(m_shotVec, -1);
	}

	// 距離が0.1より小さくなったら
	if (m_isReturn && length == 0.f)
	{
		m_isShot = false;
		m_isReturn = false;
		m_prevPos = VGet(0, 0, 0);
		m_returnVec = VGet(0, 0, 0);
	}

	if (m_isShot && !m_isReturn)
	{
		m_pos = VAdd(m_pos, m_shotVec);
	}
	else
	{
		m_pos = VAdd(m_pos, m_returnVec);
	}
}

// 当たり判定
void PlayerControll::DetectionCollision()
{
	// マス目の中に入らないようにする判定
	if (m_pos.x - m_radius < 105 && m_pos.x + m_radius > -105)
	{
		if (m_pos.z + m_radius > -110 && m_pos.z < 105)
			m_pos.z = -110 - m_radius;
		if (m_pos.z - m_radius < 110 && m_pos.z > -105)
			m_pos.z = 110 + m_radius;
	}
	if (m_pos.z - m_radius < 105 && m_pos.z + m_radius > -105)
	{
		if (m_pos.x + m_radius > -110 && m_pos.x < 105)
			m_pos.x = -110 - m_radius;
		if (m_pos.x - m_radius < 110 && m_pos.x > -105)
			m_pos.x = 110 + m_radius;
	}

	// 足場から落ちないようにする判定
	if (m_pos.x - m_radius < -135)
		m_pos.x = -135 + m_radius;
	if (m_pos.x + m_radius > 135)
		m_pos.x = 135 - m_radius;
	if (m_pos.z - m_radius < -135)
		m_pos.z = -135 + m_radius;
	if (m_pos.z + m_radius > 135)
		m_pos.z = 135 - m_radius;
}
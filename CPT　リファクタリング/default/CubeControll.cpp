//---------------------------------------------------------------
// キューブコントロールクラス
//---------------------------------------------------------------
#include "CubeControll.h"
#include "InputInfo.h"
#include "Sound.h"

//---------------------
// コンストラクタ
//---------------------
CubeControll::CubeControll()
{
	// ３Ｄモデルの読み込み
	m_modelHandle = MV1LoadModel("data/model/cube.mqo");

	SetBordInfo();
}

//---------------------
// デストラクタ
//---------------------
CubeControll::~CubeControll()
{
	// モデルのアンロード.
	MV1DeleteModel(m_modelHandle);
}

//---------------------
// 初期化
//---------------------
void CubeControll::Init()
{
	// 各変数初期化
	for (int i = 0; i < 9; i++)
	{
		// キューブを所定の位置に設定
		m_pos[i] = m_squaresPos[m_nextPosNum[i]];
		m_isSlide[i] = false;
		m_isFit[i] = false;
		m_isHit[i] = false;
	}

	m_playerPos = VGet(0, 0, 0);

	m_moveSpeed = 3.f;
	m_radius = 15.f;
	m_range = 20.f;

	m_nowStageNum = 1;
	m_slideDirection = 0;
	m_waitCnt = 0;

	m_isMove = false;
	m_isAllFit = false;
	m_isSupport = false;
	m_isReset = false;
	m_isClear = false;
}

//---------------------
// 更新
//---------------------
void CubeControll::Update()
{	
	int cnt = 0;
	for (int i = 0; i < 9; i++)
	{
		// 移動
		MoveCube(i);

		// 赤い枠内に入ったら収まったフラグをtrueにする
		if (m_pos[i].x < 45 && m_pos[i].x > -45 && m_pos[i].z < 45 && m_pos[i].z > -45)
			m_isFit[i] = true;
		else
			m_isFit[i] = false;

		//赤い枠内に全部入ったら次へ進むフラグをtrueにする
		if (m_isFit[i])
			cnt++;
		if (cnt == 9 && !m_isMove && !m_isAllFit)
		{
			m_isAllFit = true;
			playSound(SE_CLEAR);
		}
	}

	if (m_isAllFit && !m_isClear)
	{
		m_waitCnt++;
		if (m_waitCnt > 50)
		{
			m_isClear = true;
		}
	}

	Debug();
}

//---------------------
// 描画
//---------------------
void CubeControll::Draw()
{
	for (int i = 0; i < 9; i++)
	{
		// ３Dモデルのポジション設定
		MV1SetPosition(m_modelHandle, m_pos[i]);
		// ３Ｄモデルの描画
		MV1DrawModel(m_modelHandle);
	}
}

//---------------------
// 関数群
//---------------------

// 移動管理処理
void CubeControll::MoveCube(int i)
{
	if (GetInput(SHOT) == PUSHDOWN && m_isCanShot && !m_isSlide[i])
	{
		// プレイヤーがどの面に面しているかによって動かす方向を決める
		const bool moveLeft = m_playerPos.z > m_pos[i].z - m_radius && m_playerPos.z < m_pos[i].z + m_radius &&
			m_playerPos.x - m_range < m_pos[i].x + m_radius &&
			m_playerPos.x - m_range > m_pos[i].x - m_radius;
		const bool moveRight = m_playerPos.z > m_pos[i].z - m_radius && m_playerPos.z < m_pos[i].z + m_radius &&
			m_playerPos.x + m_range > m_pos[i].x - m_radius &&
			m_playerPos.x + m_range < m_pos[i].x + m_radius;
		const bool moveBack = m_playerPos.x > m_pos[i].x - m_radius && m_playerPos.x < m_pos[i].x + m_radius &&
			m_playerPos.z - m_range < m_pos[i].z + m_radius &&
			m_playerPos.z - m_range > m_pos[i].z - m_radius;
		const bool moveFront = m_playerPos.x > m_pos[i].x - m_radius && m_playerPos.x < m_pos[i].x + m_radius &&
			m_playerPos.z + m_range > m_pos[i].z - m_radius &&
			m_playerPos.z + m_range < m_pos[i].z + m_radius;

		if (moveLeft)	// 左へ動かす
		{
			m_isSlide[i] = true;
			m_slideVec = VGet(-m_moveSpeed, 0, 0);
			m_slideDirection = SLIDE_LEFT;
		}
		if (moveRight)	// 右へ動かす
		{
			m_isSlide[i] = true;
			m_slideVec = VGet(m_moveSpeed, 0, 0);
			m_slideDirection = SLIDE_RIGHT;
		}
		if (moveBack)	// 手前へ動かす
		{
			m_isSlide[i] = true;
			m_slideVec = VGet(0, 0, -m_moveSpeed);
			m_slideDirection = SLIDE_BACK;
		}
		if (moveFront)	// 奥へ動かす
		{
			m_isSlide[i] = true;
			m_slideVec = VGet(0, 0, m_moveSpeed);
			m_slideDirection = SLIDE_FRONT;
		}

		//隣接しているキューブがあるなら、そのキューブのスライドフラグもtrueにする
		if (m_isSlide[i])
		{
			CheckAdjacent(i);
		}
	}

	// 
	if (m_isSlide[i])
	{
		m_isMove = true;
		m_pos[i] = VAdd(m_pos[i], m_slideVec);
	}

	// 当たり判定
	DetectionCollision(i);
}

// 隣接しているキューブがあったらそれも動かすようにする処理
void CubeControll::CheckAdjacent(int i)
{
	for (int j = 0; j < 9; j++)
	{
		if (i == j)
		{
			j++;
		}
		if ((m_pos[j].x + m_radius == m_pos[i].x - m_radius && m_pos[j].z == m_pos[i].z && m_slideDirection == SLIDE_LEFT) ||
			(m_pos[j].x - m_radius == m_pos[i].x + m_radius && m_pos[j].z == m_pos[i].z && m_slideDirection == SLIDE_RIGHT) ||
			(m_pos[j].x == m_pos[i].x && m_pos[j].z - m_radius == m_pos[i].z + m_radius && m_slideDirection == SLIDE_FRONT) ||
			(m_pos[j].x == m_pos[i].x && m_pos[j].z + m_radius == m_pos[i].z - m_radius && m_slideDirection == SLIDE_BACK))
		{
			m_isSlide[j] = true;
		}
	}
}

// 当たり判定
void CubeControll::DetectionCollision(int i)
{
	bool hit = false;

	//マス目の端との判定
	if (m_pos[i].x < m_sqStartPoint.x || m_pos[i].x > m_sqEndPoint.x ||
		m_pos[i].z < m_sqEndPoint.z || m_pos[i].z > m_sqStartPoint.z)
	{
		hit = true;
		m_pos[i] = VAdd(m_pos[i], VScale(m_slideVec, -1));
	}

	//キューブ同士の判定
	for (int j = 0; j < 9; j++)
	{
		//同じキューブは判定しない
		if (i == j)
			j++;

		if (m_pos[i].x < m_pos[j].x + m_radius * 2 && m_pos[j].x < m_pos[i].x + m_radius * 2 &&
			m_pos[i].z < m_pos[j].z + m_radius * 2 && m_pos[j].z < m_pos[i].z + m_radius * 2 &&
			m_isSlide[j] == false)
		{
			hit = true;
			if (m_slideDirection == SLIDE_LEFT)
				m_pos[i].x = m_pos[j].x + m_radius * 2;
			if (m_slideDirection == SLIDE_RIGHT)
				m_pos[i].x = m_pos[j].x - m_radius * 2;
			if (m_slideDirection == SLIDE_FRONT)
				m_pos[i].z = m_pos[j].z - m_radius * 2;
			if (m_slideDirection == SLIDE_BACK)
				m_pos[i].z = m_pos[j].z + m_radius * 2;
		}
	}

	if (hit)
	{
		m_isSlide[i] = false;
		m_isMove = false;
		m_isHit[i] = true;
		playSound(SE_CUBEHIT);
	}
	else
	{
		m_isHit[i] = false;
	}
}

void CubeControll::ChangeNextPos(int nextStageNum)
{
	printfDx("aaa");
	for (int i = 0; i < 9; i++)
	{
		// キューブを所定の位置に設定
		m_pos[i] = m_squaresPos[m_nextPosNum[i + (nextStageNum - 1) * 9]];
		m_isSlide[i] = false;
		m_isFit[i] = false;
		m_isHit[i] = false;
	}
	m_nowStageNum = nextStageNum;
	m_isAllFit = false;
	m_isClear = false;
	m_waitCnt = 0;
}

// マス目とかの情報をセットする処理
void CubeControll::SetBordInfo()
{
	m_squaresPos[0] = VGet(-90, 0, 90);
	m_squaresPos[1] = VGet(-60, 0, 90);
	m_squaresPos[2] = VGet(-30, 0, 90);
	m_squaresPos[3] = VGet(0, 0, 90);
	m_squaresPos[4] = VGet(30, 0, 90);
	m_squaresPos[5] = VGet(60, 0, 90);
	m_squaresPos[6] = VGet(90, 0, 90);
	m_squaresPos[7] = VGet(-90, 0, 60);
	m_squaresPos[8] = VGet(-60, 0, 60);
	m_squaresPos[9] = VGet(-30, 0, 60);
	m_squaresPos[30] = VGet(0, 0, 60);
	m_squaresPos[11] = VGet(30, 0, 60);
	m_squaresPos[12] = VGet(60, 0, 60);
	m_squaresPos[13] = VGet(90, 0, 60);
	m_squaresPos[14] = VGet(-90, 0, 30);
	m_squaresPos[15] = VGet(-60, 0, 30);
	m_squaresPos[16] = VGet(-30, 0, 30);
	m_squaresPos[17] = VGet(0, 0, 30);
	m_squaresPos[18] = VGet(30, 0, 30);
	m_squaresPos[19] = VGet(60, 0, 30);
	m_squaresPos[20] = VGet(90, 0, 30);
	m_squaresPos[21] = VGet(-90, 0, 0);
	m_squaresPos[22] = VGet(-60, 0, 0);
	m_squaresPos[23] = VGet(-30, 0, 0);
	m_squaresPos[24] = VGet(0, 0, 0);
	m_squaresPos[25] = VGet(30, 0, 0);
	m_squaresPos[26] = VGet(60, 0, 0);
	m_squaresPos[27] = VGet(90, 0, 0);
	m_squaresPos[28] = VGet(-90, 0, -30);
	m_squaresPos[29] = VGet(-60, 0, -30);
	m_squaresPos[30] = VGet(-30, 0, -30);
	m_squaresPos[31] = VGet(0, 0, -30);
	m_squaresPos[32] = VGet(30, 0, -30);
	m_squaresPos[33] = VGet(60, 0, -30);
	m_squaresPos[34] = VGet(90, 0, -30);
	m_squaresPos[35] = VGet(-90, 0, -60);
	m_squaresPos[36] = VGet(-60, 0, -60);
	m_squaresPos[37] = VGet(-30, 0, -60);
	m_squaresPos[38] = VGet(0, 0, -60);
	m_squaresPos[39] = VGet(30, 0, -60);
	m_squaresPos[40] = VGet(60, 0, -60);
	m_squaresPos[41] = VGet(90, 0, -60);
	m_squaresPos[42] = VGet(-90, 0, -90);
	m_squaresPos[43] = VGet(-60, 0, -90);
	m_squaresPos[44] = VGet(-30, 0, -90);
	m_squaresPos[45] = VGet(0, 0, -90);
	m_squaresPos[46] = VGet(30, 0, -90);
	m_squaresPos[47] = VGet(60, 0, -90);
	m_squaresPos[48] = VGet(90, 0, -90);

	m_directionPos[0] = VGet(-90, 0.5, 105);
	m_directionPos[1] = VGet(-60, 0.5, 105);
	m_directionPos[2] = VGet(-30, 0.5, 105);
	m_directionPos[3] = VGet(0, 0.5, 105);
	m_directionPos[4] = VGet(30, 0.5, 105);
	m_directionPos[5] = VGet(60, 0.5, 105);
	m_directionPos[6] = VGet(90, 0.5, 105);
	m_directionPos[7] = VGet(105, 0.5, 90);
	m_directionPos[8] = VGet(105, 0.5, 60);
	m_directionPos[9] = VGet(105, 0.5, 30);
	m_directionPos[10] = VGet(105, 0.5, 0);
	m_directionPos[11] = VGet(105, 0.5, -30);
	m_directionPos[12] = VGet(105, 0.5, -60);
	m_directionPos[13] = VGet(105, 0.5, -90);
	m_directionPos[14] = VGet(90, 0.5, -105);
	m_directionPos[15] = VGet(60, 0.5, -105);
	m_directionPos[16] = VGet(30, 0.5, -105);
	m_directionPos[17] = VGet(0, 0.5, -105);
	m_directionPos[18] = VGet(-30, 0.5, -105);
	m_directionPos[19] = VGet(-60, 0.5, -105);
	m_directionPos[20] = VGet(-90, 0.5, -105);
	m_directionPos[21] = VGet(-105, 0.5, -90);
	m_directionPos[22] = VGet(-105, 0.5, -60);
	m_directionPos[23] = VGet(-105, 0.5, -30);
	m_directionPos[24] = VGet(-105, 0.5, 0);
	m_directionPos[25] = VGet(-105, 0.5, 30);
	m_directionPos[26] = VGet(-105, 0.5, 60);
	m_directionPos[27] = VGet(-105, 0.5, 90);

	m_sqStartPoint = VGet(-90, 0, 90);
	m_sqEndPoint = VGet(90, 0, -90);
}

void CubeControll::Debug()
{
	if (CheckHitKey(KEY_INPUT_NUMPAD1))
	{
		m_nowStageNum = 1;
		for (int i = 0; i < 9; i++)
		{
			// キューブを所定の位置に設定
			m_pos[i] = m_squaresPos[m_nextPosNum[i + (m_nowStageNum - 1) * 9]];
			m_isSlide[i] = false;
			m_isFit[i] = false;
			m_isHit[i] = false;
		}

		m_isMove = false;
		m_isAllFit = false;
		m_isSupport = false;
		m_isReset = false;
		m_isClear = false;
	}
	if (CheckHitKey(KEY_INPUT_NUMPAD2))
	{
		m_nowStageNum = 2;
		for (int i = 0; i < 9; i++)
		{
			// キューブを所定の位置に設定
			m_pos[i] = m_squaresPos[m_nextPosNum[i + (m_nowStageNum - 1) * 9]];
			m_isSlide[i] = false;
			m_isFit[i] = false;
			m_isHit[i] = false;
		}

		m_isMove = false;
		m_isAllFit = false;
		m_isSupport = false;
		m_isReset = false;
		m_isClear = false;
	}
	if (CheckHitKey(KEY_INPUT_NUMPAD3))
	{
		m_nowStageNum = 3;
		for (int i = 0; i < 9; i++)
		{
			// キューブを所定の位置に設定
			m_pos[i] = m_squaresPos[m_nextPosNum[i + (m_nowStageNum - 1) * 9]];
			m_isSlide[i] = false;
			m_isFit[i] = false;
			m_isHit[i] = false;
		}

		m_isMove = false;
		m_isAllFit = false;
		m_isSupport = false;
		m_isReset = false;
		m_isClear = false;
	}
	if (CheckHitKey(KEY_INPUT_NUMPAD4))
	{
		m_nowStageNum = 4;
		for (int i = 0; i < 9; i++)
		{
			// キューブを所定の位置に設定
			m_pos[i] = m_squaresPos[m_nextPosNum[i + (m_nowStageNum - 1) * 9]];
			m_isSlide[i] = false;
			m_isFit[i] = false;
			m_isHit[i] = false;
		}

		m_isMove = false;
		m_isAllFit = false;
		m_isSupport = false;
		m_isReset = false;
		m_isClear = false;
	}
	if (CheckHitKey(KEY_INPUT_NUMPAD5))
	{
		m_nowStageNum = 5
;
		for (int i = 0; i < 9; i++)
		{
			// キューブを所定の位置に設定
			m_pos[i] = m_squaresPos[m_nextPosNum[i + (m_nowStageNum - 1) * 9]];
			m_isSlide[i] = false;
			m_isFit[i] = false;
			m_isHit[i] = false;
		}

		m_isMove = false;
		m_isAllFit = false;
		m_isSupport = false;
		m_isReset = false;
		m_isClear = false;
	}
	if (CheckHitKey(KEY_INPUT_NUMPAD6))
	{
		m_nowStageNum = 6;
		for (int i = 0; i < 9; i++)
		{
			// キューブを所定の位置に設定
			m_pos[i] = m_squaresPos[m_nextPosNum[i + (m_nowStageNum - 1) * 9]];
			m_isSlide[i] = false;
			m_isFit[i] = false;
			m_isHit[i] = false;
		}

		m_isMove = false;
		m_isAllFit = false;
		m_isSupport = false;
		m_isReset = false;
		m_isClear = false;
	}
	if (CheckHitKey(KEY_INPUT_NUMPAD7))
	{
		m_nowStageNum = 7;
		for (int i = 0; i < 9; i++)
		{
			// キューブを所定の位置に設定
			m_pos[i] = m_squaresPos[m_nextPosNum[i + (m_nowStageNum - 1) * 9]];
			m_isSlide[i] = false;
			m_isFit[i] = false;
			m_isHit[i] = false;
		}

		m_isMove = false;
		m_isAllFit = false;
		m_isSupport = false;
		m_isReset = false;
		m_isClear = false;
	}
	if (CheckHitKey(KEY_INPUT_NUMPAD8))
	{
		m_nowStageNum = 8;
		for (int i = 0; i < 9; i++)
		{
			// キューブを所定の位置に設定
			m_pos[i] = m_squaresPos[m_nextPosNum[i + (m_nowStageNum - 1) * 9]];
			m_isSlide[i] = false;
			m_isFit[i] = false;
			m_isHit[i] = false;
		}

		m_isMove = false;
		m_isAllFit = false;
		m_isSupport = false;
		m_isReset = false;
		m_isClear = false;
	}
	if (CheckHitKey(KEY_INPUT_NUMPAD9))
	{
		m_nowStageNum = 9;
		for (int i = 0; i < 9; i++)
		{
			// キューブを所定の位置に設定
			m_pos[i] = m_squaresPos[m_nextPosNum[i + (m_nowStageNum - 1) * 9]];
			m_isSlide[i] = false;
			m_isFit[i] = false;
			m_isHit[i] = false;
		}

		m_isMove = false;
		m_isAllFit = false;
		m_isSupport = false;
		m_isReset = false;
		m_isClear = false;
	}
}


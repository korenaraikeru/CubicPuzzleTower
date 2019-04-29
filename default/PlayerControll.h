//---------------------------------------------------------------
// プレイヤーコントロールクラス
//---------------------------------------------------------------
#pragma once
#include "DxLib.h"

class PlayerControll
{
public:
	PlayerControll();	// コンストラクタ
	~PlayerControll();	// デストラクタ

	//---主要関数-------------------------------------------------------------------
	void Init();		// 初期化
	void Update();		// 更新
	void Draw();		// 描画
	//-----------------------------------------------------------------------------

	//---Get関数--------------------------------------------------------------------
	const VECTOR& GetPos() const { return m_pos; }			// ポジションのゲット関数
	bool GetIsGround() { return m_isGround; }				// 着地フラグのゲット関数
	//------------------------------------------------------------------------------
	
	//---Set関数---------------------------------------------------------------------
	void SetFloorPos(VECTOR v) { m_floorPos = v; }			// 床のポジションのセット関数
	void SetIsAbleMove(bool flag) { m_isAbleMove = flag; }	// 動けるフラグのセット関数
	//------------------------------------------------------------------------------

private:
	//---関数群----------------------------------------------------------------------
	void MovePlayer();						// 移動管理処理
	void CheckGround();						// 着地処理
	void UpdateVelocity();					// 移動ベクトル更新処理
	void CalculateAngleY(float x, float y);	// 回転角計算処理
	void FixedDirection();					// 向き固定処理
	void Jump();							// ジャンプ処理
	void CangeScale();						// スケールを変更してぷよぷよさせる処理
	void Shot();							// ショット処理
	void DetectionCollision();				// 当たり判定
	//------------------------------------------------------------------------------

	//---変数群----------------------------------------------------------------------
	int m_modelHandle;	// モデルハンドル

	VECTOR m_pos;		// ポジション
	VECTOR m_velocity;	// 移動ベクトル
	VECTOR m_scale;		// 拡大率
	VECTOR m_floorPos;	// 床のポジション
	VECTOR m_prevPos;	// 元のポジション（ショット時使用）
	VECTOR m_shotVec;	// ショット時のベクトル
	VECTOR m_returnVec;	// ショット時の戻り用ベクトル

	float m_angleY;		// Y軸の回転角度
	float m_moveSpeed;	// 移動速度
	float m_grabity;	// 重力
	float m_jumpAccel;	// ジャンプの初速
	float m_jumpVec;	// ジャンプ時の座標更新用変数
	float m_radius;		// モデルの半径

	bool m_isAbleMove;
	bool m_isGround;	// 着地フラグ
	bool m_isMove;		// 移動中フラグ
	bool m_isJump;		// ジャンプフラグ
	bool m_isShot;		// ショットフラグ
	bool m_isReturn;	// ショット時に元の位置に戻るためのフラグ

	int m_moveCnt;		// 移動中のカウンタ
	//------------------------------------------------------------------------------
};


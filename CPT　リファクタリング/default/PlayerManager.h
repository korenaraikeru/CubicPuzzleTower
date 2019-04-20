#pragma once
#include "PlayerControll.h"

class PlayerManager
{
public:
	PlayerManager();
	~PlayerManager();

	void Init();	// 初期化
	void Update();	// 更新
	void Draw();	// 描画

	VECTOR GetPlayerPos(){ return p_playerControll->GetPos(); }				// ポジションのゲット関数
	bool GetIsGround() { return p_playerControll->GetIsGround(); }			// 着地フラグのゲット関数
	void SetFloorPos(VECTOR v) { p_playerControll->SetFloorPos(v); }		// 床のポジションのセット関数
	void SetIsCanMove(bool flag) { p_playerControll->SetIsCanMove(flag); }	// 動けるフラグのセット関数

private:
	PlayerControll *p_playerControll;		// プレイヤーコントロールクラスのポインター
};


//-----------------------------------------------------------------------------
// プレイヤーベースクラス
//-----------------------------------------------------------------------------
#pragma once
#include "DxLib.h"
#include "PlayerControll.h"

class PlayerBase
{
public:
	PlayerBase();		// コンストラクタ
	~PlayerBase();		// デストラクタ

	//---主要関数-------------------------------------------------------------------
	void Create();		// 生成
	void Delete();		// 削除
	void Init();		// 初期化 
	void Update();		// 更新 
	void Draw();		// 描画 
	//-----------------------------------------------------------------------------

	//---Get関数--------------------------------------------------------------------
	VECTOR GetPlayerPos() { return p_playerControll->GetPos(); }
	bool GetPlayerIsGround() { return p_playerControll->GetIsGround(); }
	//-----------------------------------------------------------------------------
	
	//---Set関数--------------------------------------------------------------------
	void SetFloorPosToPlayer(VECTOR v) { p_playerControll->SetFloorPos(v); }
	void SetIsAbleMoveToPlayer(bool flag) { p_playerControll->SetIsAbleMove(flag); }
	//-----------------------------------------------------------------------------

private:
	PlayerControll *p_playerControll;
};


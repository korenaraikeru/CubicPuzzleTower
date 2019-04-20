//---------------------------------------------------------------
// プレイヤーマネージャークラス
//---------------------------------------------------------------
#include "PlayerManager.h"

//---------------------
// コンストラクタ
//---------------------
PlayerManager::PlayerManager()
{
	p_playerControll = new PlayerControll();
}

//---------------------
// デストラクタ
//---------------------
PlayerManager::~PlayerManager()
{
	// 処理なし
}

//---------------------
// 初期化
//---------------------
void PlayerManager::Init()
{
	p_playerControll->Init();
}

//---------------------
// 更新
//---------------------
void PlayerManager::Update()
{
	p_playerControll->Update();
}

//---------------------
// 描画
//---------------------
void PlayerManager::Draw()
{
	p_playerControll->Draw();
}

#include "PlayerManager.h"

PlayerManager::PlayerManager()
{
	p_playerControll = new PlayerControll();
}


PlayerManager::~PlayerManager()
{
	
}

void PlayerManager::Init()
{
	p_playerControll->Init();
}

void PlayerManager::Update()
{
	p_playerControll->Update();
}

void PlayerManager::Draw()
{
	p_playerControll->Draw();
}

VECTOR PlayerManager::GetPlayerPos()
{
	return p_playerControll->GetPos();
}

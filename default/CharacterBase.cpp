#include "CharacterBase.h"

CharacterBase::CharacterBase()
{
}


CharacterBase::~CharacterBase()
{
}

void CharacterBase::Create()
{
	p_player = new PlayerControll();
}

void CharacterBase::Delete()
{
	delete(p_player);
}

void CharacterBase::Init()
{
	p_player->Init();
}

void CharacterBase::Update()
{
	p_player->Update();
}

void CharacterBase::Draw()
{
	p_player->Draw();
}

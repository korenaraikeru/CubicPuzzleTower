#pragma once
#include "DxLib.h"
#include "PlayerControll.h"

class CharacterBase
{
public:
	CharacterBase();
	~CharacterBase();

	//---Žå—vŠÖ”-----------------------------------
	void Create();
	void Delete();
	void Init();
	void Update();
	void Draw();
	//---------------------------------------------

	//---GetŠÖ”-----------------------------------
	VECTOR GetPlayerPos() { return p_player->GetPos(); }
	bool GetPlayerIsGround() { return p_player->GetIsGround(); }
	//---------------------------------------------
	
	//---SetŠÖ”-----------------------------------
	void SetFloorPosToPlayer(VECTOR v) { p_player->SetFloorPos(v); }
	void SetIsCanMoveToPlayer(bool flag) { p_player->SetIsCanMove(flag); }
	//---------------------------------------------

private:
	PlayerControll *p_player;

};


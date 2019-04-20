#pragma once
#include "PlayerControll.h"

class PlayerManager
{
public:
	PlayerManager();
	~PlayerManager();

	void Init();
	void Update();
	void Draw();

	VECTOR GetPlayerPos();
	void SetFloorPos(VECTOR v) { p_playerControll->SetFloorPos(v); }
	bool GetIsGround() { return p_playerControll->GetIsGround(); }
	void SetIsCanMove(bool flag) { p_playerControll->SetIsCanMove(flag); }

private:
	PlayerControll *p_playerControll;

	int m_modelHandle;
	VECTOR m_pos;
	VECTOR m_scale;
};


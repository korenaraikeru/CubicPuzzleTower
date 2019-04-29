#pragma once
#include "DxLib.h"

class Player;
class Scaf;
class Title;

class Shadow
{
public:
	Shadow();
	~Shadow();

	void Init();
	void TitleUpdate(const Title& title);
	void Update(const Player& player, const Scaf& scaf);
	void Draw();
private:
	int modelHandle;

	VECTOR pos, p_pos;
	float angle;
};
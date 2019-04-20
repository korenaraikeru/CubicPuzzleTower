#pragma once
#include "DxLib.h"

class Map
{
public:
	Map();
	~Map();

	void Update();
	void Draw();
private:
	int modelHandle_stage;
	int modelHandle_frame;
	int modelHandle_tower;
};


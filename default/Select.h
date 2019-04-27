#pragma once
#include "DxLib.h"

class Select
{
public:
	Select();
	~Select();
	
	void Init();
	void Update();
	void Draw();

	int GetLevel() { return level[level_num]; }

private:
	int level[4];
	int level_num;

	int graph_level[4];
	int graph_back;
	int graph_slime;

	int s_x, s_y;
	
	bool input_once;
};
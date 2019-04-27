#pragma once
#include "DxLib.h"

class State;

class UI
{
public:
	UI();
	~UI();

	void Init();
	void Update(const State& state);
	void Draw();
private:
	int graph_floor[12];
	int graph_manual;
	int graph_tutorial[5];

	int floor_x, floor_y;
	int stage_num;
	int alpha;
	int tut_num;
	int cnt;
};
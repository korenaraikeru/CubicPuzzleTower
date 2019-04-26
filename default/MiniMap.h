#pragma once
#include "DxLib.h"

class Player;
class Cube;

class miniMap
{
public:
	miniMap();
	~miniMap();
	void Init(const Cube& cube);
	void Update(const Player& player, const Cube& cube);
	void Draw();
private:
	int graph_map;
	int graph_frame;
	int graph_cube;
	int graph_dir;

	float f_x, f_y, c_x[9], c_y[9];
	VECTOR p_pos, d_pos;

	bool support_flag;
};
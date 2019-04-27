#pragma once
#include "DxLib.h"

class Title
{
public:
	Title();
	~Title();

	void Init();
	void Update();
	void Draw();
	const VECTOR GetPos() const { return s_pos; }
	const VECTOR GetScale() const { return VGet(scaleX, 0.f, scaleZ); }
	const float GetAngle() const { return angleY; }
private:
	int modelHandle_tower;
	int modelHandle_slime;
	int graph_title;
	int graph_start;

	VECTOR t_pos, s_pos;

	float jump_vec;
	float angleY;
	float scaleX;
	float scaleY;
	float scaleZ;
	bool move_flag;
	bool start_flag;

	int cnt;
	int alpha;
};

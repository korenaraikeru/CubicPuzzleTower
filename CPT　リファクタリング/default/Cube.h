#pragma once
#include "DxLib.h"

class Player;

class Cube
{
public:
	Cube();
	~Cube();

	const VECTOR& GetPos(int i) const { return pos[i]; }
	const VECTOR& GetDirPos() const { return dir_pos[support_num]; }
	void Init();
	void Update(const Player& player);
	void Draw();
	int HitJudge();
	void ShotSupport();
	void ChangeStage(int stage_num);
	void Reset();

	bool cube_move;
	bool clear_flag;
	bool support_flag;
	bool hit_flag[9];

private:

	void MissCheck();

	int modelHandle;
	int modelHandle_dir;

	VECTOR pos[9];
	VECTOR p_pos;
	VECTOR cube_pos[9], squares_pos[49], sq_startPoint, sq_endPoint, dir_pos[28];
	float speed;
	float range;

	int size;
	int p_dir;
	int slide_dir;
	int now_stage;
	int support_num;
	int wait_cnt;
	int next_pos[108] = {
		16, 3, 18, 23, 24, 27, 30, 31, 32,
		2, 17, 20, 9, 24, 27, 30, 31, 32,
		16, 17, 18, 0, 24, 27, 28, 31, 48,
		16, 3, 18, 21,22, 25, 30, 45, 32,
		16, 0, 4, 21, 24, 25, 42, 45, 48,
		14, 3, 20, 23, 24, 25, 44, 28, 34,
		2, 6, 14, 9, 24, 27, 30, 31, 32,
		16, 3, 18, 44, 27, 6, 28, 45, 34,
		14, 0, 20, 42, 24, 48, 44, 45, 4,
		16, 20, 4, 37, 26, 48, 42, 45, 32,
		2, 4, 14, 20, 21, 27, 30, 32, 45,
		3, 6, 14, 18, 30, 34, 42, 46, 48
	};

	
	bool slide_flag[9];
	bool fit_cube[9];
	bool reset_flag;
	bool next_flag;
};


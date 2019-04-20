#include "MiniMap.h"
#include "Player.h"
#include "Cube.h"

miniMap::miniMap()
{
	graph_map = LoadGraph("data/miniMap.png");
	graph_frame = LoadGraph("data/frame.png");
	graph_cube = LoadGraph("data/cube.png");
	graph_dir = LoadGraph("data/dir_len.png");
}

miniMap::~miniMap()
{
}

void miniMap::Init(const Cube& cube)
{
	f_x = 1500;
	f_y = 150;
	d_pos = VGet(0, 0, 0);
	p_pos = VGet(0, 0, 0);
	for (int i = 0; i < 9; i++)
	{
		c_x[i] = cube.GetPos(i).x;
		c_y[i] = cube.GetPos(i).z;
	}
	support_flag = false;
}

void miniMap::Update(const Player& player, const Cube& cube)
{
	for (int i = 0; i < 9; i++)
	{
		c_x[i] = cube.GetPos(i).x;
		c_y[i] = -cube.GetPos(i).z;
	}
	p_pos = player.GetPos();
	d_pos = cube.GetDirPos();

	if (!cube.clear_flag && p_pos.y >= 0 && cube.support_flag)
		support_flag = true;
	else
		support_flag = false;
}

void miniMap::Draw()
{
	DrawGraph((int)f_x - 95, (int)f_y - 95, graph_map, TRUE);
	DrawGraph((int)f_x, (int)f_y, graph_frame, TRUE);
	
	if (support_flag)
	{
		if (p_pos.x < 105 && p_pos.x > -105)
		{
			if (p_pos.z > 105)
				DrawRotaGraph((int)d_pos.x + (int)f_x + 105, (int)-d_pos.z + (int)f_y + 210, 1.0f, 0, graph_dir, TRUE);
			else if (p_pos.z < -105)
				DrawRotaGraph((int)d_pos.x + (int)f_x + 105, (int)-d_pos.z + (int)f_y, 1.0f, 180.0f / 180.0f * DX_PI_F, graph_dir, TRUE);
		}
		else if (p_pos.z < 105 && p_pos.z > -105)
		{
			if (p_pos.x > 105)
				DrawRotaGraph((int)d_pos.x + (int)f_x, (int)-d_pos.z + (int)f_y + 105, 1.0f, 90.0f / 180.0f * DX_PI_F, graph_dir, TRUE);
			else if (p_pos.x < -105)
				DrawRotaGraph((int)d_pos.x + (int)f_x + 210, (int)-d_pos.z + (int)f_y + 105, 1.0f, 270.0f / 180.0f * DX_PI_F, graph_dir, TRUE);
		}
	}

	for (int i = 0; i < 9; i++)
	{
		DrawGraph((int)c_x[i] + (int)f_x + 90, (int)c_y[i] + (int)f_y + 90, graph_cube, TRUE);
	}
}

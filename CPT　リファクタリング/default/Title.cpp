#include "Title.h"
#include "Inputkey.h"

Title::Title()
{
	modelHandle_tower = MV1LoadModel("data/model/tower_title.mqo");
	modelHandle_slime = MV1LoadModel("data/model/slime.mqo");
	graph_title = LoadGraph("data/title2.png");
	graph_start = LoadGraph("data/start.png");

	t_pos = VGet(0.0f, 0.0f, 0.0f);
	s_pos = VGet(30.0f, 0.0f, -890.0f);

	jump_vec = 4.f;
	move_flag = false;
}

Title::~Title()
{
	MV1DeleteModel(modelHandle_tower);
	MV1DeleteModel(modelHandle_slime);
}

void Title::Init()
{
	t_pos = VGet(0.0f, 0.0f, 0.0f);
	s_pos = VGet(30.0f, 0.0f, -890.0f);

	jump_vec = 4.f;
	angleY = -40.f;
	scaleX = 1.f;
	scaleY = 1.f;
	scaleZ = 1.f;
	start_flag = false;
	move_flag = false;
	cnt = 0;
	alpha = 255;
}

void Title::Update()
{
	if (!start_flag)
	{
		if (cnt == 0)
			alpha = 255;
		else if (cnt == 30)
			alpha = 0;

		if (alpha == 255)
			cnt++;
		else
			cnt--;
	}
	else
	{
		if (cnt == 0)
			alpha = 255;
		else if (cnt == 5)
			alpha = 0;

		if (alpha == 255)
			cnt++;
		else
			cnt--;
	}
	if ((getKey(KEY_INPUT_RETURN) == KEY_STATE_PUSHDOWN || getPad(PAD_INPUT_8)) && 
		!start_flag)
	{
		alpha = 255;
		cnt = 0;
		start_flag = true;
	}
	if (start_flag && s_pos.y == 0.f)
	{
		move_flag = true;
	}

	if (move_flag)
	{
		s_pos.z += 3.5f;
		s_pos.x -= 0.2f;
		angleY -= 20.f;
	}

	s_pos.y = s_pos.y + jump_vec;
	jump_vec = jump_vec - 0.2f;
	if (jump_vec < 0 && s_pos.y < 5)
	{
		scaleX += 0.2f;
		scaleY -= 0.2f;
		scaleZ += 0.2f;
	}
	else if (scaleY < 1.f)
	{
		scaleX -= 0.1f;
		scaleY += 0.1f;
		scaleZ -= 0.1f;
	}

	if (s_pos.y < 0)
	{
		s_pos.y = 0.f;
		jump_vec = 4.f;
	}

	MV1SetPosition(modelHandle_tower, t_pos);
	MV1SetPosition(modelHandle_slime, s_pos);

	MV1SetScale(modelHandle_slime, VGet(scaleX, scaleY, scaleZ));
	MV1SetRotationXYZ(modelHandle_slime, VGet(0.0f, angleY / 180.0f * DX_PI_F, 2.0f / 180.0f * DX_PI_F));
}

void Title::Draw()
{
	MV1DrawModel(modelHandle_slime);
	MV1DrawModel(modelHandle_tower);

	DrawGraph(0, 0, graph_title, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawGraph(0, 0, graph_start, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}


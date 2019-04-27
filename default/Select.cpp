#include "Select.h"
#include "Inputkey.h"
#include "Define.h"
#include "Sound.h"

#include "InputInfo.h"

Select::Select()
{
	level[0] = easy;
	level[1] = normal;
	level[2] = hard;
	level[3] = extra;

	graph_level[0] = LoadGraph("data/easy.png");
	graph_level[1] = LoadGraph("data/normal.png");
	graph_level[2] = LoadGraph("data/hard.png");
	graph_level[3] = LoadGraph("data/extra.png");
	graph_back = LoadGraph("data/select.png");
	graph_slime = LoadGraph("data/slime.png");
}

Select::~Select()
{

}

void Select::Init()
{
	level_num = 0;
	s_x = 0;
	s_y = 0;
	input_once = false;
}

void Select::Update()
{
	if ((GetInput(RIGHT) == PUSHDOWN || getPad(PAD_INPUT_RIGHT)) &&
		!input_once)
	{
		input_once = true;
		playSound(SE_CURSOR);
		if (level_num == 3)
			level_num = 0;
		else
			level_num++;
	}
	else if ((getKey(KEY_INPUT_LEFT) == KEY_STATE_PUSHDOWN || getPad(PAD_INPUT_LEFT)) &&
		!input_once)
	{
		input_once = true;
		playSound(SE_CURSOR);
		if (level_num == 0)
			level_num = 3;
		else
			level_num--;
	}
	else if (getPad(PAD_INPUT_RIGHT) == 0 && getPad(PAD_INPUT_LEFT) == 0)
	{
		input_once = false;
	}

	if (level_num == 0 || level_num == 2)
		s_y = 260;
	else
		s_y = 635;

	if (level_num == 0)
		s_x = 270;
	if (level_num == 1)
		s_x = 675;
	if (level_num == 2)
		s_x = 1166;
	if (level_num == 3)
		s_x = 1550;
}

void Select::Draw()
{
	DrawGraph(0, 0, graph_back, TRUE);

	SetDrawBright(150, 150, 150);
	if (level[level_num] == easy)
	{
		SetDrawBright(255, 255, 255);
	}
	DrawGraph(0, 0, graph_level[0], TRUE);
	SetDrawBright(150, 150, 150);

	if (level[level_num] == normal)
	{
		SetDrawBright(255, 255, 255);
	}
	DrawGraph(0, 0, graph_level[1], TRUE);
	SetDrawBright(150, 150, 150);

	if (level[level_num] == hard)
	{
		SetDrawBright(255, 255, 255);
	}
	DrawGraph(0, 0, graph_level[2], TRUE);
	SetDrawBright(150, 150, 150);

	if (level[level_num] == extra)
	{
		SetDrawBright(255, 255, 255);
	}
	DrawGraph(0, 0, graph_level[3], TRUE);
	SetDrawBright(255, 255, 255);

	DrawGraph(s_x, s_y, graph_slime, TRUE);
}


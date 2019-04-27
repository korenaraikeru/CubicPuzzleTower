#include "UI.h"
#include "Define.h"
#include "State.h"

UI::UI()
{
	LoadDivGraph("data/floor.png", 12, 12, 1, 180, 120, graph_floor, TRUE);
	graph_manual = LoadGraph("data/sousa.png");
	graph_tutorial[0] = LoadGraph("data/tutorial1.png");
	graph_tutorial[1] = LoadGraph("data/tutorial2.png");
	graph_tutorial[2] = LoadGraph("data/tutorial3.png");
	graph_tutorial[3] = LoadGraph("data/tutorial4.png");
	graph_tutorial[4] = LoadGraph("data/tutorial5.png");
}

UI::~UI()
{

}

void UI::Init()
{
	floor_x = SCREEN_W / 2 - 90;
	floor_y = 100;
	stage_num = 0;
	alpha = 255;
	tut_num = 0;
	cnt = 0;
}

void UI::Update(const State& state)
{
	stage_num = state.stage_num - 1;
	
	if (cnt < 100)
		cnt++;
	else
		alpha -= 5;

	if (alpha == 0)
	{ 
		tut_num++;
		if (tut_num > 4)
			tut_num = 0;
		alpha = 255;
		cnt = 0;
	}
}

void UI::Draw()
{
	DrawGraph(floor_x, floor_y, graph_floor[stage_num], TRUE);
	DrawGraph(0, 50, graph_manual, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawGraph(0, 0, graph_tutorial[tut_num], TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

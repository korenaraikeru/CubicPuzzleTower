#include "Clear.h"

Clear::Clear()
{
	graph_clear = LoadGraph("data/clear2.png");
	graph_start = LoadGraph("data/clear_start.png");
}

Clear::~Clear()
{
	DeleteGraph(graph_clear);
	DeleteGraph(graph_start);
}

void Clear::Init()
{
	alpha = 255;
	cnt = 0;
}

void Clear::Update()
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

void Clear::Draw()
{
	DrawGraph(0, 0, graph_clear, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawGraph(1250, 1010, graph_start, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}
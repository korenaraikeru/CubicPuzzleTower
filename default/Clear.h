#pragma once
#include "DxLib.h"

class Clear
{
public:
	Clear();
	~Clear();

	void Init();
	void Update();
	void Draw();

private:
	int graph_clear;
	int graph_start;

	int alpha;
	int cnt;
};

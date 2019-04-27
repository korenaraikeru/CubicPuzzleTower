#pragma once
#include "DxLib.h"

class Player;
class Shadow;
class Cube;
class Scaf;
class Title;
class Select;

class State
{
public:
	State();
	~State();

	void Init();
	void Update(Player &player, Cube &cube, Scaf& scaf, Title& title, Select& select);
	void Draw();

	bool GetInitFlag() { return init_flag; }

	int game_state;
	int stage_num;
private:
	int graph_pause;
	int graph_reset;
	int graph_return;
	int graph_close;

	bool next_flag;
	bool return_flag;
	bool init_flag;
	bool input_once;

	int alpha;

	int menu_num;
};
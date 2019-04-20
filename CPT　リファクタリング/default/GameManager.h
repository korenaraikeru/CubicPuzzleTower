#pragma once

#include "DxLib.h"
#include "Player.h"
#include "Camera.h"
#include "Map.h"
#include "Cube.h"
#include "State.h"
#include "Inputkey.h"
#include "Scaffold.h"
#include "Shadow.h"
#include "Define.h"
#include "Title.h"
#include "Select.h"
#include "Clear.h"
#include "MiniMap.h"
#include "UI.h"
#include "Sound.h"

#include "InputInfo.h"
#include "PlayerManager.h"

class GameManager
{
public:
	GameManager();
	~GameManager();

	void Create();
	void Delete();
	void Init();
	void Update();
	void Draw();

	int GetNowState() { return state->game_state; }

private:
	Camera * camera;
	Player* player;
	Map* map;
	Cube* cube;
	Scaf* scaf;
	Shadow* shadow; 
	Title* title; 
	Select* select; 
	Clear* clear;
	miniMap* mini;
	UI* ui;
	State* state;

	PlayerManager* playerManager;
};


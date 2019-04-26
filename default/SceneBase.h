#pragma once
#include <DxLib.h>
#include "InputInfo.h"
#include "Camera.h"
#include "PlayerManager.h"
#include "MapObjectManager.h"
#include "StageManager.h"
#include "UIManager.h"

typedef enum SCENE_TYPE
{
	TITLE,
	SELECT,
	PLAY,
	NEXT,
	PAUSE,
	CLEAR,
}SCENE_TYPE;

class SceneBase
{
public:
	SceneBase();
	~SceneBase();

	void Create();
	void Delete();
	void Init();
	void Update();
	void Draw();

private:
	void StateChange();

	SCENE_TYPE nowScene;

	Camera *p_camera;
	PlayerManager *p_player;
	MapObjectManager *p_mapObject;
	StageManager *p_stage;
	UIManager *p_ui;
};


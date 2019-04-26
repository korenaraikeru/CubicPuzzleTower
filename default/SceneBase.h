#pragma once
#include <DxLib.h>
#include "InputInfo.h"
#include "CharacterBase.h"
#include "ObjectBase.h"
#include "Camera.h"
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

	CharacterBase *p_characterBase;
	ObjectBase *p_objectBase;

	Camera *p_camera;
	StageManager *p_stage;
	UIManager *p_ui;
};


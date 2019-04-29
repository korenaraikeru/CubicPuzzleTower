#pragma once
#include <DxLib.h>
#include "Define.h"
#include "InputInfo.h"
#include "CharacterBase.h"
#include "ObjectBase.h"
#include "Camera.h"
#include "StageManager.h"
#include "UIBase.h"

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

	SCENE_TYPE m_nowScene;

	CharacterBase *p_characterBase;
	ObjectBase *p_objectBase;

	Camera *p_camera;
	StageManager *p_stage;
	UIBase *p_ui;
};


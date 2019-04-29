#pragma once
#include "DxLib.h"
#include "Define.h"
#include "UIControll.h"
#include "MiniMapControll.h"

class UIBase
{
public:
	UIBase();
	~UIBase();

	//---éÂóvä÷êî-----------------------------------
	void Create();
	void Delete();
	void Init();
	void Update();
	void Draw();
	//---------------------------------------------


	void SetNowScene(SCENE_TYPE scene) { m_nowScene = scene; }
	void SetMiniMapInfo(int i, VECTOR cubePos, VECTOR playerPos, VECTOR dirPos, bool isSupport);

private:
	UIControll *p_uiControll;
	MiniMapControll *p_miniMap;

	SCENE_TYPE m_nowScene;
};


#pragma once
#include "DxLib.h"
#include "MiniMapControll.h"

class UIManager
{
public:
	UIManager();
	~UIManager();

	void Init();
	void Update();
	void Draw();

	void SetMiniMapInfo(int i, VECTOR cubePos, VECTOR playerPos, VECTOR dirPos, bool isSupport);

private:
	MiniMapControll *p_miniMap;
};


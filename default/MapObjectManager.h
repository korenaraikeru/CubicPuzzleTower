#pragma once
#include "DxLib.h"
#include "FloorControll.h"
#include "CubeControll.h"

class MapObjectManager
{
public:
	MapObjectManager();
	~MapObjectManager();

	void Init();
	void Update();
	void Draw();

	void SetPlayerPos(VECTOR v) { p_cubeControll->SetPlayerPos(v); }
	VECTOR GetFloorPos() { return p_floorControll->GetPos(); }
	VECTOR GetCubePos(int i) { return p_cubeControll->GetPos(i); }
	VECTOR GetCubeDirPos() { return p_cubeControll->GetDirPos(); }
	bool GetIsSupport() { return p_cubeControll->GetIsSupport(); }
	bool GetIsClear() { return p_cubeControll->GetIsClear(); }
	void NextStage(int n);
	void SetIsCanShot(bool flag) { p_cubeControll->SetIsCanShot(flag); }
	bool GetIsEndRising() { return p_floorControll->GetIsEndRising(); }

private:
	int m_modelHandleTower;
	int m_modelHandleFrame;

	FloorControll *p_floorControll;
	CubeControll *p_cubeControll;
};


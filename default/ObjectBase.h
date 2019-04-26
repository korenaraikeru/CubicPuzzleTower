#pragma once
#include "CubeControll.h"
#include "FieldObjectControll.h"

class ObjectBase
{
public:
	ObjectBase();
	~ObjectBase();

	//---Žå—vŠÖ”-----------------------------------
	void Create();
	void Delete();
	void Init();
	void Update();
	void Draw();
	//---------------------------------------------
	
	//---GetŠÖ”-----------------------------------
	VECTOR GetCubePos(int i) { return p_cube->GetPos(i); }
	VECTOR GetCubeDirPos() { return p_cube->GetDirPos(); }
	VECTOR GetFloorPos() { return p_fieldObject->GetFloorPos(); }
	bool GetCubeIsSupport() { return p_cube->GetIsSupport(); }
	bool GetCubeIsClear() { return p_cube->GetIsClear(); }
	bool GetFloorIsEndRising() { return p_fieldObject->GetIsEndRising(); }
	//---------------------------------------------

	//---SetŠÖ”-----------------------------------
	void SetPlayerPosToCube(VECTOR v) { p_cube->SetPlayerPos(v); }
	void SetIsCanShotToCube(bool flag) { p_cube->SetIsCanShot(flag); }
	void SetFloorIsRising(bool flag) { p_fieldObject->SetIsRising(flag); }
	//---------------------------------------------
	
	void NextStage(int n);

private:
	CubeControll *p_cube;
	FieldObjectControll *p_fieldObject;

};


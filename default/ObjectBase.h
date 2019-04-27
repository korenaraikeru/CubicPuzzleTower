//-----------------------------------------------------------------------------
// オブジェクトベースクラス
//-----------------------------------------------------------------------------
#pragma once
#include "CubeControll.h"
#include "FieldObjectManager.h"

class ObjectBase
{
public:
	ObjectBase();		// コンストラクタ
	~ObjectBase();		// デストラクタ

	//---主要関数-------------------------------------------------------------------
	void Create();		// 生成
	void Delete();		// 削除
	void Init();		// 初期化
	void Update();		// 更新
	void Draw();		// 描画
	//-----------------------------------------------------------------------------

	
	//---Get関数--------------------------------------------------------------------
	VECTOR GetCubePos(int i) { return p_cube->GetPos(i); }
	VECTOR GetCubeDirPos() { return p_cube->GetDirPos(); }
	VECTOR GetFloorPos() { return p_fieldObject->GetFloorPos(); }
	bool GetCubeIsSupport() { return p_cube->GetIsSupport(); }
	bool GetCubeIsClear() { return p_cube->GetIsClear(); }
	bool GetIsFloorRisingEnd() { return p_fieldObject->GetIsEndRising(); }
	//------------------------------------------------------------------------------

	//---Set関数---------------------------------------------------------------------
	void SetPlayerPosToCube(VECTOR v) { p_cube->SetPlayerPos(v); }
	void SetIsAbleShotToCube(bool flag) { p_cube->SetIsAbleShot(flag); }
	void SetIsRising(bool flag) { p_fieldObject->SetIsRising(flag); }
	//------------------------------------------------------------------------------

	void ChangeToNextStage(int n);		// 次のステージへ行く際の変更処理

private:
	CubeControll *p_cube;
	FieldObjectManager *p_fieldObject;

};


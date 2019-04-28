//-----------------------------------------------------------------------------
// シーンコントロールクラス
//-----------------------------------------------------------------------------
#pragma once
#include "DxLib.h"
#include "InputInfo.h"
#include "Sound.h"
#include "PlayerBase.h"
#include "ObjectBase.h"
#include "Camera.h"
#include "StageManager.h"
#include "UIBase.h"

class SceneControll
{
public:
	SceneControll();		// コンストラクタ
	~SceneControll();		// デストラクタ

	//---主要関数-------------------------------------------------------------------
	void Create();
	void Delete();
	void Init();			// 初期化
	void UpdateTitle();		// 更新
	void UpdateSelect();	// 更新
	void UpdatePlay();		// 更新
	void DrawTitle();		// 描画
	void DrawSelect();		// 描画
	void DrawPlay();		// 描画
	//-----------------------------------------------------------------------------
	
	void ChangeScene();		// シーン切り替え処理

	//---Get関数--------------------------------------------------------------------
	SCENE_TYPE GetNowScene() { return m_nowScene; }
	//------------------------------------------------------------------------------

private:

	// 各ポインタ
	PlayerBase *p_playerBase;
	ObjectBase *p_objectBase;
	Camera *p_camera;
	StageManager *p_stage;
	UIBase *p_uiBase;

	SCENE_TYPE m_nowScene;
};


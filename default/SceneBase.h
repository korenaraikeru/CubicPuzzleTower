//-----------------------------------------------------------------------------
// シーンベースクラス
//-----------------------------------------------------------------------------
#pragma once
#include <DxLib.h>
#include "Define.h"
#include "InputInfo.h"
#include "PlayerBase.h"
#include "ObjectBase.h"
#include "Camera.h"
#include "StageManager.h"
#include "UIBase.h"

#include "SceneControll.h"

class SceneBase
{
public:
	SceneBase();		// コンストラクタ
	~SceneBase();		// デストラクタ

	//---主要関数-------------------------------------------------------------------
	void Init();		// 初期化
	void Update();		// 更新
	void Draw();		// 描画
	//-----------------------------------------------------------------------------

private:
	SceneControll *p_sceneControll;
	
	SCENE_TYPE m_nowScene;			// 現在のシーン
};


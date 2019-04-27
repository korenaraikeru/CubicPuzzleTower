﻿//-----------------------------------------------------------------------------
// オブジェクトベースクラス
//-----------------------------------------------------------------------------
#include "ObjectBase.h"

//-----------------------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------------------
ObjectBase::ObjectBase()
{
	// 処理なし
}

//-----------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------
ObjectBase::~ObjectBase()
{
	// 処理なし
}

//-----------------------------------------------------------------------------
// 生成
//-----------------------------------------------------------------------------
void ObjectBase::Create()
{
	p_cube = new CubeControll();
	p_fieldObject = new FieldObjectManager();
}

//-----------------------------------------------------------------------------
// 削除
//-----------------------------------------------------------------------------
void ObjectBase::Delete()
{
	delete(p_cube);
	delete(p_fieldObject);
}

//-----------------------------------------------------------------------------
// 初期化
//-----------------------------------------------------------------------------
void ObjectBase::Init()
{
	p_cube->Init();
	p_fieldObject->Init();
}

//-----------------------------------------------------------------------------
// 更新
//-----------------------------------------------------------------------------
void ObjectBase::Update()
{
	p_cube->Update();
	p_fieldObject->Update();

	if (p_cube->GetIsClear())
	{
		p_fieldObject->SetIsRising(true);
	}
}

//-----------------------------------------------------------------------------
// 描画
//-----------------------------------------------------------------------------
void ObjectBase::Draw()
{
	p_cube->Draw();
	p_fieldObject->Draw();
}


// 次のステージへ行く際の変更処理
void ObjectBase::ChangeToNextStage(int n)
{
	p_cube->ChangeNextPos(n);
	p_fieldObject->Init();
}

//-----------------------------------------------------------------------------
// @brief  カメラクラス.
// 2016 Takeru Yui All Rights Reserved.
//-----------------------------------------------------------------------------
#pragma once

#include "DxLib.h"

class Camera
{
public:
	Camera();							// コンストラクタ.
	~Camera();							// デストラクタ.

	void TitleUpdate();
	void Update();	// 更新.

	// ポジションのgetter/setter.
	VECTOR GetPos() { return pos; }

private:
	VECTOR	pos;			// ポジション.

};
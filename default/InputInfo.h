//-----------------------------------------------------------------------------
// 入力情報管理関数
//-----------------------------------------------------------------------------
#pragma once
#include "DxLib.h"

#define INPUT_NUM 8

// 入力の種類
typedef enum INPUT_NAME_ENUM
{
	SHOT,
	START,
	DECISION,
	CANCEL,
	LEFT,
	RIGHT,
	UP,
	DOWN,
}INPUT_NAME_ENUM;

// 入力状態
typedef enum INPUT_STATE_ENUM
{
	OFF,
	PUSHDOWN,
	PRESSED,
	PULLUP,
}INPUT_STATE_ENUM;

void InitInput();									// 初期化
void UpdateInput();									// 更新
INPUT_STATE_ENUM GetInput(INPUT_NAME_ENUM name);	// パッドとキーボードの入力情報取得
VECTOR GetJoyAxis();								// スティックの入力情報取得

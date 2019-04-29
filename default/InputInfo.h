#pragma once
#include "DxLib.h"

#define INPUT_NUM 8

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

typedef enum INPUT_STATE_ENUM
{
	OFF,
	PUSHDOWN,
	PRESSED,
	PULLUP,
}INPUT_STATE_ENUM;

void InitInput();
void UpdateInput();
INPUT_STATE_ENUM GetInput(INPUT_NAME_ENUM name);
VECTOR GetJoyAxis();

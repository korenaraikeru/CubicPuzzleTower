//-----------------------------------------------------------------------------
// 入力情報管理関数
//-----------------------------------------------------------------------------
#include "InputInfo.h"
#include "DxLib.h"

INPUT_STATE_ENUM input[INPUT_NUM];
unsigned char padNum[INPUT_NUM];	// ゲームパッドの入力情報
unsigned char keyNum[INPUT_NUM];	// キーボードの入力情報

int joyX, joyY;						// スティックの入力情報

//-----------------------------------------------------------------------------
// 初期化
//-----------------------------------------------------------------------------
void InitInput()
{
	for (int i = 0; i < INPUT_NUM; i++)
	{
		input[i] = OFF;
	}
	padNum[0] = PAD_INPUT_1;
	padNum[1] = PAD_INPUT_8;
	padNum[2] = PAD_INPUT_1;
	padNum[3] = PAD_INPUT_2;
	padNum[4] = PAD_INPUT_LEFT;
	padNum[5] = PAD_INPUT_RIGHT;
	padNum[6] = PAD_INPUT_UP;
	padNum[7] = PAD_INPUT_DOWN;
	
	keyNum[0] = KEY_INPUT_SPACE;
	keyNum[1] = KEY_INPUT_RETURN;
	keyNum[2] = KEY_INPUT_SPACE;
	keyNum[3] = KEY_INPUT_C;
	keyNum[4] = KEY_INPUT_LEFT;
	keyNum[5] = KEY_INPUT_RIGHT;
	keyNum[6] = KEY_INPUT_UP;
	keyNum[7] = KEY_INPUT_DOWN;

	joyX = 0;
	joyY = 0;
}

//-----------------------------------------------------------------------------
// 更新
//-----------------------------------------------------------------------------
void UpdateInput()
{
	int nowInput = GetJoypadInputState(DX_INPUT_PAD1);
	GetJoypadAnalogInput(&joyX, &joyY, DX_INPUT_PAD1);
	joyY *= -1;

	for (int i = 0; i < INPUT_NUM; i++)
	{
		if (nowInput & padNum[i] == 1 || CheckHitKey(keyNum[i]) == 1)
		{
			if (input[i] == OFF)
			{
				input[i] = PUSHDOWN;
			}
			else if (input[i] == PUSHDOWN)
			{
				input[i] = PRESSED;
			}
		}
		else if (nowInput & padNum[i] == 0 || CheckHitKey(keyNum[i]) == 0)
		{
			if (input[i] == PUSHDOWN || input[i] == PRESSED)
			{
				input[i] = PULLUP;
			}
			else
			{
				input[i] = OFF;
			}
		}
	}

	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		joyX = -1000;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		joyX = 1000;
	}
	if (CheckHitKey(KEY_INPUT_UP))
	{
		joyY = 1000;
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		joyY = -1000;
	}
}

//-----------------------------------------------------------------------------
// Get関数
//-----------------------------------------------------------------------------
INPUT_STATE_ENUM GetInput(INPUT_NAME_ENUM name)
{
	return input[name];
}

VECTOR GetJoyAxis()
{
	VECTOR joyAxis = VGet((float)joyX, (float)joyY, 0.f);

	return joyAxis;
}

//-----------------------------------------------------------------------------
// プレイヤークラス.
//-----------------------------------------------------------------------------
#include "Player.h"
#include "Define.h"
#include <math.h>
#include "Inputkey.h"
#include "Scaffold.h"
#include "Cube.h"
#include "Sound.h"

#include "InputInfo.h"

//-----------------------------------------------------------------------------
// コンストラクタ.
//-----------------------------------------------------------------------------
Player::Player()
{
	// ３Ｄモデルの読み込み
	modelHandle = MV1LoadModel("data/model/slime.mqo");

	pos = VGet(0.f, -150.f, 120.f);
	dir = dir_back;
	angleY = 0.f;
	speed = 3.5f;

	Key = 0;
	Input = 0;
	inputX = 0;
	inputY = 0;

	joypad_flag = true;

	move_flag = false;
	shot_flag = false;
	return_flag = false;
	jump_flag = false;
	g = 0.3f;
	jump_accel = 4.f;
	jump_vec = 0;
	margin = 12;

	shot_cnt = 0;
	move_cnt = 0;
}

//-----------------------------------------------------------------------------
// デストラクタ.
//-----------------------------------------------------------------------------
Player::~Player()
{
	// モデルのアンロード.
	MV1DeleteModel(modelHandle);
}

void Player::Init()
{
	pos = VGet(0.f, -150.f, 120.f);
	vec = VGet(0, 0, 0);
	dir = dir_back;
	angleY = 0.0f;
	scaleX = 1.0f;
	scaleY = 1.0f;
	scaleZ = 1.0f;
	jump_vec = 0.0f;
	
	move_flag = false;
	shot_flag = false;
	return_flag = false;
	jump_flag = false;
	input_once = false;

	shot_cnt = 0;
	move_cnt = 0;
}

void Player::VectorControll()
{
	vec = VNorm(vec);

	vec.x = vec.x * speed;
	vec.z = vec.z * speed;

	pos = VAdd(pos, vec);
}

//-----------------------------------------------------------------------------
// 更新.
//-----------------------------------------------------------------------------
void Player::Update(const Cube& cube, const Scaf& scaf)
{
	if (getKey(KEY_INPUT_F1))
	{
		joypad_flag = true;
	}
	if (getKey(KEY_INPUT_F2))
	{
		joypad_flag = false;
	}

	if (!cube.clear_flag && pos.y >= -1)
	{
		if (joypad_flag)
		{
			Input = GetJoypadInputState(DX_INPUT_PAD1);
			GetJoypadAnalogInput(&inputX, &inputY, DX_INPUT_PAD1);

			if (!shot_flag)
			{
				if (GetJoyAxis().x != 0 || GetJoyAxis().y != 0)
				{
					/*vec.x = (float)inputX;
					vec.z = (float)-inputY;*/
					vec.x = GetJoyAxis().x;
					vec.z = GetJoyAxis().y;

					VectorControll();
					angleY = AngleCalculation((float)inputX, (float)inputY);
				}

				// 右上に入力していたら右斜め上に進む
				if ((Input & PAD_INPUT_UP) && (Input & PAD_INPUT_RIGHT))
				{
					dir = dir_f_right;
					move_flag = true;
				}
				// 左上に入力していたら左斜め上に進む
				else if ((Input & PAD_INPUT_UP) && (Input & PAD_INPUT_LEFT))
				{
					dir = dir_f_left;
					move_flag = true;
				}
				// 右下に入力していたら右斜め下に進む
				else if ((Input & PAD_INPUT_DOWN) && (Input & PAD_INPUT_RIGHT))
				{
					dir = dir_b_right;
					move_flag = true;
				}
				// 左下に入力していたら左斜め下に進む
				else if ((Input & PAD_INPUT_DOWN) && (Input & PAD_INPUT_LEFT))
				{
					dir = dir_b_left;
					move_flag = true;
				}
				// 上を押していたら上に進む
				else if (Input & PAD_INPUT_UP)
				{
					dir = dir_front;
					move_flag = true;
				}
				// 下を押していたら下に進む
				else if (Input & PAD_INPUT_DOWN)
				{
					dir = dir_back;
					move_flag = true;
				}
				// 右を押していたら右に進む
				else if (Input & PAD_INPUT_RIGHT)
				{
					dir = dir_right;
					move_flag = true;
				}
				// 左を押していたら左に進む
				else if (Input & PAD_INPUT_LEFT)
				{
					dir = dir_left;
					move_flag = true;
				}
				else
				{
					move_flag = false;
					move_cnt = 0;
				}
			}

			if (GetInput(SHOT) == PUSHDOWN && !jump_flag && !shot_flag && !move_flag
				&& !input_once)
			{
				shot_flag = true;
				prev_pos = pos;
				playSound(SE_SHOT);
			}
		}
		else
		{
			if (!shot_flag)
			{
				// 右上に入力していたら右斜め上に進む
				if (getKey(KEY_INPUT_UP) == KEY_STATE_PRESSED &&
					getKey(KEY_INPUT_RIGHT) == KEY_STATE_PRESSED)
				{
					pos.x += speed * VECTOR_SCALING;
					pos.z += speed * VECTOR_SCALING;
					dir = dir_f_right;
					angleY = -135.0f;
					move_flag = true;
				}
				// 左上に入力していたら左斜め上に進む
				else if (getKey(KEY_INPUT_UP) == KEY_STATE_PRESSED &&
					getKey(KEY_INPUT_LEFT) == KEY_STATE_PRESSED)
				{
					pos.x -= speed * VECTOR_SCALING;
					pos.z += speed * VECTOR_SCALING;
					dir = dir_f_left;
					angleY = 135.0f;
					move_flag = true;
				}
				// 右下に入力していたら右斜め下に進む
				else if (getKey(KEY_INPUT_DOWN) == KEY_STATE_PRESSED &&
					getKey(KEY_INPUT_RIGHT) == KEY_STATE_PRESSED)
				{
					pos.x += speed * VECTOR_SCALING;
					pos.z -= speed * VECTOR_SCALING;
					dir = dir_b_right;
					angleY = -45.0f;
					move_flag = true;
				}
				// 左下に入力していたら左斜め下に進む
				else if (getKey(KEY_INPUT_DOWN) == KEY_STATE_PRESSED &&
					getKey(KEY_INPUT_LEFT) == KEY_STATE_PRESSED)
				{
					pos.x -= speed * VECTOR_SCALING;
					pos.z -= speed * VECTOR_SCALING;
					dir = dir_b_left;
					angleY = 45.0f;
					move_flag = true;
				}
				// 上を押していたら上に進む
				else if (getKey(KEY_INPUT_UP) == KEY_STATE_PRESSED)
				{
					pos.z += speed;
					dir = dir_front;
					angleY = 180.0f;
					move_flag = true;
				}
				// 下を押していたら下に進む
				else if (getKey(KEY_INPUT_DOWN) == KEY_STATE_PRESSED)
				{
					pos.z -= speed;
					dir = dir_back;
					angleY = 0.0f;
					move_flag = true;
				}
				// 右を押していたら右に進む
				else if (getKey(KEY_INPUT_RIGHT) == KEY_STATE_PRESSED)
				{
					pos.x += speed;
					dir = dir_right;
					angleY = -90.0f;
					move_flag = true;
				}
				// 左を押していたら左に進む
				else if (getKey(KEY_INPUT_LEFT) == KEY_STATE_PRESSED)
				{
					pos.x -= speed;
					angleY = 90.0f;
					move_flag = true;
				}
				else
				{
					move_flag = false;
					move_cnt = 0;
				}
			}

			if (GetInput(SHOT) == PUSHDOWN && !jump_flag && !shot_flag)
			{
				shot_flag = true;
				prev_pos = pos;
				playSound(SE_SHOT);
			}
		}
	}
	//動いている間カウントする
	if (move_flag)
		move_cnt++;

	// 操作していないときは内側を向かせる
	if (!move_flag)
	{
		if (pos.x > -105 && pos.x < 105)
		{
			if (pos.z < 0)
			{
				dir = dir_front;
				angleY = 180.0f;
			}
			else
			{
				dir = dir_back;
				angleY = 0.0f;
			}
		}
		else if (pos.z > -105 && pos.z < 105)
		{
			if (pos.x < 0)
			{
				dir = dir_right;
				angleY = -90.0f;
			}
			else
			{
				dir = dir_left;
				angleY = 90.0f;
			}
		}
	}

	// ショット処理
	if (shot_flag)
	{
		Shot();
	}

	ScaleChange(scaf.GetPos().y);

	//ジャンプ処理
	if (!jump_flag && move_flag && move_cnt > 20 && !shot_flag)
	{
		jump_flag = true;
		jump_vec = jump_accel;
		playSound(SE_JUMP);
	}
	if (jump_flag)
	{
		pos.y = pos.y + jump_vec;
		jump_vec = jump_vec - g;
	}

	// 着地処理
	if (pos.y < scaf.GetPos().y)
	{
		pos.y = scaf.GetPos().y;
		jump_flag = false;
	}

	//当たり判定
	if (!shot_flag)
	{
		if (pos.x - margin < 105 && pos.x + margin > -105)
		{
			if (pos.z + margin > -110 && pos.z < 105)
				pos.z = -110 - margin;
			if (pos.z - margin < 110 && pos.z > -105)
				pos.z = 110 + margin;
		}
		if (pos.z - margin < 105 && pos.z + margin > -105)
		{
			if (pos.x + margin > -110 && pos.x < 105)
				pos.x = -110 - margin;
			if (pos.x - margin < 110 && pos.x > -105)
				pos.x = 110 + margin;
		}
		if (pos.x - margin < -140)
			pos.x = -140 + margin;
		if (pos.x + margin > 140)
			pos.x = 140 - margin;
		if (pos.z - margin < -140)
			pos.z = -140 + margin;
		if (pos.z + margin > 140)
			pos.z = 140 - margin;
	}

	// ３Dモデルのポジション設定
	MV1SetPosition(modelHandle, pos);

	// ３Dモデルの回転角設定
	MV1SetRotationXYZ(modelHandle, VGet(0.0f, angleY / 180.0f * DX_PI_F, 0.0f));

	MV1SetScale(modelHandle, VGet(scaleX, scaleY, scaleZ));
}

float Player::AngleCalculation(float x, float y)
{
	VECTOR vec = VGet(0,0,0);
	float angle = 0;
	vec.x = x;
	vec.z = y;
	vec = VNorm(vec);

	angle = (float)atan2((double)vec.z, (double)vec.x) * 180.0f / DX_PI_F;
	angle -= 90.0f;

	return angle;
}

//ショット処理
void Player::Shot()
{
	if (shot_flag && !return_flag)
	{
		if (shot_cnt > 3)
			return_flag = true;
		shot_cnt++;
		if (dir == dir_front)
		{
			pos.z += 3;
		}
		else if (dir == dir_back)
		{
			pos.z -= 3;
		}
		else if (dir == dir_left)
		{
			pos.x -= 3;
		}
		else if (dir == dir_right)
		{
			pos.x += 3;
		}
	}
	
	if (return_flag)
	{
		if (pos.x == prev_pos.x && pos.z == prev_pos.z)
		{
			return_flag = false;
			shot_flag = false;
			shot_cnt = 0;
		}
		if (dir == dir_front)
			pos.z -= 1;
		else if (dir == dir_back)
			pos.z += 1;
		else if (dir == dir_left)
			pos.x += 1;
		else if (dir == dir_right)
			pos.x -= 1;
	}
}

void Player::ScaleChange(float scaf_y)
{
	// 動いていないときに大きさが変わっていたら元の大きさまで戻す
	if (!move_flag && !jump_flag)
	{
		if (scaleX > 1)
			scaleX -= 0.1f;
		if (scaleY < 1)
			scaleY += 0.1f;
		if (scaleZ > 1)
			scaleZ -= 0.1f;
	}
	// 動いてるときジャンプするまで縮める
	if (move_flag && !jump_flag)
	{
		scaleX += 0.01f;
		scaleY -= 0.01f;
		scaleZ += 0.01f;
	}

	if (jump_flag)
	{
		// 着地する直前に全力でつぶす
		if (jump_vec < 0 && pos.y < scaf_y + 5)
		{
			scaleX += 0.2f;
			scaleY -= 0.2f;
			scaleZ += 0.2f;
		}
		// 浮いている間は少しずつ細くする
		else if (scaleY < 1.f)
		{
			scaleX -= 0.1f;
			scaleY += 0.1f;
			scaleZ -= 0.1f;
		}
	}
}

//-----------------------------------------------------------------------------
// 描画.
//-----------------------------------------------------------------------------
void Player::Draw()
{
	// ３Ｄモデルの描画
	MV1DrawModel(modelHandle);
}
//-----------------------------------------------------------------------------
// プレイヤークラス.
//-----------------------------------------------------------------------------
#pragma once

#include "DxLib.h"

class Cube;
class Scaf;

class Player
{
public:
	Player();				// コンストラクタ.
	~Player();				// デストラクタ.

	void Init();
	void VectorControll();
	void Update(const Cube& cube, const Scaf& scaf);			// 更新.
	void Draw();			// 描画.

	// モデルハンドルの取得.
	//int GetModelHandle() { return modelHandle; }

	// ポジションのgetter/setter.
	const VECTOR& GetPos() const { return pos; }
	const int GetDir() const { return dir; }
	const float GetAngle() const { return angleY; }
	const VECTOR GetScale() const { return VGet(scaleX, 0.f, scaleZ); }
	void SetPos(const VECTOR set) { pos = set; }
	float AngleCalculation(float x, float y);

	VECTOR	pos, vec;		// ポジション.

	const bool SlideStart() const { if (shot_cnt > 1) return true; else return false;}
private:
	void Shot();
	void ScaleChange(float scaf_y);

	int	modelHandle;	// モデルハンドル.

	int dir;			//向き
	float angleY;		//回転角
	float scaleX;
	float scaleY;
	float scaleZ;
	float speed;
	bool move_flag;
	bool shot_flag;
	bool return_flag;
	bool jump_flag;
	float jump_vec;
	float g;
	float jump_accel;
	float margin;

	VECTOR prev_pos;
	int shot_cnt;
	int move_cnt;

	int Key;
	int Input;
	int inputX, inputY;	//アナログパッドの入力状態
	bool joypad_flag;
	bool input_once;
};
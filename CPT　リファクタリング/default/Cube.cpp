#include "Cube.h"
#include "Map.h"
#include "State.h"
#include "Define.h"
#include "Inputkey.h"
#include "Player.h"
#include "Sound.h"

Cube::Cube()
{
	speed = 3.f;
	cube_move = false;
	clear_flag = false;
	size = 30;
	now_stage = 1;
	range = 20;

	reset_flag = false;

	modelHandle = MV1LoadModel("data/model/cube.mqo");
	modelHandle_dir = MV1LoadModel("data/model/dir.mqo");

	squares_pos[0] = VGet(-90, 0, 90);
	squares_pos[1] = VGet(-60, 0, 90);
	squares_pos[2] = VGet(-30, 0, 90);
	squares_pos[3] = VGet(0, 0, 90);
	squares_pos[4] = VGet(30, 0, 90);
	squares_pos[5] = VGet(60, 0, 90);
	squares_pos[6] = VGet(90, 0, 90);
	squares_pos[7] = VGet(-90, 0, 60);
	squares_pos[8] = VGet(-60, 0, 60);
	squares_pos[9] = VGet(-30, 0, 60);
	squares_pos[30] = VGet(0, 0, 60);
	squares_pos[11] = VGet(30, 0, 60);
	squares_pos[12] = VGet(60, 0, 60);
	squares_pos[13] = VGet(90, 0, 60);
	squares_pos[14] = VGet(-90, 0, 30);
	squares_pos[15] = VGet(-60, 0, 30);
	squares_pos[16] = VGet(-30, 0, 30);
	squares_pos[17] = VGet(0, 0, 30);
	squares_pos[18] = VGet(30, 0, 30);
	squares_pos[19] = VGet(60, 0, 30);
	squares_pos[20] = VGet(90, 0, 30);
	squares_pos[21] = VGet(-90, 0, 0);
	squares_pos[22] = VGet(-60, 0, 0);
	squares_pos[23] = VGet(-30, 0, 0);
	squares_pos[24] = VGet(0, 0, 0);
	squares_pos[25] = VGet(30, 0, 0);
	squares_pos[26] = VGet(60, 0, 0);
	squares_pos[27] = VGet(90, 0, 0);
	squares_pos[28] = VGet(-90, 0, -30);
	squares_pos[29] = VGet(-60, 0, -30);
	squares_pos[30] = VGet(-30, 0, -30);
	squares_pos[31] = VGet(0, 0, -30);
	squares_pos[32] = VGet(30, 0, -30);
	squares_pos[33] = VGet(60, 0, -30);
	squares_pos[34] = VGet(90, 0, -30);
	squares_pos[35] = VGet(-90, 0, -60);
	squares_pos[36] = VGet(-60, 0, -60);
	squares_pos[37] = VGet(-30, 0, -60);
	squares_pos[38] = VGet(0, 0, -60);
	squares_pos[39] = VGet(30, 0, -60);
	squares_pos[40] = VGet(60, 0, -60);
	squares_pos[41] = VGet(90, 0, -60);
	squares_pos[42] = VGet(-90, 0, -90);
	squares_pos[43] = VGet(-60, 0, -90);
	squares_pos[44] = VGet(-30, 0, -90);
	squares_pos[45] = VGet(0, 0, -90);
	squares_pos[46] = VGet(30, 0, -90);
	squares_pos[47] = VGet(60, 0, -90);
	squares_pos[48] = VGet(90, 0, -90);

	dir_pos[0] = VGet(-90, 0.5, 105);
	dir_pos[1] = VGet(-60, 0.5, 105);
	dir_pos[2] = VGet(-30, 0.5, 105);
	dir_pos[3] = VGet(0, 0.5, 105);
	dir_pos[4] = VGet(30, 0.5, 105);
	dir_pos[5] = VGet(60, 0.5, 105);
	dir_pos[6] = VGet(90, 0.5, 105);
	dir_pos[7] = VGet(105, 0.5, 90);
	dir_pos[8] = VGet(105, 0.5, 60);
	dir_pos[9] = VGet(105, 0.5, 30);
	dir_pos[10] = VGet(105, 0.5, 0);
	dir_pos[11] = VGet(105, 0.5, -30);
	dir_pos[12] = VGet(105, 0.5, -60);
	dir_pos[13] = VGet(105, 0.5, -90);
	dir_pos[14] = VGet(90, 0.5, -105);
	dir_pos[15] = VGet(60, 0.5, -105);
	dir_pos[16] = VGet(30, 0.5, -105);
	dir_pos[17] = VGet(0, 0.5, -105);
	dir_pos[18] = VGet(-30, 0.5, -105);
	dir_pos[19] = VGet(-60, 0.5, -105);
	dir_pos[20] = VGet(-90, 0.5, -105);
	dir_pos[21] = VGet(-105, 0.5, -90);
	dir_pos[22] = VGet(-105, 0.5, -60);
	dir_pos[23] = VGet(-105, 0.5, -30);
	dir_pos[24] = VGet(-105, 0.5, 0);
	dir_pos[25] = VGet(-105, 0.5, 30);
	dir_pos[26] = VGet(-105, 0.5, 60);
	dir_pos[27] = VGet(-105, 0.5, 90);

	for (int i = 0; i < 9; i++) {
		cube_pos[i] = squares_pos[next_pos[i]];
	}

	sq_startPoint.x = -90;
	sq_endPoint.x = 90;
	sq_startPoint.y = 0;
	sq_endPoint.y = 0;
	sq_startPoint.z = 90;
	sq_endPoint.z = -90;
}

Cube::~Cube()
{
	// モデルのアンロード.
	MV1DeleteModel(modelHandle);
}

//初期化
void Cube::Init()
{
	for (int i = 0; i < 9; i++)
	{
		pos[i] = squares_pos[next_pos[i]];
		slide_flag[i] = false;
		fit_cube[i] = false;
		hit_flag[i] = false;
	}

	cube_move = false;
	clear_flag = false;
	reset_flag = false;
	next_flag = false;
	support_flag = false;
	wait_cnt = 0;

	p_pos = VGet(0, 0, 0);
	p_dir = 0;
	now_stage = 1;

	support_num = 0;
}

//アップデート
void Cube::Update(const Player& player)
{
	//プレイヤーの位置と向きを取得
	p_pos = player.GetPos();
	p_dir = player.GetDir();

	for (int i = 0; i < 9; i++)
	{
		//スペースを押したときプレイヤーがキューブの側面にいたらスライドフラグをtrueにして動かす向きを決める
		if (player.SlideStart() && slide_flag[i] == false)
		{
			//左右の側面かどうか
			if (p_pos.z > pos[i].z - size / 2 && p_pos.z < pos[i].z + size / 2)
			{
				if ((p_pos.x + range > pos[i].x - size / 2 && p_pos.x + range < pos[i].x + size / 2 &&
						p_dir == dir_right) ||
					(p_pos.x - range < pos[i].x + size / 2 && p_pos.x - range > pos[i].x - size / 2 &&
						p_dir == dir_left))
				{
					slide_flag[i] = true;
					if (p_dir == dir_right)
						slide_dir = dir_right;
					else
						slide_dir = dir_left;
				}
			}
			//前後の側面かどうか
			if (p_pos.x > pos[i].x - size / 2 && p_pos.x < pos[i].x + size / 2)
			{
				if ((p_pos.z - range < pos[i].z + size / 2 && p_pos.z - range > pos[i].z - size / 2 &&
						p_dir == dir_back) ||
					(p_pos.z + range > pos[i].z - size / 2 && p_pos.z + range < pos[i].z + size / 2 &&
						p_dir == dir_front))
				{
					slide_flag[i] = true;
					if (p_dir == dir_back)
						slide_dir = dir_back;
					else
						slide_dir = dir_front;
				}
			}

			//隣接しているキューブがあるなら、そのキューブのスライドフラグもtrueにする
			if (slide_flag[i])
			{
				for (int j = 0; j < 9; j++)
				{
					if (i == j)
						j++;
					if ((pos[j].x + size / 2 == pos[i].x - size / 2 && pos[j].z == pos[i].z && slide_dir == dir_left) ||
						(pos[j].x - size / 2 == pos[i].x + size / 2 && pos[j].z == pos[i].z && slide_dir == dir_right) ||
						(pos[j].x == pos[i].x && pos[j].z - size / 2 == pos[i].z + size / 2 && slide_dir == dir_front) ||
						(pos[j].x == pos[i].x && pos[j].z + size / 2 == pos[i].z - size / 2 && slide_dir == dir_back))
						slide_flag[j] = true;
				}
			}
		}

		//スライドフラグがtrueならキューブを動かす
		if (slide_flag[i])
		{
			cube_move = true;
			if (slide_dir == dir_left)//左
				pos[i].x -= speed;
			if (slide_dir == dir_right)//右
				pos[i].x += speed;
			if (slide_dir == dir_front)//前
				pos[i].z += speed;
			if (slide_dir == dir_back)//後
				pos[i].z -= speed;
		}

		//キューブ同士が衝突したり枠外に出そうになったら止める
		if (HitJudge())
		{
			slide_flag[i] = false;
			cube_move = false;
			playSound(SE_CUBEHIT);
			hit_flag[i] = true;
		}
		else
		{
			hit_flag[i] = false;
		}

		if (pos[i].x < 45 && pos[i].x > -45 && pos[i].z < 45 && pos[i].z > -45)
			fit_cube[i] = true;
		else
			fit_cube[i] = false;
	}

	ShotSupport();

	//赤い枠内に全部入ったらクリアフラグをtrueにする
	int cnt = 0;
	for (int i = 0; i < 9; i++)
	{
		if (fit_cube[i] == true)
			cnt++;
		if (cnt == 9 && cube_move == false && !next_flag)
		{
			next_flag = true;
			playSound(SE_CLEAR);
		}
	}
	if (next_flag && !clear_flag)
	{
		wait_cnt++;
		if (wait_cnt > 50)
			clear_flag = true;
	}

	if (getKey(KEY_INPUT_Z) == KEY_STATE_PUSHDOWN && reset_flag == false)
	{
		reset_flag = true;
	}
	if (getKey(KEY_INPUT_Z) == KEY_STATE_PULLUP)
	{
		reset_flag = false;
	}
	if (reset_flag)
	{
		Reset();
	}
}

//描画
void Cube::Draw()
{
	for (int i = 0; i < 9; i++)
	{
		// ３Dモデルのポジション設定
		MV1SetPosition(modelHandle, pos[i]);
		// ３Ｄモデルの描画
		MV1DrawModel(modelHandle);
	}

	if (!clear_flag && p_pos.y >= 0 && support_flag)
	{
		for (int i = 0; i < 28; i++)
		{
			if (support_num == i)
			{
				MV1SetPosition(modelHandle_dir, dir_pos[i]);

				if (i >= 7 && i <= 13)
					MV1SetRotationXYZ(modelHandle_dir, VGet(0.0f, 90.0f / 180.0f * DX_PI_F, 0.0f));
				else if (i >= 14 && i <= 20)
					MV1SetRotationXYZ(modelHandle_dir, VGet(0.0f, 180.0f / 180.0f * DX_PI_F, 0.0f));
				else if (i >= 21 && i <= 27)
					MV1SetRotationXYZ(modelHandle_dir, VGet(0.0f, -90.0f / 180.0f * DX_PI_F, 0.0f));
				else
					MV1SetRotationXYZ(modelHandle_dir, VGet(0.0f, 0.0f / 180.0f * DX_PI_F, 0.0f));

				MV1DrawModel(modelHandle_dir);
			}
		}
	}
}

//マス目の端との当たり判定とキューブ同士の当たり判定
int Cube::HitJudge()
{
	bool hit = false;

	for (int i = 0; i < 9; i++) {
		//マス目の端との判定
		if (pos[i].x < sq_startPoint.x || pos[i].x > sq_endPoint.x ||
			pos[i].z < sq_endPoint.z || pos[i].z > sq_startPoint.z)
		{
			hit = true;
			if (slide_dir == dir_left)
				pos[i].x += speed;
			if (slide_dir == dir_right)
				pos[i].x -= speed;
			if (slide_dir == dir_front)
				pos[i].z -= speed;
			if (slide_dir == dir_back)
				pos[i].z += speed;
		}
		//キューブ同士の判定
		for (int j = 0; j < 9; j++)
		{
			//同じキューブは判定しない
			if (i == j)
				j++;
			
			if (pos[i].x < pos[j].x + size && pos[j].x < pos[i].x + size &&
				pos[i].z < pos[j].z + size && pos[j].z < pos[i].z + size &&
				slide_flag[j] == false)
			{
				hit = true;
				if (slide_dir == dir_left)
					pos[i].x = pos[j].x + size;
				if (slide_dir == dir_right)
					pos[i].x = pos[j].x - size;
				if (slide_dir == dir_front)
					pos[i].z = pos[j].z - size;
				if (slide_dir == dir_back)
					pos[i].z = pos[j].z + size;
			}
		}
	}

	return hit;
}

void Cube::ShotSupport()
{
	if (p_pos.z > 105 || p_pos.z < -105)
	{
		for (int i = 0; i < 7; i++)
		{
			if (p_pos.x > -105 + i * 30 && p_pos.x < -75 + i * 30)
			{
				if (p_pos.z > 105)
					support_num = i;
				else
					support_num = 20 - i;
			}
		}
	}
	else if (p_pos.x > 105 || p_pos.x < -105)
	{
		for (int i = 0; i < 7; i++)
		{
			if (p_pos.z < 105 - i * 30 && p_pos.z > 75 - i * 30)
			{
				if (p_pos.x > 105)
					support_num = i + 7;
				else
					support_num = 27 - i;
			}
		}
	}

	if ((p_pos.x > -105 && p_pos.x < 105 && 
		((p_pos.z > 0 && p_pos.z < 140) || (p_pos.z < 0 && p_pos.z > -140))) ||
		(p_pos.z > -105 && p_pos.z < 105 &&
		((p_pos.x > 0 && p_pos.x < 140) || (p_pos.x < 0 && p_pos.x > -140))))
		support_flag = true;
	else
		support_flag = false;
}

//ステージ更新処理
void Cube::ChangeStage(int stage_num)
{
	for (int i = 0; i < 9; i++) {
		pos[i] = squares_pos[next_pos[i + (stage_num - 1) * 9]];
		slide_flag[i] = false;
		fit_cube[i] = false;
	}
	now_stage = stage_num;
	clear_flag = false;
	next_flag = false;
	wait_cnt = 0;
}

void Cube::Reset()
{
	for (int i = 0; i < 9; i++) {
		pos[i] = squares_pos[next_pos[i + (now_stage - 1) * 9]];
		slide_flag[i] = false;
		fit_cube[i] = false;
	}
}

void Cube::MissCheck()
{
	
}


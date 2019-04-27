#include "GameManager.h"

State::State()
{
	game_state = TITLE;
	stage_num = 1;
	next_flag = false;
	init_flag = false;
	alpha = 0;
	menu_num = 0;
	graph_pause = LoadGraph("data/pause.png");
	graph_reset = LoadGraph("data/reset.png");
	graph_return = LoadGraph("data/return.png");
	graph_close = LoadGraph("data/close.png");
}

State::~State()
{
	InitSoundMem();
}

void State::Init()
{
	stage_num = 1;
	next_flag = false;
	return_flag = false;
	init_flag = false;
	alpha = 0;
	menu_num = 0;
	input_once = false;
}

void State::Update(Player &player, Cube &cube, Scaf& scaf, Title& title, Select& select)
{
	if (init_flag)
	{
		init_flag = false;
	}

	if (game_state == TITLE)
	{
		playSound(BGM_TITLE);
		if ((getKey(KEY_INPUT_RETURN) == KEY_STATE_PUSHDOWN || getPad(PAD_INPUT_8)) 
			&& !next_flag)
		{
			next_flag = true;
			playSound(SE_START);
		}
		if (next_flag)
		{
			alpha += 3;

			if (alpha >= 255)
			{
				next_flag = false;
				game_state = SELECT;
				stopSound(BGM_TITLE);
				resetSound(BGM_TITLE);
			}
		}
		else
		{
			alpha = 0;
		}
	}
	else if (game_state == SELECT)
	{
		playSound(BGM_SELECT);
		if ((getKey(KEY_INPUT_SPACE) == KEY_STATE_PUSHDOWN || getPad(PAD_INPUT_1))
			&& !next_flag)
		{
			next_flag = true;
			playSound(SE_DECISION);
		}
		if (getKey(KEY_INPUT_C) == KEY_STATE_PUSHDOWN || getPad(PAD_INPUT_2))
		{
			return_flag = true;
			playSound(SE_CANCEL);
			resetSound(BGM_TITLE);
		}

		if (next_flag)
		{
			alpha += 15;

			if (alpha >= 255)
			{
				next_flag = false;
				game_state = PLAY;
				if (select.GetLevel() == easy)
					stage_num = 1;
				if (select.GetLevel() == normal)
					stage_num = 4;
				if (select.GetLevel() == hard)
					stage_num = 7;
				if (select.GetLevel() == extra)
					stage_num = 10;

				cube.ChangeStage(stage_num);
				stopSound(BGM_SELECT);
				resetSound(BGM_SELECT);
			}
		}
		else if (return_flag)
		{
			alpha += 25;

			if (alpha >= 255)
			{
				return_flag = false;
				game_state = TITLE;
				title.Init();
				select.Init();
				stopSound(BGM_SELECT);
				resetSound(BGM_SELECT);
			}
		}
		else
		{
			if (alpha > 0)
				alpha -= 15;
			if (alpha < 0)
				alpha = 0;
		}
	}
	else if (game_state == PLAY)
	{
		if (alpha > 20)
			playSound(BGM_PLAY);
		if ((getKey(KEY_INPUT_RETURN) == KEY_STATE_PUSHDOWN || getPad(PAD_INPUT_8)) &&
			alpha == 0)
		{
			game_state = PAUSE;
			menu_num = 0;
			playSound(SE_PAUSE);
			stopSound(BGM_PLAY);
		}
		else
			input_once = false;

		if (cube.clear_flag)
		{
			player.pos.y += 2;
			alpha += 5;
			if (alpha >= 255)
			{
				if (stage_num < 12)
				{
					stage_num += 1;
					player.Init();
					cube.ChangeStage(stage_num);
					scaf.Init();
				}
				else if (stage_num == 12)
				{
					game_state = CLEAR;
					stopSound(BGM_PLAY);
					resetSound(BGM_PLAY);
				}
			}
		}
		else
		{
			if (alpha > 0)
				alpha -= 5;
		}
	}
	else if (game_state == PAUSE)
	{
		if ((getKey(KEY_INPUT_DOWN) == KEY_STATE_PUSHDOWN || getPad(PAD_INPUT_DOWN)) &&
			!input_once)
		{
			input_once = true;
			if (menu_num == 2)
				menu_num = 0;
			else
				menu_num++;
			playSound(SE_CURSOR);
		}
		else if ((getKey(KEY_INPUT_UP) == KEY_STATE_PUSHDOWN || getPad(PAD_INPUT_UP)) &&
			!input_once)
		{
			input_once = true;
			if (menu_num == 0)
				menu_num = 2;
			else
				menu_num--;
			playSound(SE_CURSOR);
		}
		else if (getPad(PAD_INPUT_DOWN) == 0 && getPad(PAD_INPUT_UP) == 0)
			input_once = false;

		if (getKey(KEY_INPUT_RETURN) == KEY_STATE_PUSHDOWN || getPad(PAD_INPUT_8))
		{
			menu_num = 2;
			next_flag = true;
			playSound(SE_CANCEL);
		}

		if ((getKey(KEY_INPUT_SPACE) == KEY_STATE_PUSHDOWN || getPad(PAD_INPUT_1)) 
			&& !next_flag)
		{
			next_flag = true;
			if (menu_num == 2)
				playSound(SE_CANCEL);
			else
				playSound(SE_DECISION);
		}
		if (next_flag)
		{
			if (menu_num == 0)
			{
				alpha += 25;

				if (alpha >= 255)
				{
					next_flag = false;
					game_state = PLAY;
					cube.Reset();
					player.Init();
					playSound(BGM_PLAY);
				}
			}
			else if (menu_num == 1)
			{
				alpha += 15;

				if (alpha >= 255)
				{
					next_flag = false;
					game_state = TITLE;
					init_flag = true;
					Init();
					title.Init();
					player.Init();
					scaf.Init();
					cube.Init();
					alpha = 0;
					resetSound(BGM_PLAY);
				}
			}
			else
			{
				next_flag = false;
				game_state = PLAY;
				alpha = 0;
				playSound(BGM_PLAY);
			}
		}
	}
	else if (game_state == CLEAR)
	{
		playSound(BGM_ALLCLEAR);
		if ((getKey(KEY_INPUT_SPACE) == KEY_STATE_PUSHDOWN || 
			getPad(PAD_INPUT_1) || getPad(PAD_INPUT_8)) && !next_flag)
		{
			next_flag = true;
		}
		if (next_flag)
		{
			alpha += 15;

			if (alpha >= 255)
			{
				next_flag = false;
				game_state = TITLE;
				init_flag = true;
				Init();
				alpha = 0;
				stopSound(BGM_ALLCLEAR);
				resetSound(BGM_ALLCLEAR);
			}
		}
		else
		{
			if (alpha > 0)
				alpha -= 15;
			if (alpha < 0)
				alpha = 0;
		}
	}
}

void State::Draw()
{
	if (game_state == PAUSE)
	{
		DrawGraph(0, 0, graph_pause, TRUE);

		SetDrawBright(120, 120, 120);
		if (menu_num == 0)
		{
			SetDrawBright(255, 255, 255);
		}
		DrawGraph(0, 0, graph_reset, TRUE);
		SetDrawBright(120, 120, 120);

		if (menu_num == 1)
		{
			SetDrawBright(255, 255, 255);
		}
		DrawGraph(0, 0, graph_return, TRUE);
		SetDrawBright(120, 120, 120);

		if (menu_num == 2)
		{
			SetDrawBright(255, 255, 255);
		}
		DrawGraph(0, 0, graph_close, TRUE);
		SetDrawBright(255, 255, 255);
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

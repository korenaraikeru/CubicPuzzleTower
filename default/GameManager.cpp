#include "GameManager.h"



GameManager::GameManager()
{
	Create();
}


GameManager::~GameManager()
{
	Delete();
}

void GameManager::Create()
{
	player = new Player();	// プレイヤーを生成
	shadow = new Shadow();	// 影を生成
	cube = new Cube();		// キューブを生成
	camera = new Camera();	// カメラを生成
	map = new Map();		// マップを生成
	mini = new miniMap();	// ミニマップを生成
	scaf = new Scaf();		// 足場を生成
	state = new State();	// ステートを生成
	title = new Title();	// タイトルを生成
	select = new Select();	// セレクトを生成
	clear = new Clear();	// クリアを生成
	ui = new UI();			// UIを生成
}

void GameManager::Delete()
{
	delete(player);	// プレイヤーを削除
	delete(shadow);	// 影を削除
	delete(cube);	// キューブを削除
	delete(camera);	// カメラを削除
	delete(map);	// マップを削除
	delete(mini);	// ミニマップを削除
	delete(scaf);	// 足場を削除
	delete(state);	// ステートを削除
	delete(title);	// タイトルを削除
	delete(select);	// セレクトを削除
	delete(clear);	// クリアを削除
	delete(ui);		// UIを削除
	deleteSound();	// 音データを削除
}

void GameManager::Init()
{
	//キー入力判定処理の初期化
	InitKeyInput();
	initKey();

	InitInput();

	state->Init();

	player->Init();

	cube->Init();

	scaf->Init();

	shadow->Init();

	title->Init();

	select->Init();

	clear->Init();

	mini->Init(*cube);

	ui->Init();

	loadSound();

}

//----------------------
// アップデート関数
//----------------------
void GameManager::Update()
{
	updateKey();//キー入力

	UpdateInput();

	if (state->game_state == TITLE)
	{
		camera->TitleUpdate();

		title->Update();

		shadow->TitleUpdate(*title);
	}
	if (state->game_state == SELECT)
	{
		select->Update();
	}
	if (state->game_state == PLAY)
	{
		// プレイヤー制御.
		player->Update(*cube, *scaf);

		// カメラ制御.
		camera->Update();

		cube->Update(*player);

		shadow->Update(*player, *scaf);

		scaf->Update(*cube);

		mini->Update(*player, *cube);

		ui->Update(*state);
	}
	if (state->game_state == CLEAR)
	{
		clear->Update();
	}
	state->Update(*player, *cube, *scaf, *title, *select);

	if (state->GetInitFlag())
	{
		Init();
	}
}

//----------------------
// 描画関数
//----------------------
void GameManager::Draw()
{
	if (state->game_state == TITLE)
	{
		title->Draw();

		shadow->Draw();
	}
	if (state->game_state == SELECT)
	{
		select->Draw();
	}
	if (state->game_state == PLAY || state->game_state == PAUSE)
	{
		map->Draw();

		// プレイヤー描画.
		player->Draw();

		cube->Draw();

		shadow->Draw();

		scaf->Draw();

		mini->Draw();

		ui->Draw();

		//effect->Draw();
	}
	if (state->game_state == CLEAR)
	{
		clear->Draw();
	}
	state->Draw();
}

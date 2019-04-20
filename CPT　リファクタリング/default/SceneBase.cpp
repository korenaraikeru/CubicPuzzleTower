//
#include "SceneBase.h"
#include "Sound.h"


SceneBase::SceneBase()
{
	// ˆ—‚È‚µ
}


SceneBase::~SceneBase()
{
	// ˆ—‚È‚µ
}

void SceneBase::Create()
{
	p_camera = new Camera();

	p_player = new PlayerManager();

	p_mapObject = new MapObjectManager();

	p_stage = new StageManager();
}

void SceneBase::Delete()
{
	delete(p_camera);
	delete(p_player);
	delete(p_mapObject);
	delete(p_stage);
	deleteSound();
}

void SceneBase::Init()
{
	nowScene = PLAY;

	InitInput();

	p_player->Init();

	p_mapObject->Init();

	p_stage->Init();

	loadSound();
}

void SceneBase::Update()
{
	UpdateInput();

	p_camera->Update();

	p_player->SetFloorPos(p_mapObject->GetFloorPos());
	p_player->Update();

	p_mapObject->SetPlayerPos(p_player->GetPlayerPos());
	p_mapObject->Update();

	p_stage->Update();

	StateChange();
}

void SceneBase::Draw()
{
	if (nowScene == PLAY || nowScene == NEXT)
	{
		p_player->Draw();

		p_mapObject->Draw();

		p_stage->Draw();
	}
}

void SceneBase::StateChange()
{
	if (nowScene == PLAY)
	{
		if (p_mapObject->GetIsEndRising())
		{
			p_player->SetIsCanMove(true);

			if (p_player->GetIsGround())
			{
				p_mapObject->SetIsCanShot(true);
			}
			else
			{
				p_mapObject->SetIsCanShot(false);
			}
		}
		else
		{
			p_player->SetIsCanMove(false);

			p_mapObject->SetIsCanShot(false);
		}

		if (p_mapObject->GetIsClear())
		{
			p_stage->SetIsNext(true);
			nowScene = NEXT;
		}
	}
	if (nowScene == NEXT)
	{
		if (p_stage->GetIsChange())
		{
			p_player->Init();
			p_mapObject->NextStage(p_stage->GetNowStageNum());
			nowScene = PLAY;
		}
	}
}

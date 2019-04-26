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
	p_characterBase = new CharacterBase();
	p_characterBase->Create();

	p_objectBase = new ObjectBase();
	p_objectBase->Create();

	p_camera = new Camera();

	p_stage = new StageManager();

	p_ui = new UIManager();
}

void SceneBase::Delete()
{
	p_characterBase->Delete();
	delete(p_characterBase);

	p_objectBase->Delete();
	delete(p_objectBase);

	delete(p_camera);
	delete(p_stage);
	delete(p_ui);
	deleteSound();
}

void SceneBase::Init()
{
	nowScene = PLAY;

	InitInput();

	p_characterBase->Init();

	p_objectBase->Init();

	p_stage->Init();

	p_ui->Init();

	loadSound();
}

void SceneBase::Update()
{
	UpdateInput();

	p_characterBase->SetFloorPosToPlayer(p_objectBase->GetFloorPos());
	p_characterBase->Update();

	p_camera->Update();

	p_objectBase->SetPlayerPosToCube(p_characterBase->GetPlayerPos());
	p_objectBase->Update();

	p_stage->Update();

	p_ui->Update();

	for (int i = 0; i < 9; i++)
	{
		p_ui->SetMiniMapInfo(i, p_objectBase->GetCubePos(i), p_characterBase->GetPlayerPos(),
							 p_objectBase->GetCubeDirPos(), (p_objectBase->GetCubeIsSupport() && !p_objectBase->GetCubeIsClear()));
	}

	StateChange();
}

void SceneBase::Draw()
{
	if (nowScene == PLAY || nowScene == NEXT)
	{
		p_characterBase->Draw();

		p_objectBase->Draw();

		p_ui->Draw();

		p_stage->Draw();
	}
}

void SceneBase::StateChange()
{
	if (nowScene == PLAY)
	{
		if (p_objectBase->GetFloorIsEndRising())
		{
			p_characterBase->SetIsCanMoveToPlayer(true);

			if (p_characterBase->GetPlayerIsGround())
			{
				p_objectBase->SetIsCanShotToCube(true);
			}
			else
			{
				p_objectBase->SetIsCanShotToCube(false);
			}
		}
		else
		{
			p_characterBase->SetIsCanMoveToPlayer(false);

			p_objectBase->SetIsCanShotToCube(false);
		}

		if (p_objectBase->GetCubeIsClear())
		{
			p_stage->SetIsNext(true);
			nowScene = NEXT;
		}
	}
	if (nowScene == NEXT)
	{
		if (p_stage->GetIsChange())
		{
			p_characterBase->Init();
			p_mapObject->NextStage(p_stage->GetNowStageNum());
			nowScene = PLAY;
		}
	}
}

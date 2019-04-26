#include "MapObjectManager.h"


MapObjectManager::MapObjectManager()
{
	p_floorControll = new FloorControll();
	p_cubeControll = new CubeControll();

	m_modelHandleFrame = MV1LoadModel("data/model/frame.mqo");	//枠
	m_modelHandleTower = MV1LoadModel("data/model/tower.x");	//タワー
}


MapObjectManager::~MapObjectManager()
{
	MV1DeleteModel(m_modelHandleTower);
	MV1DeleteModel(m_modelHandleFrame);
}

void MapObjectManager::Init()
{
	p_floorControll->Init();
	p_cubeControll->Init();
}

void MapObjectManager::Update()
{
	p_floorControll->Update();
	p_cubeControll->Update();

	if (p_cubeControll->GetIsClear())
	{
		p_floorControll->SetIsRising(true);
	}
}

void MapObjectManager::Draw()
{
	// ３Dモデルのポジション設定
	MV1SetPosition(m_modelHandleTower, VGet(0, 0, 0));
	MV1SetPosition(m_modelHandleFrame, VGet(0, 0, 0));
	
	// ３Ｄモデルの描画
	MV1DrawModel(m_modelHandleTower);
	MV1DrawModel(m_modelHandleFrame);

	p_floorControll->Draw();
	p_cubeControll->Draw();
}

void MapObjectManager::NextStage(int n)
{
	p_cubeControll->ChangeNextPos(n);
	p_floorControll->Init();
}

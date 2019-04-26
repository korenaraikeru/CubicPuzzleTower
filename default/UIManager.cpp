#include "UIManager.h"

UIManager::UIManager()
{
	p_miniMap = new MiniMapControll();
}


UIManager::~UIManager()
{
	
}

void UIManager::Init()
{
	p_miniMap->Init();
}

void UIManager::Update()
{

}

void UIManager::Draw()
{
	p_miniMap->Draw();
}

void UIManager::SetMiniMapInfo(int i, VECTOR cubePos, VECTOR playerPos, VECTOR dirPos, bool isSupport)
{
	p_miniMap->SetCubePos(i, cubePos);
	p_miniMap->SetPlayerPos(playerPos);
	p_miniMap->SetDirPos(dirPos);

	if (isSupport)
	{
		p_miniMap->SetIsSupport(true);
	}
	else
	{
		p_miniMap->SetIsSupport(false);
	}
}

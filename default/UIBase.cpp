#include "UIBase.h"

UIBase::UIBase()
{
	p_miniMap = new MiniMapControll();
}


UIBase::~UIBase()
{
	
}

void UIBase::Create()
{
	p_uiControll = new UIControll();
	p_miniMap = new MiniMapControll();
}

void UIBase::Delete()
{
	delete(p_uiControll);
	delete(p_miniMap);
}

void UIBase::Init()
{
	p_uiControll->Init();
	p_miniMap->Init();
}

void UIBase::Update()
{
	if (m_nowScene == TITLE)
	{
		p_uiControll->UpdateTitle();
	}
	else if (m_nowScene == PLAY)
	{
		;
	}
}

void UIBase::Draw()
{
	if (m_nowScene == TITLE)
	{
		p_uiControll->DrawTitle();
	}
	else if (m_nowScene == PLAY)
	{
		p_miniMap->Draw();
	}
}

void UIBase::SetMiniMapInfo(int i, VECTOR cubePos, VECTOR playerPos, VECTOR dirPos, bool isSupport)
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

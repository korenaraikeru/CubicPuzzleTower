#include "UIControll.h"

UIControll::UIControll()
{
	m_graphTitle = LoadGraph("data/title2.png");
	m_graphStart = LoadGraph("data/start.png");
}


UIControll::~UIControll()
{
}

void UIControll::Init()
{
	m_startTime = 0;
	m_alpha = 255;

	m_isBlink = false;
}

void UIControll::UpdateTitle()
{
	BlinkGraph(1);
}

void UIControll::DrawTitle()
{
	DrawGraph(0, 0, m_graphTitle, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alpha);
	DrawGraph(0, 0, m_graphStart, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

void UIControll::BlinkGraph(float interval)
{
	if (!m_isBlink)
	{
		m_startTime = GetNowCount();
		m_isBlink = true;
	}

	if (m_isBlink && (GetNowCount() - m_startTime) / 1000 >= interval)
	{
		if (m_alpha == 0)
		{
			m_alpha = 255;
		}
		else
		{
			m_alpha = 0;
		}

		m_isBlink = false;
	}
}

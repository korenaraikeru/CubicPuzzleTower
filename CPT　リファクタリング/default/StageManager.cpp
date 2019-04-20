#include "StageManager.h"
#include "Sound.h"


StageManager::StageManager()
{

}


StageManager::~StageManager()
{
}

void StageManager::Init()
{
	m_nowStageNum = 1;
	m_alpha = 255;

	m_isNext = false;
	m_isChange = false;
}

void StageManager::Update()
{
	if (m_isChange)
	{
		m_isChange = false;
	}

	if (m_isNext)
	{
		m_alpha += 5;
		if (m_alpha >= 255)
		{
			m_nowStageNum++;
			m_isNext = false;
			m_isChange = true;
		}
	}
	else
	{
		if (m_alpha > 0)
		{
			m_alpha -= 5;
		}
	}

	if (m_nowStageNum > 12)
	{
		m_nowStageNum = 1;
	}
}

void StageManager::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alpha);
	DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

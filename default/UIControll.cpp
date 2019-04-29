﻿//-----------------------------------------------------------------------------
// UIコントロールクラス
//-----------------------------------------------------------------------------
#include "UIControll.h"

//-----------------------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------------------
UIControll::UIControll()
{
	m_graphTitle = LoadGraph("data/title2.png");
	m_graphStart = LoadGraph("data/start.png");
}

//-----------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------
UIControll::~UIControll()
{
}

//-----------------------------------------------------------------------------
// 初期化
//-----------------------------------------------------------------------------
void UIControll::Init()
{
	m_startTime = 0;
	m_alpha = 255;

	m_isBlink = false;
}

//-----------------------------------------------------------------------------
// 更新（タイトル）
//-----------------------------------------------------------------------------
void UIControll::UpdateTitle()
{
	BlinkGraph(1);
}

//-----------------------------------------------------------------------------
// 描画（タイトル）
//-----------------------------------------------------------------------------
void UIControll::DrawTitle()
{
	DrawGraph(0, 0, m_graphTitle, TRUE);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alpha);
	DrawGraph(0, 0, m_graphStart, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

// 点滅処理（引数に指定した秒毎にalphaを変更して点滅させる）
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
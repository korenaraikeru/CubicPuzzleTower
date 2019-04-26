#include "FloorControll.h"
#include "Sound.h"


FloorControll::FloorControll()
{
	m_modelHandle = MV1LoadModel("data/model/scaffold.mqo");
}


FloorControll::~FloorControll()
{
	MV1DeleteModel(m_modelHandle);
}

void FloorControll::Init()
{
	m_pos = VGet(0.f, -150.f, 0.f);

	m_isRising = false;
	m_isEndRising = false;
}

void FloorControll::Update()
{
	// 床が動いている間、効果音再生
	if (m_pos.y != 0)
	{
		playSound(SE_SCAF);
	}
	else
	{
		stopSound(SE_SCAF);
		resetSound(SE_SCAF);
	}

	if (m_pos.y >= 0 && !m_isRising)
	{
		m_pos.y = 0.f;
		m_isEndRising = true;
	}
	else
	{
		m_pos.y += 2.f;
		m_isEndRising = false;
	}
}

void FloorControll::Draw()
{
	// ３Ｄモデルのポジション設定
	MV1SetPosition(m_modelHandle, m_pos);

	// ３Ｄモデルの描画
	MV1DrawModel(m_modelHandle);
}

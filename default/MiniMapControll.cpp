//-----------------------------------------------------------------------------
// ミニマップコントロールクラス
//-----------------------------------------------------------------------------
#include "MiniMapControll.h"

//-----------------------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------------------
MiniMapControll::MiniMapControll()
{
	m_graphFrame = LoadGraph("data/miniMap.png");
	m_graphGrid = LoadGraph("data/frame.png");
	m_graphCube = LoadGraph("data/cube.png");
	m_graphDir = LoadGraph("data/dir_len.png");
}

//-----------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------
MiniMapControll::~MiniMapControll()
{
	// 処理なし
}

//-----------------------------------------------------------------------------
// 初期化
//-----------------------------------------------------------------------------
void MiniMapControll::Init()
{
	m_gridPos.x = 1500;
	m_gridPos.y = 150;
	m_playerPos = VGet(0, 0, 0);
	m_dirPos = VGet(0, 0, 0);

	for (int i = 0; i < 9; i++)
	{
		m_cubePos[i] = VGet(0, 0, 0);
	}

	m_isSupport = false;
}

//-----------------------------------------------------------------------------
// 更新
//-----------------------------------------------------------------------------
void MiniMapControll::Update()
{
	
}

//-----------------------------------------------------------------------------
// 描画
//-----------------------------------------------------------------------------
void MiniMapControll::Draw()
{
	DrawGraph(m_gridPos.x - 95, m_gridPos.y - 95, m_graphFrame, TRUE);
	DrawGraph(m_gridPos.x, m_gridPos.y, m_graphGrid, TRUE);

	if (m_isSupport && m_playerPos.y > -2)
	{
		if (m_playerPos.x < 105 && m_playerPos.x > -105)
		{
			if (m_playerPos.z > 105)
				DrawRotaGraph((int)m_dirPos.x + (int)m_gridPos.x + 105, (int)-m_dirPos.z + (int)m_gridPos.y + 210, 1.0f, 0, m_graphDir, TRUE);
			else if (m_playerPos.z < -105)
				DrawRotaGraph((int)m_dirPos.x + (int)m_gridPos.x + 105, (int)-m_dirPos.z + (int)m_gridPos.y, 1.0f, 180.0f / 180.0f * DX_PI_F, m_graphDir, TRUE);
		}
		else if (m_playerPos.z < 105 && m_playerPos.z > -105)
		{
			if (m_playerPos.x > 105)
				DrawRotaGraph((int)m_dirPos.x + (int)m_gridPos.x, (int)-m_dirPos.z + (int)m_gridPos.y + 105, 1.0f, 90.0f / 180.0f * DX_PI_F, m_graphDir, TRUE);
			else if (m_playerPos.x < -105)
				DrawRotaGraph((int)m_dirPos.x + (int)m_gridPos.x + 210, (int)-m_dirPos.z + (int)m_gridPos.y + 105, 1.0f, 270.0f / 180.0f * DX_PI_F, m_graphDir, TRUE);
		}
	}

	for (int i = 0; i < 9; i++)
	{
		DrawGraph((int)m_cubePos[i].x + (int)m_gridPos.x + 90, (int)-m_cubePos[i].z + (int)m_gridPos.y + 90, m_graphCube, TRUE);
	}
}

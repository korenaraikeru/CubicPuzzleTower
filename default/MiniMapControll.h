//-----------------------------------------------------------------------------
// ミニマップコントロールクラス
//-----------------------------------------------------------------------------
#pragma once
#include "DxLib.h"

class MiniMapControll
{
public:
	MiniMapControll();	// コンストラクタ
	~MiniMapControll();	// デストラクタ

	//---主要関数-------------------------------------------------------------------
	void Init();		// 初期化
	void Update();		// 更新
	void Draw();		// 描画
	//-----------------------------------------------------------------------------

	//---Set関数---------------------------------------------------------------------
	void SetCubePos(int i, VECTOR v) { m_cubePos[i] = v; }
	void SetPlayerPos(VECTOR v) { m_playerPos = v; }
	void SetDirPos(VECTOR v) { m_dirPos = v; }
	void SetIsSupport(bool flag) { m_isSupport = flag; }
	//------------------------------------------------------------------------------

private:
	//---変数群----------------------------------------------------------------------
	int m_graphFrame;
	int m_graphGrid;
	int m_graphCube;
	int m_graphDir;

	VECTOR m_gridPos;
	VECTOR m_cubePos[9];
	VECTOR m_playerPos;
	VECTOR m_dirPos;

	bool m_isSupport;
	//------------------------------------------------------------------------------
};


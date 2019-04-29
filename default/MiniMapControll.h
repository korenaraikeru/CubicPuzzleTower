#pragma once
#include "DxLib.h"

class MiniMapControll
{
public:
	MiniMapControll();
	~MiniMapControll();

	void Init();
	void Update();
	void Draw();

	void SetCubePos(int i, VECTOR v) { m_cubePos[i] = v; }
	void SetPlayerPos(VECTOR v) { m_playerPos = v; }
	void SetDirPos(VECTOR v) { m_dirPos = v; }
	void SetIsSupport(bool flag) { m_isSupport = flag; }

private:
	int m_graphMap;
	int m_graphFrame;
	int m_graphCube;
	int m_graphDir;

	VECTOR m_framePos;
	VECTOR m_cubePos[9];
	VECTOR m_playerPos;
	VECTOR m_dirPos;

	bool m_isSupport;
};


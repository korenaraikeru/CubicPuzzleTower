#pragma once
#include "DxLib.h"

typedef enum SLIDE_DIR
{
	SLIDE_LEFT,
	SLIDE_RIGHT,
	SLIDE_FRONT,
	SLIDE_BACK,
}SLIDE_DIR;

class CubeControll
{
public:
	CubeControll();
	~CubeControll();

	void Init();
	void Update();
	void Draw();

	const VECTOR& GetPos(int i) const { return m_pos[i]; }
	const VECTOR& GetDirPos() const { return m_dirPos[m_supportNum]; }
	bool GetIsSupport() { return m_isSupport; }
	bool GetIsClear() { return m_isClear; }
	void SetPlayerPos(VECTOR v) { m_playerPos = v; }
	void ChangeNextPos(int stageNum);
	void SetIsCanShot(bool flag) { m_isCanShot = flag; }

private:
	
	void MoveCube(int i);
	void CheckAdjacent(int i);
	void ShotSupport();
	void DetectionCollision(int i);
	void SetBordInfo();
	void Debug();

	int m_modelHandle;
	int m_modelHandleDir;

	VECTOR m_pos[9];
	VECTOR m_playerPos;
	VECTOR m_squaresPos[49];
	VECTOR m_dirPos[28];
	VECTOR m_sqStartPoint, m_sqEndPoint;
	VECTOR m_slideVec;
	
	float m_radius;
	float m_moveSpeed;
	float m_range;

	int m_slideDirection;
	int m_nowStageNum;
	int m_supportNum;
	int m_waitCnt;
	int m_nextPosNum[108] = {16,  3, 18, 23, 24, 27, 30, 31, 32,
							  2, 17, 20,  9, 24, 27, 30, 31, 32,
							 16, 17, 18,  0, 24, 27, 28, 31, 48,
							 16,  3, 18, 21, 22, 25, 30, 45, 32,
							 16,  0,  4, 21, 24, 25, 42, 45, 48,
							 14,  3, 20, 23, 24, 25, 44, 28, 34,
							  2,  6, 14,  9, 24, 27, 30, 31, 32,
							 16,  3, 18, 44, 27,  6, 28, 45, 34,
							 14,  0, 20, 42, 24, 48, 44, 45,  4,
							 16, 20,  4, 37, 26, 48, 42, 45, 32,
							  2,  4, 14, 20, 21, 27, 30, 32, 45,
							  3,  6, 14, 18, 30, 34, 42, 46, 48};

	bool m_isSlide[9];
	bool m_isFit[9];
	bool m_isHit[9];
	bool m_isCanShot;
	bool m_isMove;
	bool m_isAllFit;
	bool m_isSupport;
	bool m_isReset;
	bool m_isClear;
};


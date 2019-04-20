#pragma once
#include "DxLib.h"

class StageManager
{
public:
	StageManager();
	~StageManager();

	void Init();
	void Update();
	void Draw();

	void SetIsNext(bool flag) { m_isNext = flag; }
	int GetNowStageNum() { return m_nowStageNum; }
	bool GetIsChange() { return m_isChange; }

private:
	int m_nowStageNum;
	int m_alpha;

	bool m_isNext;
	bool m_isChange;
};


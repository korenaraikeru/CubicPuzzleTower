#pragma once
#include "DxLib.h"

class FloorControll
{
public:
	FloorControll();
	~FloorControll();

	void Init();
	void Update();
	void Draw();

	const VECTOR& GetPos() const { return m_pos; }
	bool GetIsEndRising() { return m_isEndRising; }
	void SetIsRising(bool flag) { m_isRising = flag; }

private:
	int m_modelHandle;
	VECTOR m_pos;

	bool m_isRising;
	bool m_isEndRising;
};


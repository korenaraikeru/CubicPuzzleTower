#pragma once
#include <math.h>
#include "DxLib.h"

class FPS
{
public:
	FPS();
	~FPS();

	bool Update();
	void Wait();
private:
	int m_startTime;			// 測定開始時刻
	int m_count;				// カウンタ
	float m_fps;				// fps
	static const int N = 60;	// 平均をとるサンプル数
	static const int Fps = 60;	// 設定するFPS
};


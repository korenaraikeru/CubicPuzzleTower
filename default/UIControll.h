//-----------------------------------------------------------------------------
// UIコントロールクラス
//-----------------------------------------------------------------------------
#pragma once
#include "DxLib.h"
#include "Define.h"

class UIControll
{
public:
	UIControll();
	~UIControll();
	
	//---主要関数-------------------------------------------------------------------
	void Init();
	void UpdateTitle();
	void DrawTitle();
	//-----------------------------------------------------------------------------

private:
	void BlinkGraph(float interval);		// 点滅処理

	//---変数群----------------------------------------------------------------------
	int m_graphTitle;
	int m_graphStart;
	int m_graphFloorNum[12];
	int m_graphManual;
	int m_graphTutorial[5];
	int m_graphLevel[4];
	int m_graphBackGound;
	int m_graphSlime;

	int m_alpha;
	int m_startTime;

	bool m_isBlink;

	SCENE_TYPE m_nowScene;
	//-----------------------------------------------------------------------------
};


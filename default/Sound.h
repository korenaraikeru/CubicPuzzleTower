//------------------------------
// 音関連関数群
//------------------------------
#pragma once
#define ALL_NUM 14

// 音の種類
typedef enum SOUND_NUM
{
	BGM_TITLE,
	BGM_SELECT,
	BGM_PLAY,
	SE_SCAF,
	BGM_ALLCLEAR,
	SE_CURSOR,
	SE_DECISION,
	SE_START,
	SE_PAUSE,
	SE_CANCEL,
	SE_SHOT,
	SE_CUBEHIT,
	SE_JUMP,
	SE_CLEAR
}SOUND_NUM;

void loadSound();					// 読み込み
void deleteSound();					// 削除
void playSound(int sound_name);		// 再生
void stopSound(int sound_name);		// 停止
void resetSound(int sound_name);	// 再生位置初期化
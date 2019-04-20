#include "Sound.h"
#include "DxLib.h"

int sound[ALL_NUM];

void loadSound()
{
	sound[BGM_TITLE] = LoadSoundMem("data/sound/title.mp3");
	sound[BGM_SELECT] = LoadSoundMem("data/sound/select.mp3");
	sound[BGM_PLAY] = LoadSoundMem("data/sound/bgm_play.mp3");
	sound[BGM_ALLCLEAR] = LoadSoundMem("data/sound/AllClear.mp3");
	sound[SE_CURSOR] = LoadSoundMem("data/sound/cursor.mp3");
	sound[SE_DECISION] = LoadSoundMem("data/sound/decision.mp3");
	sound[SE_START] = LoadSoundMem("data/sound/start.mp3");
	sound[SE_PAUSE] = LoadSoundMem("data/sound/pause.mp3");
	sound[SE_CANCEL] = LoadSoundMem("data/sound/cancel.mp3");
	sound[SE_SHOT] = LoadSoundMem("data/sound/shot.mp3");
	sound[SE_CUBEHIT] = LoadSoundMem("data/sound/cube_hit.mp3");
	sound[SE_JUMP] = LoadSoundMem("data/sound/jump.mp3");
	sound[SE_CLEAR] = LoadSoundMem("data/sound/clear.mp3");
	sound[SE_SCAF] = LoadSoundMem("data/sound/scaf_move.mp3");
}

void deleteSound()
{
	for (int i = 0; i < ALL_NUM; i++)
		DeleteSoundMem(sound[i]);
}

void playSound(int sound_name)
{
	if (CheckSoundMem(sound[sound_name]) == 0)
	{
		if (sound_name >= BGM_TITLE && sound_name <= BGM_ALLCLEAR)
			PlaySoundMem(sound[sound_name], DX_PLAYTYPE_LOOP, FALSE);
	}
	if (sound_name >= SE_CURSOR)
		PlaySoundMem(sound[sound_name], DX_PLAYTYPE_BACK);
}

void stopSound(int sound_name)
{
	if (CheckSoundMem(sound[sound_name]) == 1)
	{
		StopSoundMem(sound[sound_name]);
	}
}

void resetSound(int sound_name)
{
	SetCurrentPositionSoundMem(0, sound[sound_name]);
}

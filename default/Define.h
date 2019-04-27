#pragma once

#define SCREEN_W 1920
#define SCREEN_H 1080

#define VECTOR_SCALING 0.70710678118f //Î‚ßˆÚ“®ŒW”

typedef enum SCENE_TYPE
{
	TITLE,
	SELECT,
	PLAY,
	NEXT,
	PAUSE,
	CLEAR,
}SCENE_TYPE;

enum LEVEL
{
	easy,
	normal,
	hard,
	extra
};
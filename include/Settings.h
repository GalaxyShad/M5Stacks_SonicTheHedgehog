#pragma once
#include "..\GameSettings.h"

#define CORE

#define TEXTURES_COUNT 	3

#define TEX_OBJECTS 	0
#define TEX_GHZ_TILES 	1
#define TEX_GHZ_GIMM 	2

#include <M5Stack.h>
#include <list>

#ifdef OPTIMAL_RESOLUTION
	#define SCREEN_WIDTH    160
	#define SCREEN_HEIGHT   140
#endif
#ifdef FULL_RESOLUTION
	#define SCREEN_WIDTH    320
	#define SCREEN_HEIGHT   200
#endif
#ifdef MAX_FPS_RESOLUTION
	#define SCREEN_WIDTH    80
	#define SCREEN_HEIGHT   80
#endif

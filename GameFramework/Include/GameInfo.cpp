
#include "GameInfo.h"

// 180µµ = PI

float RadianToDegree(float Radian)
{
	return Radian / PI * 180.f;
}

float DegreeToRadian(float Degree)
{
	return Degree / 180.f * PI;
}

int g_SoundVolume = 100;
int g_MusicVolume = 100;
int g_PlayerSelect = 0;
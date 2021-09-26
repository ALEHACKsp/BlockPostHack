#pragma once
#include "Vector.h"

class WallHack
{
public:	
	void Render();
	Vector2 GetPlayerPos(int i);
	int selectiedFigure = 0;
	bool teamcheck = false;
	float colorWh[4] = { 0.780f, 0.031f, 0.756f,1.0f };
	float colorWhS[4] = { 0.007f, 0.152f, 0.788f,1.0f };
	

};
class WallHackNames
{
public:
	char Lenght[8];
	int xxx_pad;
	char Pname[32];
	char ANTICRASH[64];
};

#pragma once
#include "Vector.h"
#include "framework/il2cpp-appdata.h"


class WallHack
{
public:	
	void Render();
	Vector2WH GetPlayerPos(int i);
	int GetPlayerIsSpawnprotect(int i);
	bool GetPlayerIsVisible(int i);
	bool visibleCheck;
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

class myCameraS {
public:
	char pad[0x3b4];
	app::Vector3 campos;
};

class cscameraS {
public:
	char pad[8];
	myCameraS* camira;
};


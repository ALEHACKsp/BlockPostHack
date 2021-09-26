#pragma once
#include "Vector.h"
class Skeleton
{
public:
	VectorSkelet GetBones(int i);
	void Render();
	bool teamcheck = false;
	float colorSkelet[4] = { 0.007f, 0.152f, 0.788f,1.0f };
	float colorSkeletS[4] = { 0.007f, 0.152f, 0.788f,1.0f };
};

class WallHackNamess
{
public:
	char Lenght[8];
	int xxx_pad;
	char Pname[32];
	char ANTICRASH[64];
};
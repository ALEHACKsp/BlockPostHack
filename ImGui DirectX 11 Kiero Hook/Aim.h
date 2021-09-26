#pragma once
#include "includes.h"
#include "Vector.h"
#include "framework/il2cpp-appdata.h"

class AimBot
{
public:
	Vector2 GetDistanceAndAngle(Vector3 startPOS, app::Vector3 endPOS);
	void Render();
	bool toggle = false;
	bool teamcheck = false;
	float distanceFov = 40;
	float fov = 1;
	float dist;	
};


class myCamera {
public:
	char pad[0x3b4];
	Vector3 campos;
};

class cscamera {
public:
	char pad[8];
	myCamera* camira;
};



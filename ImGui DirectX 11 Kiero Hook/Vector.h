#pragma once
#include "framework/il2cpp-appdata.h"
#include "framework/il2cpp-init.h"
class Vector3
{
public:
	float x, y, z;

};


class Vector2
{
public:
	float x, y, d;
	char* str;
};

class VectorSkelet
{
public:
	app::Vector2 bone[15];
};
class Vector2WH
{
public:
	app::Vector2 pos[2];
};
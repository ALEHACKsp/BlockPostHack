#pragma once
#include "Vector.h"
class Tracer
{
public:
	void Render();
	Vector2 GetPlayerPos(int i);
	bool teamcheck = false;
	float LineSize = 1;
	float colorTracer[4] = { 0.0f,1.0f,0.0f,1.0f };
	
};
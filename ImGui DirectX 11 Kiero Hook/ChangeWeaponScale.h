#pragma once
#include "ChangeWeaponScale.h"
#include "framework/il2cpp-appdata.h"
#include "offsetsM.h"
class ChangeWeaponScale
{
public:
	void StartS(UINT32 i, float scale);
	app::Vector3 sac = { 1.27,1.27,1.27 };
	bool active = false;
};
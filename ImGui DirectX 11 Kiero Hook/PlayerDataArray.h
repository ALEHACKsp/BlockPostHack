#pragma once
#include "includes.h"
#include "framework/il2cpp-appdata.h"
class PlayerDataArray
{
public:
	char pad_0012[0xF]; //0x00c
	app::PlayerData* Player[40]; //0x0010
};

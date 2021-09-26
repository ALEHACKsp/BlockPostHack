#include "WallHack.h"
#include "framework/il2cpp-appdata.h"
#include <iostream>
#include "Vector.h"
#include "offsetsM.h"
#include "includes.h"


app::PlayerData* GetPlayerData(UINT32 i)
{
	offsetsM offsets;
	PlayerDataArray* pdataA = (PlayerDataArray*)(*app::PLH__TypeInfo)->static_fields->player;
	DWORD CHECK = (DWORD)pdataA->Player[i];
	if (CHECK < 0xfffff || CHECK == NULL || &CHECK == nullptr)
		return NULL;
	return pdataA->Player[i];
}


Vector2 WallHack::GetPlayerPos(int i)
{
	offsetsM offsets;
	ImVec2 posInScreenTrue;
	if (offsets.GetPointerAddress(reinterpret_cast<uintptr_t>(GetModuleHandle("GameAssembly.dll")) + 0xB35CA8, { 0x5C,0x0C, (UINT)0x10 + i * 4,  0x28 }) == reinterpret_cast<uintptr_t>(GetModuleHandle("GameAssembly.dll")) + 0xB35CA8)
		return { -1, -1,-1 };/// vec 0
	app::PlayerData* enemy = GetPlayerData(i);
	WallHackNames* chars = (WallHackNames*)(enemy->fields.name);

	if (teamcheck == true)
	{
		if ((*app::Controll__TypeInfo)->static_fields->pl->fields.team == enemy->fields.team)
		{
			return { -1, -1,-1 };/// vec 07
		}
	}
	if (enemy->fields.currweapon == nullptr)
		return { -1,-1,-1 };
	if (app::Camera_WorldToScreenPoint((*app::Controll__TypeInfo)->static_fields->csCam, enemy->fields.currPos, app::Camera_MonoOrStereoscopicEye__Enum::Mono, nullptr).z <= 1.0f)
		return { -1, -1,-1 };/// vec 0
	if (enemy->fields.bstate == 5)
		return { -1,-1,-1 };	
	posInScreenTrue.y = app::Screen_get_height(nullptr) - app::Camera_WorldToScreenPoint((*app::Controll__TypeInfo)->static_fields->csCam, enemy->fields.currPos, app::Camera_MonoOrStereoscopicEye__Enum::Mono, nullptr).y;
	if (enemy->fields.leg_limit == 46)
		return { posInScreenTrue.x ,posInScreenTrue.y,44,chars->Pname };
			if (enemy->fields.spawnprotect)
			{
				return { app::Camera_WorldToScreenPoint((*app::Controll__TypeInfo)->static_fields->csCam, enemy->fields.currPos, app::Camera_MonoOrStereoscopicEye__Enum::Mono, nullptr).x ,posInScreenTrue.y,3,chars->Pname };/// vec 07
			}
			return { app::Camera_WorldToScreenPoint((*app::Controll__TypeInfo)->static_fields->csCam, enemy->fields.currPos, app::Camera_MonoOrStereoscopicEye__Enum::Mono, nullptr).x ,posInScreenTrue.y,0,chars->Pname };
}

void WallHack::Render()
{
	ImGui::GetBackgroundDrawList()->AddText({ 0,0 }, ImColor{ 10, 63, 255,255 }, "EZHACKBYSCUB");

	for (int i = 0; i < 40; i++)
	{
		Vector2 Temper = GetPlayerPos(i);
		if (Temper.d == -1)
			continue;

		char aaa[16] = { Temper.str[0], Temper.str[2],Temper.str[4], Temper.str[6], Temper.str[8] ,Temper.str[10], Temper.str[12], Temper.str[14], Temper.str[16], Temper.str[18], Temper.str[20], Temper.str[22], Temper.str[24], Temper.str[26], Temper.str[28], Temper.str[30] };

		
		if (Temper.d == 3)
		{

			ImGui::GetBackgroundDrawList()->AddText({ Temper.x - 30,Temper.y - 20 }, ImColor{ 255, 255, 222, 255 }, aaa);
			if (selectiedFigure == 0)
				ImGui::GetBackgroundDrawList()->AddCircle({ Temper.x,Temper.y }, 10, ImColor{ colorWhS[0],colorWhS[1],colorWhS[2],colorWhS[3] }, 12, 2);
			if (selectiedFigure == 1)
				ImGui::GetBackgroundDrawList()->AddRect({ Temper.x - 10,Temper.y + 15 }, { Temper.x + 10,Temper.y - 15 }, ImColor{ colorWhS[0],colorWhS[1],colorWhS[2],colorWhS[3] });
			if (selectiedFigure == 2)
				ImGui::GetBackgroundDrawList()->AddRectFilled({ Temper.x - 10,Temper.y + 15 }, { Temper.x + 10,Temper.y - 15 }, ImColor{ colorWhS[0],colorWhS[1],colorWhS[2],colorWhS[3] });

		}
		else if (Temper.d == 44)
		{
			ImGui::GetBackgroundDrawList()->AddText({ Temper.x - 30,Temper.y - 20 }, ImColor{ 255, 255, 222, 255 }, aaa);
			if (selectiedFigure == 0)
				ImGui::GetBackgroundDrawList()->AddCircle({ Temper.x,Temper.y }, 10, ImColor{ 255, 255, 222, 255 }, 12, 2);
			if (selectiedFigure == 1)
				ImGui::GetBackgroundDrawList()->AddRect({ Temper.x - 10,Temper.y + 15 }, { Temper.x + 10,Temper.y - 15 }, ImColor{ 255, 255, 222, 255 });
			if (selectiedFigure == 2)
				ImGui::GetBackgroundDrawList()->AddRectFilled({ Temper.x - 10,Temper.y + 15 }, { Temper.x + 10,Temper.y - 15 }, ImColor{ 255, 255, 222, 255 });

		}
		else
		{
			ImGui::GetBackgroundDrawList()->AddText({ Temper.x - 30,Temper.y - 20 }, ImColor{ 255, 255, 222, 255 }, aaa);
			if (selectiedFigure == 0)
				ImGui::GetBackgroundDrawList()->AddCircle({ Temper.x,Temper.y }, 10, ImColor{ colorWh[0],colorWh[1],colorWh[2],colorWh[3] }, 12, 2);
			if (selectiedFigure == 1)
				ImGui::GetBackgroundDrawList()->AddRect({ Temper.x - 10,Temper.y + 15 }, { Temper.x + 10,Temper.y - 15 }, ImColor{ colorWh[0],colorWh[1],colorWh[2],colorWh[3] });
			if (selectiedFigure == 2)
				ImGui::GetBackgroundDrawList()->AddRectFilled({ Temper.x - 10,Temper.y + 15 }, { Temper.x + 10,Temper.y - 15 }, ImColor{ colorWh[0],colorWh[1],colorWh[2],colorWh[3] });

		}	
	}

}
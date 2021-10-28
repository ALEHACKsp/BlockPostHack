#include "WallHack.h"
#include "framework/il2cpp-appdata.h"
#include <iostream>
#include "Vector.h"
#include "offsetsM.h"
#include "includes.h"
#include "Functions.h"
#include "kiero/minhook/include/MinHook.h"
typedef void(__fastcall* hookfunc)(int a1);

app::RaycastHit Hitp;
float distSac;
int layerSac;

int nump = 0;
bool activeRay = false;
bool visiblesac;
void RaySack(int a1)
{
	
	if (nump <= 40)
	{
		app::PlayerData* enemy = Functions::GetPlayerData(nump);
		if (enemy == NULL)
		{
			nump++;
			return;
		}
		app::Vector3 enm = enemy->fields.currPos;
		app::Transform* sackTr = app::GameObject_get_transform(enemy->fields.goBody, nullptr);
		app::Vector3 enemyBody = app::Transform_get_position(sackTr, nullptr);
		if (app::Physics_Linecast_1(enm, (*app::Controll__TypeInfo)->static_fields->currPos, &Hitp, nullptr))
		{
			float cmpPosx = Hitp.m_Point.x - (*app::Controll__TypeInfo)->static_fields->currPos.x;
			float cmpPosy = Hitp.m_Point.y - (*app::Controll__TypeInfo)->static_fields->currPos.y;
			float cmpPoz = Hitp.m_Point.z - (*app::Controll__TypeInfo)->static_fields->currPos.z;
			if (cmpPosx > -1 && cmpPosx < 1 && cmpPosy > -1 && cmpPosy < 1 && cmpPoz > -1 && cmpPoz < 1)
			{
				if (visiblesac)
				{
					enemy->fields.leg_limit = 46;
				}
				
			}
			else
			{
				if (app::Physics_Linecast_1((*app::Controll__TypeInfo)->static_fields->currPos, enemyBody, &Hitp, nullptr))
				{					
					float cmpPosx = Hitp.m_Point.x - enemyBody.x;
					float cmpPosy = Hitp.m_Point.y - enemyBody.y;
					float cmpPoz = Hitp.m_Point.z - enemyBody.z;
					if (cmpPosx > -1 && cmpPosx < 1 && cmpPosy > -1 && cmpPosy < 1 && cmpPoz > -1 && cmpPoz < 1)
					{
						if (visiblesac)
						{
							enemy->fields.leg_limit = 46;
						}
					}
					else
					{
						enemy->fields.leg_limit = 45;
					}
				}
			}
		}
		nump++;
	}
	else
	{
		nump = 0;
	}

	return;
}
uintptr_t scastz(UINT64 adr)
{

	return reinterpret_cast<std::uintptr_t>(GetModuleHandle(TEXT("GameAssembly.dll"))) + adr;
}




Vector2WH WallHack::GetPlayerPos(int i)
{
	if (activeRay == false)
	{
		hookfunc HookName = hookfunc(scastz(0x287440)); //makes this to be a function to hook

		MH_CreateHook(HookName, &RaySack, NULL);
		MH_EnableHook(HookName);
		activeRay = true;
	}
	ImVec2 posInScreenTrue;
	ImVec2 posInScreenTrue2;
	Vector2WH posArray;
	app::PlayerData* enemy = Functions::GetPlayerData(i);
	if(Functions::GetEnemyLive(i) == false)
		return Vector2WH{ 0 };
	if (teamcheck == true)
	{
		if ((*app::Controll__TypeInfo)->static_fields->pl->fields.team == enemy->fields.team)
		{
			return Vector2WH{ 0 };
		}
	}
	app::Camera* cam = app::Camera_get_main(nullptr);
	app::Vector3 posHead = app::Transform_get_position(app::GameObject_get_transform(enemy->fields.goHead, nullptr), nullptr);
	app::Vector3 WorldPosHead = app::Camera_WorldToScreenPoint((*app::Controll__TypeInfo)->static_fields->csCam, posHead, app::Camera_MonoOrStereoscopicEye__Enum::Mono, nullptr);
	app::Vector3 WorldPosLeg = app::Camera_WorldToScreenPoint((*app::Controll__TypeInfo)->static_fields->csCam, { posHead.x,posHead.y - 2,posHead.z}, app::Camera_MonoOrStereoscopicEye__Enum::Mono, nullptr);
	if (WorldPosHead.z <= 1.0f)
		return Vector2WH{ 0 };
	if (WorldPosLeg.z <= 1.0f)
		return Vector2WH{ 0 };
	posInScreenTrue = { WorldPosHead.x,app::Screen_get_height(nullptr) - WorldPosHead.y };
	posInScreenTrue2 = { WorldPosLeg.x,app::Screen_get_height(nullptr) - WorldPosLeg.y };
	posArray.pos[0] = { posInScreenTrue2.x  ,posInScreenTrue2.y };
	posArray.pos[1] = { posInScreenTrue.x  ,posInScreenTrue.y };
	float width = abs(posInScreenTrue.y - posInScreenTrue2.y) * 0.3f;
	return { posArray.pos[0].x + width, posArray.pos[0].y ,posArray.pos[1].x - width, posArray.pos[1].y };
}
int WallHack::GetPlayerIsSpawnprotect(int i)
{
	app::PlayerData* enemy = Functions::GetPlayerData(i);
	if (Functions::GetEnemyLive(i) == false)
		return -1;
	if (teamcheck == true)
	{
		if ((*app::Controll__TypeInfo)->static_fields->pl->fields.team == enemy->fields.team)
		{
			return -1;
		}
	}
	if (enemy->fields.spawnprotect)
	{
		return 1;
	}
	return 0;
}
bool WallHack::GetPlayerIsVisible(int i)
{
	app::PlayerData* enemy = Functions::GetPlayerData(i);
	if (Functions::GetEnemyLive(i) == false)
		return 0;
	if (teamcheck == true)
	{
		if ((*app::Controll__TypeInfo)->static_fields->pl->fields.team == enemy->fields.team)
		{
			return 0;
		}
	}
	if (enemy->fields.leg_limit == 46)
	{
		return 1;
	}
	return 0;
}
void WallHack::Render()
{
	for (int i = 0; i < 40; i++)
	{
		if (visibleCheck)
			visiblesac = true;
		else
		{
			visiblesac = false;
		}
		Vector2WH Temper = GetPlayerPos(i);
		int SpawnProtectEnemy = GetPlayerIsSpawnprotect(i);
		bool Visible = GetPlayerIsVisible(i);
		if (Temper.pos == 0)
			continue;
			if (Visible)
				ImGui::GetBackgroundDrawList()->AddRect({ Temper.pos[0].x,Temper.pos[0].y }, { Temper.pos[1].x,Temper.pos[1].y }, ImColor{ 255,255,255,255 }, 0, 15, 3);
			else if (SpawnProtectEnemy == 0)
				ImGui::GetBackgroundDrawList()->AddRect({ Temper.pos[0].x,Temper.pos[0].y }, { Temper.pos[1].x,Temper.pos[1].y }, ImColor{ colorWh[0],colorWh[1],colorWh[2],colorWh[3] }, 0, 15, 3);
			else if (SpawnProtectEnemy == 1)
				ImGui::GetBackgroundDrawList()->AddRect({ Temper.pos[0].x,Temper.pos[0].y }, { Temper.pos[1].x,Temper.pos[1].y }, ImColor{ colorWhS[0],colorWhS[1],colorWhS[2],colorWhS[3] }, 0, 15, 3);
		
		
	}
}
#include "WallHack.h"
#include "framework/il2cpp-appdata.h"
#include <iostream>
#include "Vector.h"
#include "offsetsM.h"
#include "includes.h"
#include "Functions.h"


Vector2WH WallHack::GetPlayerPos(int i)
{
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

void WallHack::Render()
{
	ImGui::GetBackgroundDrawList()->AddText({ 0,0 }, ImColor{ 10, 63, 255,255 }, "EZHACKBYSCUB");
	for (int i = 0; i < 40; i++)
	{
		Vector2WH Temper = GetPlayerPos(i);
		if (Temper.pos == 0)
			continue;
			ImGui::GetBackgroundDrawList()->AddRect({ Temper.pos[0].x,Temper.pos[0].y }, { Temper.pos[1].x,Temper.pos[1].y }, ImColor{ colorWh[0],colorWh[1],colorWh[2],colorWh[3] },0,15,3);			
	}
}
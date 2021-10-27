#include "Skeleton.h"
#include "framework/il2cpp-appdata.h"
#include <iostream>
#include "Vector.h"
#include "Functions.h"
#include "Bines.h"
#include "imgui/imgui.h"
#include "offsetsM.h"
#define EntListBase 0xB35C3C
#define EntListBase2 0xB35CA8
VectorSkelet is_null()
{
	constexpr VectorSkelet fuck{};
	return fuck;
}

VectorSkelet Skeleton::GetBones(int i)
{
	uintptr_t baseModule = reinterpret_cast<uintptr_t>(GetModuleHandle(TEXT("GameAssembly.dll")));
	app::Vector2 posInScreenTrue;
	app::Vector3 Larm;
	app::Vector3 Rarm;
	VectorSkelet posArray = is_null();
	if (Functions::GetEnemyLive(i) == false)
		return is_null();
	app::PlayerData* enemy = Functions::GetPlayerData(i);
	if (teamcheck == true)
	{
		if ((*app::Controll__TypeInfo)->static_fields->pl->fields.team == enemy->fields.team)
		{
			return is_null();
		}
	}
	for (int d = 0; d < 15; d++)
	{
		if (d == 2 || d == 4 || d == 5 || d == 10 || d == 14 || d == 15)
			continue;
		if (d == 6)
		{
			Larm = app::Camera_WorldToScreenPoint((*app::Controll__TypeInfo)->static_fields->csCam, app::Transform_get_position(app::GameObject_get_transform((app::GameObject*)offsetsM::GetPointerAddress(baseModule + EntListBase2, { 0x5C,0x0C, (ULONG)0x10 + i * 0x4,0xC4,0x14,0x0 }), nullptr), nullptr), app::Camera_MonoOrStereoscopicEye__Enum::Mono, nullptr);
			if (Larm.z <= 1.0f)
				return is_null();
			posInScreenTrue = { Larm.x,app::Screen_get_height(nullptr) - Larm.y };
			posArray.bone[d] = posInScreenTrue;
			continue;
		}
		if (d == 7)
		{
			Rarm = app::Camera_WorldToScreenPoint((*app::Controll__TypeInfo)->static_fields->csCam, app::Transform_get_position(app::GameObject_get_transform((app::GameObject*)offsetsM::GetPointerAddress(baseModule + EntListBase2, { 0x5C,0x0C, (ULONG)0x10 + i * 0x4,0xC8,0x14,0x0 }), nullptr), nullptr), app::Camera_MonoOrStereoscopicEye__Enum::Mono, nullptr);
			if (Rarm.z <= 1.0f)
				return is_null();
			posInScreenTrue = { Rarm.x,app::Screen_get_height(nullptr) - Rarm.y };
			posArray.bone[d] = posInScreenTrue;
			continue;
		}
		if (d == 8)
		{
			Rarm = app::Camera_WorldToScreenPoint((*app::Controll__TypeInfo)->static_fields->csCam, app::Transform_get_position(app::GameObject_get_transform((app::GameObject*)offsetsM::GetPointerAddress(baseModule + EntListBase2, { 0x5C,0x0C, (ULONG)0x10 + i * 0x4,0xCC,0x14,0x0 }), nullptr), nullptr), app::Camera_MonoOrStereoscopicEye__Enum::Mono, nullptr);
			if (Rarm.z <= 1.0f)
				return is_null();
			posInScreenTrue = { Rarm.x,app::Screen_get_height(nullptr) - Rarm.y };
			posArray.bone[d] = posInScreenTrue;
			continue;
		}
		if (d == 9)
		{
			Rarm = app::Camera_WorldToScreenPoint((*app::Controll__TypeInfo)->static_fields->csCam, app::Transform_get_position(app::GameObject_get_transform((app::GameObject*)offsetsM::GetPointerAddress(baseModule + EntListBase2, { 0x5C,0x0C, (ULONG)0x10 + i * 0x4,0xD0,0x14,0x0 }), nullptr), nullptr), app::Camera_MonoOrStereoscopicEye__Enum::Mono, nullptr);
			if (Rarm.z <= 1.0f)
				return is_null();
			posInScreenTrue = { Rarm.x,app::Screen_get_height(nullptr) - Rarm.y };
			posArray.bone[d] = posInScreenTrue;
			continue;
		}
		Bines* bone = (Bines*)enemy;
		app::Vector3 TransBone = app::Transform_get_position(app::GameObject_get_transform(bone->bones[d], nullptr), nullptr);
		app::Vector3 pos = app::Camera_WorldToScreenPoint((*app::Controll__TypeInfo)->static_fields->csCam, TransBone, app::Camera_MonoOrStereoscopicEye__Enum::Mono, nullptr);
		if (pos.z <= 1.0f)
			return is_null();
		posInScreenTrue = { pos.x,app::Screen_get_height(nullptr) - pos.y };
		posArray.bone[d] = posInScreenTrue;
	}
	return posArray;
}
void Skeleton::Render()
{
	for (int i = 0; i < 40; i++)
	{
		if (Functions::GetEnemyLive)
		{
			if (Functions::GetEnemyLive)
			{
				VectorSkelet Temper = GetBones(i);
				VectorSkelet null = is_null();
				if (Temper.bone[0].x == null.bone[0].x)
					continue;
				ImGui::GetBackgroundDrawList()->AddLine({ Temper.bone[0].x,Temper.bone[0].y }, { Temper.bone[1].x,Temper.bone[1].y }, ImColor{ colorSkelet[0],colorSkelet[1],colorSkelet[2],colorSkelet[3] }, 2.f);
				//ImGui::GetBackgroundDrawList()->AddLine({ Temper.bone[1].x,Temper.bone[1].y }, { Temper.bone[3].x,Temper.bone[3].y }, ImColor{ colorSkelet[0],colorSkelet[1],colorSkelet[2],colorSkelet[3] }, 2.f);
				ImGui::GetBackgroundDrawList()->AddLine({ Temper.bone[11].x,Temper.bone[11].y }, { Temper.bone[6].x,Temper.bone[6].y }, ImColor{ colorSkelet[0],colorSkelet[1],colorSkelet[2],colorSkelet[3] }, 2.f);
				ImGui::GetBackgroundDrawList()->AddLine({ Temper.bone[11].x,Temper.bone[11].y }, { Temper.bone[7].x,Temper.bone[7].y }, ImColor{ colorSkelet[0],colorSkelet[1],colorSkelet[2],colorSkelet[3] }, 2.f);
				ImGui::GetBackgroundDrawList()->AddLine({ Temper.bone[1].x,Temper.bone[1].y }, { Temper.bone[8].x,Temper.bone[8].y }, ImColor{ colorSkelet[0],colorSkelet[1],colorSkelet[2],colorSkelet[3] }, 2.f);
				ImGui::GetBackgroundDrawList()->AddLine({ Temper.bone[1].x,Temper.bone[1].y }, { Temper.bone[9].x,Temper.bone[9].y }, ImColor{ colorSkelet[0],colorSkelet[1],colorSkelet[2],colorSkelet[3] }, 2.f);			
			}
		}		
	}
}

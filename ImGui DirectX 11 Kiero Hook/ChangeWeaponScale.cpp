#include "ChangeWeaponScale.h"
#include "framework/il2cpp-appdata.h"
#include "offsetsM.h"
#include "Functions.h"


app::PlayerData* GetPlayerDataSas(UINT32 i)
{
	offsetsM offsets;
	PlayerDataArray* pdataA = (PlayerDataArray*)(*app::PLH__TypeInfo)->static_fields->player;
	DWORD CHECK = (DWORD)pdataA->Player[i];
	if (CHECK < 0xfffff || CHECK == NULL || &CHECK == nullptr)
		return NULL;
	return pdataA->Player[i];
}

void ChangeWeaponScale::StartS(UINT32 i,float scale)
{
	offsetsM offsets;
	app::PlayerData* enemy = GetPlayerDataSas(i);
	if (active == true)
	{
		if (Functions::GetEnemyLive(i) == false)
			return;		
		if ((*app::Controll__TypeInfo)->static_fields->pl->fields.team != 2 && (*app::Controll__TypeInfo)->static_fields->pl->fields.bstate != 5)
		{
			if ((*app::Main__TypeInfo)->static_fields->show == false)
			{
				if (enemy != nullptr || &enemy != nullptr)
				{
					if (enemy->fields.go != nullptr)
					{
						app::Transform_set_localScale(app::GameObject_get_transform(enemy->fields.go, nullptr), sac, nullptr);
					}
				}
			}
		}
	}
	else
	{
		if (Functions::GetEnemyLive(i) == false)
			return;
		if ((*app::Controll__TypeInfo)->static_fields->pl->fields.team != 2 && (*app::Controll__TypeInfo)->static_fields->pl->fields.bstate != 5)
		{
			if ((*app::Main__TypeInfo)->static_fields->show == false)
			{
				if (enemy != nullptr || &enemy != nullptr)
				{
					if (enemy->fields.go != nullptr)
					{

						app::Transform_set_localScale(app::GameObject_get_transform(enemy->fields.go, nullptr), { 1,1,1 }, nullptr);
					}
				}
			}
		}
	}
	
}
#include "ChangeWeaponScale.h"
#include "framework/il2cpp-appdata.h"
#include "offsetsM.h"


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
		if (offsets.GetPointerAddress(reinterpret_cast<uintptr_t>(GetModuleHandle("GameAssembly.dll")) + 0xB35CA8, { 0x5C,0x0C, (UINT)0x10 + i * 4,  0x28 }) != reinterpret_cast<uintptr_t>(GetModuleHandle("GameAssembly.dll")) + 0xB35CA8)
		{
			if (offsets.GetPointerAddress(reinterpret_cast<uintptr_t>(GetModuleHandle("GameAssembly.dll")) + EntListBase2, { 0x5C,0x0C, 0x10 + (UINT)i * 4,  0x28 }) != reinterpret_cast<uintptr_t>(GetModuleHandle(TEXT("GameAssembly.dll"))) + EntListBase2)
			{
				if (enemy != nullptr)
				{
					if (enemy->fields.health >= 1)
					{
						if (enemy->fields.bstate != 5)
						{
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
					}
				}
				
			}
		}
	}
	else
	{
		if (offsets.GetPointerAddress(reinterpret_cast<uintptr_t>(GetModuleHandle("GameAssembly.dll")) + 0xB35CA8, { 0x5C,0x0C, (UINT)0x10 + i * 4,  0x28 }) != reinterpret_cast<uintptr_t>(GetModuleHandle("GameAssembly.dll")) + 0xB35CA8)
		{
			if (offsets.GetPointerAddress(reinterpret_cast<uintptr_t>(GetModuleHandle("GameAssembly.dll")) + EntListBase2, { 0x5C,0x0C, 0x10 + (UINT)i * 4,  0x28 }) != reinterpret_cast<uintptr_t>(GetModuleHandle(TEXT("GameAssembly.dll"))) + EntListBase2)
			{
				if (enemy != nullptr)
				{
					if (enemy->fields.health >= 1)
					{
						if (enemy->fields.bstate != 5)
						{
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
				}
				
			}
		}
	}
	
}
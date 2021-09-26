#include "Fov.h"
#include "framework/il2cpp-appdata.h"
#include "offsetsM.h"

app::PlayerData* GetPlayerDataSack(UINT32 i)
{

	offsetsM offsets;
	PlayerDataArray* pdataA = (PlayerDataArray*)(*app::PLH__TypeInfo)->static_fields->player;
	DWORD CHECK = (DWORD)pdataA->Player[i];
	if (CHECK < 0xfffff || CHECK == NULL || &CHECK == nullptr)
		return NULL;
	return pdataA->Player[i];
}

void FovView::Start()
{
	offsetsM offsets;
	bool sack = false;

	for (int i = 0; i < 40; i++)
	{		
		app::PlayerData* enemy = GetPlayerDataSack(i);
		if (enemy != nullptr)
		{
			sack = true;
			break;
		}
	}
	if (sack == true) // фиксить надо 
	{
		if ((*app::Controll__TypeInfo)->static_fields->csCam != nullptr)
		{
			if ((*app::Controll__TypeInfo)->static_fields->inZoom == true)
			{
				app::Camera_set_fieldOfView((*app::Controll__TypeInfo)->static_fields->csCam, 25, nullptr);
			}
			else
			{
				app::Camera_set_fieldOfView((*app::Controll__TypeInfo)->static_fields->csCam, viewFov, nullptr);
			}
		}
	}						
}


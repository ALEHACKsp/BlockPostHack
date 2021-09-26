#include "Crash.h"
#include "includes.h"
#include <cmath>
#include <array>
#include <iostream>
#include "framework/il2cpp-appdata.h"
ULONG val = 0;

void Crash::Render()
{
	app::WeaponInfo* wi = 0;
	if (active == true)
	{
		offsetsM offsets;
		DWORD crash = (DWORD)(*app::GUIInv__TypeInfo)->static_fields->wlist;
		
		int sack = (int)offsets.GetPointerAddress(crash + 8, { 0xC,0x0 });
		for (ULONG i = 0; i <= sack; i++)
		{
			if (offsets.GetPointerAddress(crash + 8, { 0x10 + i * 0x4,0x10,0x0 }) != crash + 8)
			{
				wi = (app::WeaponInfo*)offsets.GetPointerAddress(crash + 8, { 0x10 + i * 0x4,0x10,0x0 });

				if (wi->fields.id == 69)
				{
					wi->fields.id = 107;
					val = i;
					break;
				}
			}
		}
	}
	else
	{
		if (val != 0)
		{
			offsetsM offsets;
			DWORD crash = (DWORD)(*app::GUIInv__TypeInfo)->static_fields->wlist;
			if (offsets.GetPointerAddress(crash + 8, { 0x10 + val * 0x4,0x10,0x0 }) != crash + 8)
			{
				app::WeaponInfo* wi = (app::WeaponInfo*)offsets.GetPointerAddress(crash + 8, { 0x10 + val * 0x4,0x10,0x0 });
				wi->fields.id = 69;
			}
		}
	}
}


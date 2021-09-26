#include "MaxScoup.h"
#include "includes.h"

void MaxScoup::Start()
{

	
		offsetsM offsets;
		DWORD crash = (DWORD)(*app::GUIInv__TypeInfo)->static_fields->wlist;

		int sack = (int)offsets.GetPointerAddress(crash + 8, { 0xC,0x0 });
		for (ULONG i = 0; i <= sack; i++)
		{
			if (offsets.GetPointerAddress(crash + 8, { 0x10 + i * 0x4,0x10,0x0 }) != crash + 8)
			{
				int* frags = reinterpret_cast<int*>(offsets.GetPointerAddress(crash + 8, { 0x10 + i * 0x4,0x14 }));
				*frags = 9999;

			}
		}
	
}
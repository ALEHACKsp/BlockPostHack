#include "goThrowWall.h"
#include "framework/il2cpp-appdata.h"
#include "offsetsM.h"

//"GameAssembly.dll"+00B2468C 480 0 5c 10c

app::PlayerData* GetPlayerDataSSa(UINT32 i)
{
	offsetsM offsets;
	PlayerDataArray* pdataA = (PlayerDataArray*)(*app::PLH__TypeInfo)->static_fields->player;
	DWORD CHECK = (DWORD)pdataA->Player[i];
	if (CHECK < 0xfffff || CHECK == NULL || &CHECK == nullptr)
		return NULL;
	return pdataA->Player[i];
}

void goThrowWall::Start()
{
	app::PlayerData* enemy = GetPlayerDataSSa(0);
	
	offsetsM offsets;

	if (offsets.GetPointerAddress(reinterpret_cast<uintptr_t>(GetModuleHandle("GameAssembly.dll")) + 0x00B2468C, { 0x480,0x0,0x5C,0x10C }) != reinterpret_cast<uintptr_t>(GetModuleHandle("GameAssembly.dll")) + 0x00B2468C)
	{
		uintptr_t addr = offsets.GetPointerAddress(reinterpret_cast<uintptr_t>(GetModuleHandle("GameAssembly.dll")) + 0x00B2468C, { 0x480,0x0,0x5C,0x10C });

		float* posy = reinterpret_cast<float*>(addr);
		*posy = tpTo;

		Sleep(100);
	}		
}
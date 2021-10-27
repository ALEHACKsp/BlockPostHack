#include "Functions.h"
#include "PlayerDataArray.h"

bool Functions::GetEnemyLive(int i)
{
	uintptr_t baseModule = reinterpret_cast<uintptr_t>(GetModuleHandle(TEXT("GameAssembly.dll")));
	app::PlayerData* enemy = Functions::GetPlayerData(i);
	if (enemy == nullptr)
		return false;
	if (enemy->fields.currweapon == nullptr)
		return false;
	if (offsetsM::GetPointerAddress(baseModule + EntListBase2, { 0x5C,0x0C, 0x10 + (UINT)i * 4,  0x28 }) == baseModule + EntListBase2)
		return false;
	if (enemy->fields.health <= 1)
		return false;
	if (enemy->fields.bstate == 5)
		return false;
	return true;
}

app::PlayerData* Functions::GetPlayerData(int i)
{
	PlayerDataArray* pdataA = (PlayerDataArray*)(*app::PLH__TypeInfo)->static_fields->player;
	DWORD CHECK = (DWORD)pdataA->Player[i];
	if (CHECK < 0xfffff || CHECK == NULL || &CHECK == nullptr)
		return NULL;
	return pdataA->Player[i];
}
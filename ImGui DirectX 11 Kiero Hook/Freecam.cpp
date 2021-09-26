#include "framework/il2cpp-appdata.h"
#include "Freecam.h"
#include "offsetsM.h"

//void FreeCam::FreecamRec()  // нужно фиксить 
//{
//	offsetsM offsets;
//	uintptr_t baseModule = reinterpret_cast<uintptr_t>(GetModuleHandle(TEXT("GameAssembly.dll")));
//	if (offsets.GetPointerAddress(baseModule + 0xB35C3C, { 0x5C,0x80,0x8,0x20,0xE8 }) != baseModule + 0xB35C3C && offsets.GetPointerAddress(baseModule + 0xB35C3C, { 0x5C,0x80,0x8,0x20,0xE8 }) != 0)
//	{
//		float* rec = reinterpret_cast<float*>(offsets.GetPointerAddress(baseModule + 0xB35C3C, { 0x5C,0x80,0x8,0x20,0xE8 }));
//		*rec = 0;
//	}	
//}

void FreeCam::Render()
{
	app::Controll__StaticFields* sack = (*app::Controll__TypeInfo)->static_fields;
	sack->freefly = !sack->freefly;	
}
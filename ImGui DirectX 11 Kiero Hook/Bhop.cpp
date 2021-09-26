#include "Bhop.h"
#include "framework/il2cpp-appdata.h"
#include "includes.h"
#include "offsetsM.h"
#define Base 0xB35C3C

void Bhop::Start()
{
	offsetsM offsets;
	app::Controll__StaticFields* controll = (*app::Controll__TypeInfo)->static_fields;
	if (GetAsyncKeyState(VK_SPACE) )
	{
		if (controll->inAir == false)
		{
			if (controll->inAirFrame == 0)
			{
				float* sack = reinterpret_cast<float*>(offsets.GetPointerAddress(reinterpret_cast<uintptr_t>(GetModuleHandle("GameAssembly.dll")) + Base, { 0x5c,0x9c }));
				*sack = 2;
			}	
		}
	}
}
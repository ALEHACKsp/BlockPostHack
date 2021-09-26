#include "includes.h"
#include <vector>

DWORD  offsetsM::GetPointerAddress(DWORD ptr, std::vector<DWORD> offsets)
{
    DWORD addr = ptr;
    DWORD da = 24;
    if (&addr != nullptr && &addr != &da )
    {
        for (int i = 0; i < offsets.size(); ++i)
        {
            if (&addr != nullptr && addr != da )
            {
                addr = *(DWORD*)addr;
                if (addr && &addr != nullptr && addr != NULL)
                {
                    addr += offsets[i];
                }
                else
                {
                    return ptr;
                }
                
            }
        }
        return addr;
    }

}
void offsetsM::nopBytes(DWORD address, int size)
{

    DWORD OldProtection;
    VirtualProtect((LPVOID)address, size + 10, 0x40, &OldProtection);
    for (int i = 0; i < size; i++)
    {
        BYTE* Patched = reinterpret_cast<BYTE*>(address + i);
        *Patched = 0x90;
    }

}

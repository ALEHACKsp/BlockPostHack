#pragma once
#include "includes.h"
#include <vector>

class offsetsM
{
public:
	static DWORD GetPointerAddress(DWORD ptr, std::vector<DWORD> offsets);
	static void nopBytes(DWORD address, int size);
};
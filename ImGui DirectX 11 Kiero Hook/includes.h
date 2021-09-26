#pragma once
#define KEYMENY VK_INSERT
#define EntListBase 0xB35C3C
#define EntListBase2 0xB35CA8

#include <Windows.h>
#include <d3d11.h>
#include <dxgi.h>
#include "kiero/kiero.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_animated.h"
#include "offsetsM.h"
#include "Aim.h"
#include "PlayerDataArray.h"
#include "AutomaticW.h"


typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
typedef uintptr_t PTR;
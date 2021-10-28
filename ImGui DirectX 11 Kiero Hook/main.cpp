#include "includes.h"
#include "Settings.h"
#include <iostream>
#include <fstream>
#include <windows.h>
#include "framework/il2cpp-init.h"
#include "WallHack.h"
#include "Freecam.h";
#include "framework/il2cpp-appdata.h"
#include "Cross.h"
#include "Crash.h"
#include "Skeleton.h"
#include "Tracer.h"
#include "MaxScoup.h"
#include "Fov.h"
#include <iostream>
#include <string>
#include "goThrowWall.h"
#include "ChangeWeaponScale.h"
#include "Bhop.h"
#define WIN32_LEAN_AND_MEAN


Bhop bhop;
ChangeWeaponScale cwsS;
goThrowWall goThrowWalls;
FovView fovview;
MaxScoup msc;
Tracer tracer;
Skeleton skelet;
Crash crash;
CrossH cros;
USettings Settings;
Present oPresent;
HWND window = NULL;
WNDPROC oWndProc;
ID3D11Device* pDevice = NULL;
ID3D11DeviceContext* pContext = NULL;
ID3D11RenderTargetView* mainRenderTargetView;
AimBot aim;
WallHack wall;
FreeCam freeca;
const char* config1 = "config1";
const char* config2 = "config2";
const char* config3 = "config3";
static int tab = 3;
static int tabb = 5;
bool init = false;
bool DrawWatermark = true;
static const char* Croshairs[8]{ "DEFOLT", "WITH A DOT","DOT","WITHOUT LINE UP","DA","2 LINE","SACK","STRENG DOT" };
static const char* GameEvent[3]{ "NONE","WINTER", "HALLOWEEN" };
static const char* Figure[4]{ "Circle", "Rect","RectFilled","Rect (Regular)" };
static const char* cfg[3]{ config1, config2,config3 };
float colorSkyLight[4] = { 0.450f, 0.450f, 0.450f,0.1f };
static int selectedMode = 0;
static int selectiedCfg = 0;
float viewfovs = 65;
float  scale = 1;
bool show = true;
bool toggle = false;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void InitImGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(pDevice, pContext);
}

LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (show) {
		ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);

		return true;
	}
	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}
BOOL __stdcall StartThread(HMODULE hModule, LPTHREAD_START_ROUTINE StartAddress)
{
	return CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)StartAddress, hModule, 0, 0));
}


HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (!init)
	{
		if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
		{
			pDevice->GetImmediateContext(&pContext);
			DXGI_SWAP_CHAIN_DESC sd;
			pSwapChain->GetDesc(&sd);
			window = sd.OutputWindow;
			ID3D11Texture2D* pBackBuffer;
			pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			InitImGui();
			init = true;
		}

		else
			return oPresent(pSwapChain, SyncInterval, Flags);
	}
	
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	
	if (GetAsyncKeyState(KEYMENY) & 1)
	{
		show = !show;
	}
	if (show)
	{
		ImGui::GetBackgroundDrawList()->AddText({ 0,0 }, ImColor{ 10, 63, 255,255 }, "EZHACKBYSCUB");
		ImGui::Begin("BLOCKPOST-US");
		if (ImGui::Button(("Aim"), ImVec2(100.f, 0.f)))
			tabb = 0;
		ImGui::SameLine(0.f, 2.f);
		if (ImGui::Button(("Visuals"), ImVec2(100.f, 0.f)))
			tabb = 1;
		ImGui::SameLine(0.f, 2.f);
		if (ImGui::Button(("Misc"), ImVec2(100.f, 0.f)))
			tabb = 2;
		ImGui::SameLine(0.f, 2.f);
		if (ImGui::Button(("Info"), ImVec2(100.f, 0.f)))
			tabb = 3;
		ImGui::SameLine(0.f, 2.f);
		if (ImGui::Button(("CFG"), ImVec2(100.f, 0.f)))
			tabb = 4;
		ImGui::SameLine(0.f, 2.f);
		if (ImGui::Button(("COLORS"), ImVec2(100.f, 0.f)))
			tabb = 5;
		if (tabb == 0) {
			
			ImGui::Toggle("AimBot", &Settings.AimActive);
			ImGui::Toggle("AimBotKey", &Settings.AimKeyActive);
			ImGui::Toggle("TeamCheck", &Settings.TeamCheck);
			ImGui::Toggle("Visible Check", &aim.visiblecheck);
			ImGui::SliderFloat("Distance", &Settings.Dinstace, 1, 250);
			ImGui::SliderFloat("AimFov", &Settings.fov, 2.8, 360);
		}
		else if (tabb == 1) {
			ImGui::Toggle("WallHack", &Settings.Wallhack);
			ImGui::Toggle("Visible Check", &wall.visibleCheck);
			ImGui::Toggle("Skelet (DONT WORK WITH ANTICRASH!)", &Settings.Skelet);
			ImGui::Toggle("TeamCheck", &Settings.TeamCheck);
			ImGui::Toggle("Tracer", &Settings.Tracer);
			ImGui::SliderFloat("LineSize", &Settings.LineSize, 0, 10);			
			ImGui::SliderFloat("Fov", &fovview.viewFov, 0, 360);


		}
		else if (tabb == 2) {
		ImGui::Toggle("AllWeaponMaxScoup", &Settings.MaxScoup);
		ImGui::Toggle("AntiCrash", &Settings.AntiCrash);
		ImGui::Toggle("Big Man", &Settings.BigMan);
		ImGui::Toggle("Bhop", &Settings.Bhop);
		ImGui::Toggle("Crash  (BUTTON 4)", &Settings.Crash);
		ImGui::Toggle("Destroy Watter", &Settings.DestroyWatter);
		ImGui::Toggle("Freecam  ", &Settings.FreeCam);
		ImGui::Toggle("FackeDuck  ", &Settings.Duck);
		ImGui::Toggle("GoThrowWall", &Settings.ThrowWall);
		ImGui::SameLine(0.f, 2.f);
		ImGui::SliderInt("TpTo", &goThrowWalls.tpTo, 0, 400);
		ImGui::Toggle("NoFreez  ", &Settings.NoFreez);
		ImGui::Toggle("NoReload ", &Settings.NoReload);
		ImGui::Toggle("SpeedBoost  ", &Settings.SpeedBoost);
		ImGui::ListBox("CrossHair", &cros.selectItemDa, Croshairs, 8, 2); 
		ImGui::ListBox("GameEvent", &selectedMode, GameEvent, 3, 3);

		}
		else if (tabb == 3)
		{
		ImGui::Checkbox("Discord", &Settings.Discord);
		ImGui::Checkbox("YouTube", &Settings.YouTube);
		}
		else if (tabb == 4)
		{
		ImGui::Combo("CFG", &selectiedCfg, cfg, 3);
		if (ImGui::Button("Save", ImVec2(100.f, 0.f)))
			Settings.saveconfig = true;
		ImGui::SameLine(0.f, 2.f);
		if (ImGui::Button("Load", ImVec2(100.f, 0.f)))
			Settings.LoadConfig = true;
		ImGui::SameLine(0.f, 2.f);
		}
		else if (tabb = 5)
		{
		ImGui::ColorEdit4("WallHackColor", wall.colorWh);
		ImGui::ColorEdit4("WallHackColorInSpawnProtect", wall.colorWhS);
		ImGui::ColorEdit4("ColorTracer", tracer.colorTracer);
		ImGui::ColorEdit4("ColorSkelet", skelet.colorSkelet);
		ImGui::ColorEdit4("ColorSkeletSpawnProtect", skelet.colorSkeletS);
		ImGui::ColorEdit3("SkyLight (Direction Light)", colorSkyLight);
		}

		if (Settings.Wallhack)
			wall.Render();
		if (Settings.Skelet)
			skelet.Render();
		if (Settings.Tracer)
			tracer.Render();

		static int bg_alpha = 160;
		auto& drawlist = *ImGui::GetBackgroundDrawList();
		drawlist.AddRectFilled({ 0, 0 }, ImVec2(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)), IM_COL32(0, 0, 0, bg_alpha));

		ImGui::End();

		ImGui::Render();
	}
	else
	{
	ImGui::Begin("dasdas", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar);


	if (Settings.Wallhack)
		wall.Render();
	if (Settings.Skelet)
		skelet.Render();
	if (Settings.Tracer)
		tracer.Render();


	ImGui::End();
	ImGui::Render();
	}


	ImGui::EndFrame();
	pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return oPresent(pSwapChain, SyncInterval, Flags);
}



DWORD WINAPI FreeCamThread(HMODULE hMod)
{
	FreeCam freecam;
	offsetsM offsets;
	app::Controll__StaticFields* da = (*app::Controll__TypeInfo)->static_fields; // saksak 
	app::Main__StaticFields* main = (*app::Main__TypeInfo)->static_fields;
	
	offsets.nopBytes(reinterpret_cast<uintptr_t>(GetModuleHandle("GameAssembly.dll"))+0x2D9B16,7); // insert crash bypass


	while (true)
	{
		cros.Render();
		tracer.LineSize = Settings.LineSize;
		(*app::Crosshair__TypeInfo)->static_fields->crosshair_attack = 0;
		if (Settings.Bhop)
		{
			bhop.Start();
		}
		if (Settings.BigMan)
		{
			for (int i = 0; i < 40; i++)
			{
				cwsS.StartS(i, scale);
				cwsS.active = true;
			}
		}
		else
		{
			for (int i = 0; i < 40; i++)
			{
				cwsS.StartS(i, scale);
				cwsS.active = false;
			}

		}				
		if (selectedMode == 0)
		{
			main->winter = 0;
			main->halloween = 0;
		}
		if (selectedMode == 1)
		{
			main->winter = 1;
			main->halloween = 0;
		}
		if (selectedMode == 2)
		{
			main->winter = 0;
			main->halloween = 1;
		}				
		if (Settings.Duck)
		{
			da->inDuck = true;
			da->boxheight = 1.89;
		}
		if (Settings.NoFreez)
		{
			da->inStuck = false;
			da->inFreeze = false;
		}
		if (Settings.NoReload)
			da->inReload = false;
		if (Settings.MaxScoup)
			msc.Start();
		if (Settings.SpeedBoost)
			da->default_speed = 0.55f;	
		else
		{
			da->default_speed = 0.5f;
		}
	
		if (Settings.Crash)
		{
			crash.Render();
			crash.active = true;
		}
		else
		{			
			crash.Render();
			crash.active = false;
		}
		if (Settings.FreeCam)
		{
			if(GetAsyncKeyState(0x58) & 1)
			freecam.Render();
		}
		if (Settings.Discord)
		{
			ShellExecute(NULL, "open", "https://discord.gg/QwYW3vMN", NULL, NULL, SW_SHOW);
			Settings.Discord = false;
		}
		if (Settings.YouTube)
		{
			ShellExecute(NULL, "open", "www.youtube.com/channel/UC-jF6GNJZiaNY4SFKfjrNGw?sub_confirmation=1", NULL, NULL, SW_SHOW);
			Settings.YouTube = false;
		}
	}
	
	FreeLibraryAndExitThread(hMod, 0);
}
DWORD WINAPI FunctTread(HMODULE hMod)
{
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);
	AutomaticW asdddd; 
	DWORD OldProtection;
	uintptr_t baseModule = reinterpret_cast<uintptr_t>(GetModuleHandle(TEXT("GameAssembly.dll")));
	asdddd.Render();
	

	while (true)
	{
		
		

		aim.fov = 2+atan(aim.dist) * Settings.fov;
		aim.distanceFov = Settings.Dinstace;
		if (Settings.DestroyWatter)
		{
			if ((*app::Map__TypeInfo)->static_fields->goMapWater != nullptr)
			{
				
				app::Object_1_Destroy_1((app::Object_1*)(*app::Map__TypeInfo)->static_fields->goMapWater, nullptr);
				Settings.DestroyWatter = false;
			}
			
		}

		

		int fpsmax = reinterpret_cast<int>(GetModuleHandle(TEXT("UnityPlayer.dll"))) + 0x105E60C;
		if (*(int*)fpsmax > 201)
		{
			int* fpsmaxs = reinterpret_cast<int*>(fpsmax);
			*fpsmaxs = 200;
		}
		if (Settings.AimActive)		
			aim.Render();
		

		
		if (Settings.AimKeyActive)
			aim.toggle = true;
		else
		{			
			aim.toggle = false;
		}

		if (Settings.TeamCheck)
		{
			aim.teamcheck = true;
			wall.teamcheck = true;
			skelet.teamcheck = true;
			tracer.teamcheck = true;
		}
		else
		{
			aim.teamcheck = false;
			wall.teamcheck = false;
			skelet.teamcheck = false;
			tracer.teamcheck = false;
		}
		if (Settings.AntiCrash)
		{				
			BYTE* antcrash = reinterpret_cast<BYTE*>((uintptr_t)baseModule + 0x157100);
			*antcrash = 0xC3;
		}
		else
		{
			uintptr_t RsolverCrash = baseModule + 0x157100;
			VirtualProtect((LPVOID)RsolverCrash, 4, 0x40, &OldProtection);
			BYTE* antcrash = reinterpret_cast<BYTE*>((uintptr_t)baseModule + 0x157100);
			*antcrash = 0x80,0x3D,0x9F,0xAA,0x69,0x7A,0x00;
		}
	
		Sleep(100);
	}
	FreeLibraryAndExitThread(hMod, 0);
}

DWORD WINAPI ConfigThread(HMODULE hMod)
{
	app::GUIProfile__StaticFields* profile = (*app::GUIProfile__TypeInfo)->static_fields;
	app::GUIOptions__StaticFields* options = (*app::GUIOptions__TypeInfo)->static_fields;
	options->level = 0;


	while (true)
	{
		
		
		fovview.Start();
		//app::RenderSettings_set_ambientSkyColor(app::Color{ colorSkyLight[0], colorSkyLight[1], colorSkyLight[2],colorSkyLight[3] }, nullptr);
		
		if (Settings.saveconfig)
		{
			std::ofstream out1("cfg1.txt");
			out1 << Settings.AimActive << std::endl << Settings.AimKeyActive << std::endl << Settings.Crash << std::endl << Settings.Dinstace << std::endl << viewfovs << std::endl << Settings.fov << std::endl << Settings.FreeCam << std::endl << Settings.LineSize << std::endl << Settings.TeamCheck << std::endl << Settings.Tracer << std::endl << Settings.Wallhack << std::endl << tracer.colorTracer[0] << std::endl << tracer.colorTracer[1] << std::endl  << tracer.colorTracer[2] << std::endl  << tracer.colorTracer[3] << std::endl << wall.colorWh[0] << std::endl << wall.colorWh[1] << std::endl << wall.colorWh[2] << std::endl << wall.colorWh[3] << std::endl << wall.colorWhS[0] << std::endl << wall.colorWhS[1] << std::endl << wall.colorWhS[2] << std::endl << wall.colorWhS[3]   << std::endl << cros.selectItemDa << std::endl << Settings.Duck << std::endl << Settings.NoFreez << std::endl << Settings.NoReload << std::endl << Settings.SpeedBoost << std::endl << wall.selectiedFigure << std::endl << Settings.Skelet << std::endl << skelet.colorSkelet[0] << std::endl << skelet.colorSkelet[1] << std::endl << skelet.colorSkelet[2] << std::endl << skelet.colorSkelet[3] << std::endl << skelet.colorSkeletS[0] << std::endl << skelet.colorSkeletS[1] << std::endl << skelet.colorSkeletS[2] << std::endl << skelet.colorSkeletS[3];
			out1.close();
			Settings.saveconfig = false;
		}
		if (Settings.LoadConfig)
		{			
			std::string index[38];
			std::size_t count = 0;
			for (std::ifstream input("cfg1.txt"); (count < 38) && std::getline(input, index[count]); ++count)
			{
				// this space intentionally blank
			}
		
			Settings.AimActive = std::stoi(index[0]);
			Settings.AimKeyActive = std::stoi(index[1]);
			Settings.Crash = std::stoi(index[2]);
			Settings.Dinstace = std::stoi(index[3]);
			viewfovs = std::stoi(index[4]);
			Settings.fov = std::stoi(index[5]);
			Settings.FreeCam = std::stoi(index[6]);
			Settings.LineSize = std::stoi(index[7]);
			Settings.TeamCheck = std::stoi(index[8]);
			Settings.Tracer = std::stoi(index[9]);
			Settings.Wallhack = std::stoi(index[10]);
			tracer.colorTracer[0] = std::stof(index[11]);
			tracer.colorTracer[1] = std::stof(index[12]);
			tracer.colorTracer[2] = std::stof(index[13]);
			tracer.colorTracer[3] = std::stof(index[14]);
			wall.colorWh[0] = std::stof(index[15]);
			wall.colorWh[1] = std::stof(index[16]);
			wall.colorWh[2] = std::stof(index[17]);
			wall.colorWh[3] = std::stof(index[18]);
			wall.colorWhS[0] = std::stof(index[19]);
			wall.colorWhS[1] = std::stof(index[20]);
			wall.colorWhS[2] = std::stof(index[21]);
			wall.colorWhS[3] = std::stof(index[22]);
			cros.selectItemDa = std::stof(index[23]);
			Settings.Duck = std::stof(index[24]);
			Settings.NoFreez = std::stof(index[25]);
			Settings.NoReload = std::stof(index[26]);
			Settings.SpeedBoost = std::stof(index[27]);
			wall.selectiedFigure = std::stof(index[28]);
			Settings.Skelet = std::stof(index[29]);
			skelet.colorSkelet[0] = std::stof(index[30]);
			skelet.colorSkelet[1] = std::stof(index[31]);
			skelet.colorSkelet[2] = std::stof(index[32]);
			skelet.colorSkelet[3] = std::stof(index[33]);
			skelet.colorSkeletS[0] = std::stof(index[34]);
			skelet.colorSkeletS[1] = std::stof(index[35]);
			skelet.colorSkeletS[2] = std::stof(index[36]);
			skelet.colorSkeletS[3] = std::stof(index[37]);
			Settings.LoadConfig = false;
		}
	}
	FreeLibraryAndExitThread(hMod, 0);
}

DWORD WINAPI SackThread(HMODULE hMod)
{
	while (true)
	{
		if (Settings.ThrowWall || GetAsyncKeyState(0x5A) & 1)
		{
			goThrowWalls.Start();
		}		
		
	}
FreeLibraryAndExitThread(hMod, 0);
}
DWORD WINAPI MainThread(LPVOID lpReserved)
{
	bool init_hook = false;
	do
	{
		if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
		{
			kiero::bind(8, (void**)& oPresent, hkPresent);
			init_hook = true;
		}
	} while (!init_hook);
	return TRUE;
}


BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		init_il2cpp();
		DisableThreadLibraryCalls(hMod);
		CreateThread(nullptr, 0, MainThread, hMod, 0, nullptr);
		StartThread(nullptr, (LPTHREAD_START_ROUTINE)FunctTread);
		StartThread(nullptr, (LPTHREAD_START_ROUTINE)FreeCamThread);
		StartThread(nullptr, (LPTHREAD_START_ROUTINE)ConfigThread);
		StartThread(nullptr, (LPTHREAD_START_ROUTINE)SackThread);
		break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		break;
	}
	return TRUE;
} 
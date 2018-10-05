
/*
Big thanks to the following for this to be possible -

The entire AimTux Team
UC as a whole
Aixxe
TGF

others i cant think of right now

*/

#include "DllMain.h"
#include "Renderer.h"
bool StageEnd = false;

DWORD WINAPI Stage1(LPVOID hInstance)
{
	pGlowManager = *(CGlowObjectManager **)(FindPattern("client_panorama.dll", "\x0F\x11\x05\x00\x00\x00\x00\x83\xC8\x01\xC7\x05\x00\x00\x00\x00\x00\x00\x00\x00", "xxx????xxxxx????xxxx") + 3);
	KeyValues_KeyValues = FindPatternIDA("client_panorama.dll", "8B 0E 33 4D FC 81 E1 ? ? ? ? 31 0E 88 46 03 C1 F8 08 66 89 46 12 8B C6") - 0x45;
	KeyValues_LoadFromBuffer = FindPatternIDA("client_panorama.dll", "55 8B EC 83 E4 F8 83 EC 34 53 8B 5D 0C 89 4C 24 04");
	pPredSeed = *(int**)(FindPattern("client_panorama.dll", "\x8B\x0D\x00\x00\x00\x00\xBA\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x83\xC4\x04", "xx????x????x????xxx") + 2);
	dwPresent = (DWORD_PTR**)(FindPattern("gameoverlayrenderer.dll", "\xA3\x00\x00\x00\x00\x68\x00\x00\x00\x00\xFF\x76\x54\xE8\x00\x00\x00\x00\x83\xC4\x08\x84\xC0\x75\x17", "x????x????xxxx????xxxxxxx") + 1);
	pClientState = *(CClientState**)(FindPattern("engine.dll", "\x8B\x3D\x00\x00\x00\x00\x8A\xF9", "xx????xx") + 2); pClientState = *(CClientState**)(pClientState);
	pGameRules = *(CSGameRulesProxy***)(FindPattern("client_panorama.dll", "\xA1\x00\x00\x00\x00\x85\xC0\x0F\x84\x00\x00\x00\x00\x80\xB8\x00\x00\x00\x00\x00\x0F\x84\x00\x00\x00\x00\x0F\x10\x05", "x????xxxx????xx?????xx????xxx") + 0x1);
	csPlayerResource = *(C_CSPlayerResource***)(FindPattern("client_panorama.dll", "\xA1\x00\x00\x00\x00\x57\x85\xC0\x74\x08", "x????xxxxx") +1 );
	pD3device = **reinterpret_cast<IDirect3DDevice9***>(FindPattern("shaderapidx9.dll", "\xA1\x00\x00\x00\x00\x50\x8B\x08\xFF\x51\x0C", "x????xxxxxx") + 1);
	pMoveHelper = **(IMoveHelper***)(FindPattern("client_panorama.dll", "\x8B\x0D\x00\x00\x00\x00\x8B\x45\x00\x51\x8B\xD4\x89\x02\x8B\x01", "xx????xx?xxxxxxx") + 2);

	pGameMovement = (IGameMovement*)(CreateInterfaceFn(GetProcAddress(GetModuleHandleA("client_panorama.dll"), "CreateInterface"))	("GameMovement001", nullptr));
	pPrediction = (IPrediction*)(CreateInterfaceFn(GetProcAddress(GetModuleHandleA("client_panorama.dll"), "CreateInterface"))	("VClientPrediction001", nullptr));
	pInputSystem = (IInputSystem*)(CreateInterfaceFn(GetProcAddress(GetModuleHandleA("inputsystem.dll"), "CreateInterface"))	("InputSystemVersion001", nullptr));
	pSurface = (ISurface*)(CreateInterfaceFn(GetProcAddress(GetModuleHandleA("vguimatsurface.dll"), "CreateInterface"))		("VGUI_Surface031", nullptr));
	pPanel = (IVPanel*)(CreateInterfaceFn(GetProcAddress(GetModuleHandleA("vgui2.dll"), "CreateInterface"))		("VGUI_Panel009", nullptr));
	pPhysics = (IPhysicsSurfaceProps*)(CreateInterfaceFn(GetProcAddress(GetModuleHandleA("vphysics.dll"), "CreateInterface"))	("VPhysicsSurfaceProps001", nullptr));
	pMaterial = (IMaterialSystem*)(CreateInterfaceFn(GetProcAddress(GetModuleHandleA("materialsystem.dll"), "CreateInterface"))		("VMaterialSystem080", nullptr));
	pCvar = (ICvar*)(CreateInterfaceFn(GetProcAddress(GetModuleHandleA("materialsystem.dll"), "CreateInterface"))		("VEngineCvar007", nullptr));
	pGameui = (CGameUI*)(CreateInterfaceFn(GetProcAddress(GetModuleHandleA("client_panorama.dll"), "CreateInterface"))		("GameUI011", nullptr));
	pClient = (IBaseClientDLL*)(CreateInterfaceFn(GetProcAddress(GetModuleHandleA("client_panorama.dll"), "CreateInterface"))		("VClient018", nullptr));
	pEntityList = (IClientEntityList*)(CreateInterfaceFn(GetProcAddress(GetModuleHandleA("client_panorama.dll"), "CreateInterface"))		("VClientEntityList003", nullptr));
	pTrace = (IEngineTrace*)(CreateInterfaceFn(GetProcAddress(GetModuleHandleA("engine.dll"), "CreateInterface"))		("EngineTraceClient004", nullptr));
	pModelInfo = (IVModelInfo*)(CreateInterfaceFn(GetProcAddress(GetModuleHandleA("engine.dll"), "CreateInterface"))		("VModelInfoClient004", nullptr));
	pModelRender = (IVModelRender*)(CreateInterfaceFn(GetProcAddress(GetModuleHandleA("engine.dll"), "CreateInterface"))		("VEngineModel016", nullptr));
	pEngine = (IEngineClient*)(CreateInterfaceFn(GetProcAddress(GetModuleHandleA("engine.dll"), "CreateInterface"))		("VEngineClient014", nullptr));
	pDebugOverlay = (IVDebugOverlay*)(CreateInterfaceFn(GetProcAddress(GetModuleHandleA("engine.dll"), "CreateInterface"))		("VDebugOverlay004", nullptr));
	pGameEvent = (IGameEventManager2*)(CreateInterfaceFn(GetProcAddress(GetModuleHandleA("engine.dll"), "CreateInterface"))		("GAMEEVENTSMANAGER002", nullptr));
	pLocalize = (ILocalize*)(CreateInterfaceFn(GetProcAddress(GetModuleHandleA("localize.dll"), "CreateInterface"))		("Localize_001", nullptr));
	pEffects = (CEffects*)(CreateInterfaceFn(GetProcAddress(GetModuleHandleA("engine.dll"), "CreateInterface"))		("VEngineEffects001", nullptr));
	pSound = (IEngineSound*)(CreateInterfaceFn(GetProcAddress(GetModuleHandleA("engine.dll"), "CreateInterface"))		("IEngineSoundClient003", nullptr));

	pClientMode = **(IClientMode***)((*(DWORD**)pClient)[10] + 0x5);
	pGlobalVars = **(CGlobalVars***)((*(DWORD**)pClient)[0] + 0x1B);
	pInput = *(CInput**)(FindPatternIDA("client_panorama.dll", "B9 ? ? ? ? F3 0F 11 04 24 FF 50 10") + 1);
	
	NetVarManager::DumpNetvars();
	Offsets::GetOffsets();

	Settings::LoadSettings();

	esp_font = pSurface->CreateFontA();
	pSurface->SetFontGlyphSet(esp_font, "Tahoma", 15, 500, 0, 0, (int)FontFlags::FONTFLAG_OUTLINE);

	renderer.Initialize(FindWindowA("Valve001", NULL), pD3device);

	D3D9Hook = std::make_unique<VMTHook>(pD3device);
	D3D9Hook->HookFunction(Hooks::hReset, 16);
	D3D9Hook->HookFunction(Hooks::hkEndScene, 42);

	dwAddress = *dwPresent;
	//Present = (Present_t)(*dwAddress);
	//*dwAddress = (DWORD_PTR)(Hooks::hPresent);

	PanelHook = std::make_unique<VMTHook>(pPanel);
	PanelHook->HookFunction(Hooks::hPaintTraverse, 41);

	SurfaceHook = std::make_unique<VMTHook>(pSurface);
	SurfaceHook->HookFunction(Hooks::hPlaySounds, 82);

	MaterialHook = std::make_unique<VMTHook>(pMaterial);
	MaterialHook->HookFunction(Hooks::hBeginFrame, 42);


	ModelRenderHook = std::make_unique<VMTHook>(pModelRender);
	ModelRenderHook->HookFunction(Hooks::hDrawModelExecute, 21);

	ClientModeHook = std::make_unique<VMTHook>(pClientMode);
	ClientModeHook->HookFunction(Hooks::hCreateMove, 24);
	ClientModeHook->HookFunction(Hooks::hOverrideView, 18);
	ClientModeHook->HookFunction(Hooks::hGetViewModelFOV, 35);

	ClientHook = std::make_unique<VMTHook>(pClient);
	ClientHook->HookFunction(Hooks::hFrameStageNotify, 37);

	FireEventHook = std::make_unique<VMTHook>((DWORD**)pGameEvent);
	FireEventHook->HookFunction(Hooks::hFireEventClientSide, 9);

	//RenderViewHook = std::make_unique<VMTHook>(pViewRender);
	//RenderViewHook->HookFunction(Hooks::hRenderView, 6); seems to not work on some computers, not sure why

	//OpenConsole();
	//std::cout << fabs(clock() - Timer) / CLOCKS_PER_SEC;

	ExitThread(0);
}

DWORD WINAPI Stage2(LPVOID hInstance)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(10000));
	while (pInputSystem && !pInputSystem->IsButtonDown(KEY_END))
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	
	if (Open)
		FreeConsole();

	//std::this_thread::sleep_for(std::chrono::milliseconds(100));
	//*dwAddress = (DWORD_PTR)Present;

	//std::this_thread::sleep_for(std::chrono::milliseconds(100));
	//RenderViewHook->UnhookFunction(6);

	//std::this_thread::sleep_for(std::chrono::milliseconds(100));
	//SoundHook->UnhookFunction(5);

	//std::this_thread::sleep_for(std::chrono::milliseconds(100));
	//SoundHook->UnhookFunction(6);

	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	SurfaceHook->UnhookFunction(82);

	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	D3D9Hook->UnhookFunction(16);

	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	D3D9Hook->UnhookFunction(42);

	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	PanelHook->UnhookFunction(41);

	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	ModelRenderHook->UnhookFunction(21);

	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	ClientModeHook->UnhookFunction(18);

	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	ClientModeHook->UnhookFunction(24);

	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	ClientModeHook->UnhookFunction(35);

	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	ClientHook->UnhookFunction(37);

	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	FireEventHook->UnhookFunction(9);

	FreeLibraryAndExitThread(HINSTANCE(hInstance), 0);
}


BOOL WINAPI CreateThreads(HINSTANCE hInstance)
{
	return CreateThread(nullptr, 0, Stage1, hInstance, 0, nullptr) && CreateThread(nullptr, 0, Stage2, hInstance, 0, nullptr);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) 
{
	Timer = clock();
	if (fdwReason == 1 && FindWindow("Valve001", 0)) {
		return CreateThreads(hinstDLL);
	}
}

#include "Loader.h"

SlimUtils::SlimMem mem;
const SlimUtils::SlimModule* gameModule;
bool Loader::isRunning = true;

#if defined _M_X64
#pragma comment(lib, "MinHook.x64.lib")
#elif defined _M_IX86
#pragma comment(lib, "MinHook.x86.lib")
#endif

DWORD WINAPI ejectThread(LPVOID lpParam) {
	while (Loader::isRunning) {
		if ((GameData::isKeyDown(VK_CONTROL) && GameData::isKeyDown('L')) || GameData::isKeyDown(VK_END) || GameData::shouldTerminate()) {
			Loader::isRunning = false;  // Uninject
			break;
		}

		Sleep(20);
	}
	logF("Stopping Threads...");
	GameData::terminate();
	Sleep(50);  // Give the threads a bit of time to exit

	FreeLibraryAndExitThread(static_cast<HMODULE>(lpParam), 1);  // Uninject
}

#ifndef _MSC_VER
#define _MSC_VER "unk"
#endif

DWORD WINAPI start(LPVOID lpParam) {
	logF("Starting up...");
	logF("MSC v%i at %s", _MSC_VER, __TIMESTAMP__);
	init();

	DWORD procId = GetCurrentProcessId();
	if (!mem.Open(procId, SlimUtils::ProcessAccess::Full)) {
		logF("Failed to open process, error-code: %i", GetLastError());
		return 1;
	}
	gameModule = mem.GetModule(L"Minecraft.Windows.exe");  // Get Module for Base Address

	MH_Initialize();
	GameData::initGameData(gameModule, &mem, (HMODULE)lpParam);
	Target::init(Game.getPtrLocalPlayer());
	Hooks::Init();

	DWORD ejectThreadId;
	CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)ejectThread, lpParam, NULL, &ejectThreadId);  // Checking Keypresses
	logF("EjectThread: %i", ejectThreadId);

	cmdMgr->initCommands();
	logF("Initialized command manager (1/3)");
	moduleMgr->initModules();
	logF("Initialized module manager (2/3)");
	configMgr->init();
	logF("Initialized config manager (3/3)");

	Hooks::Enable();
	TabGui::init();
	ClickGui::init();

	logF("Hooks enabled");

	std::thread countThread([] {
		while (Loader::isRunning) {
			Sleep(1000);
			Game.fps = Game.frameCount;
			Game.frameCount = 0;
			Game.cpsLeft = Game.leftclickCount;
			Game.leftclickCount = 0;
			Game.cpsRight = Game.rightclickCount;
			Game.rightclickCount = 0;
		}
	});
	countThread.detach();

	logF("Count thread started");

	ExitThread(0);
}

BOOL __stdcall DllMain(HMODULE hModule,
					   DWORD ul_reason_for_call,
					   LPVOID) {
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH: {
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)start, hModule, NULL, NULL);
		DisableThreadLibraryCalls(hModule);
	} break;
	case DLL_PROCESS_DETACH:
		Loader::isRunning = false;

		configMgr->saveConfig();
		moduleMgr->disable();
		cmdMgr->disable();
		Hooks::Restore();

		logF("Removing logger");
		Logger::Disable();

		MH_Uninitialize();
		delete moduleMgr;
		delete cmdMgr;
		delete configMgr;
		if (Game.getLocalPlayer() != nullptr) {
			GuiData* guiData = Game.getClientInstance()->getGuiData();
			if (guiData != nullptr && !GameData::shouldHide())
				guiData->displayClientMessageF("%sEjected!", RED);
		}
		break;
	}
	return TRUE;
}

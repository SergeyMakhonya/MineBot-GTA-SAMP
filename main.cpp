
///////////////////
//  
//  Координаты шахты
//  X = -1832
//  Y = 21
//  Z = -1649
//  
///////////////////

#include <Windows.h>
#include "Bot.h"

HMODULE h;
Bot* bot;

DWORD WINAPI Hacks(LPVOID lpArgs)
{
	Init();

	bot = new Bot();

	while ( bot->Update() );

	DisableBot();

	return 1;
}

bool WINAPI DllMain(HMODULE hModule, DWORD Reason, LPVOID lpReserved)
{
	h = hModule;

	switch (Reason)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(0, 0, Hacks, 0, 0, 0);
		break;
	case DLL_PROCESS_DETACH:
		MessageBox(0, L"CLOSE MineBot by SergeyMakhonya", 0, 0);
		Sleep(5000);
		break;
	}

	return true;
}
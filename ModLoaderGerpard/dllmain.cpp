#include "pch.h"
#include <windows.h>
#include <iostream>
#include "Hooks/MinHook.h"
#ifdef _WIN64
#pragma comment(lib, "Hooks/libMinHook.x64.lib")
#else
#pragma comment(lib, "Hooks/libMinHook.x86.lib")
#endif

// Define the type of the original function
typedef void(*SWorldUpdateFn)(void*); // change this if SWorld::Update has different params

// Declare pointer to original function
SWorldUpdateFn oSWorldUpdate = nullptr;

// Define your hook
void hkSWorldUpdate(void* thisPtr) {
    std::cout << "[ModLoader] SWorld::Update Hooked!\n";

    // Call the original if needed
    if (oSWorldUpdate)
        oSWorldUpdate(thisPtr);
}

DWORD WINAPI InitThread(LPVOID) {
    // 🔧 Allocate console before any output
    AllocConsole();
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
    freopen_s((FILE**)stdin, "CONIN$", "r", stdin);
    freopen_s((FILE**)stderr, "CONOUT$", "w", stderr);

    SetConsoleTitleA("Gerpard Mod Loader Console");

    std::cout << "[ModLoader] Console initialized.\n";

    // Optional message box
    MessageBoxA(NULL, "Mod Loader Injected!", "ModLoaderGerpard", MB_OK);

    std::cout << "[ModLoader] Initializing hooks...\n";

    // Initialize MinHook
    if (MH_Initialize() != MH_OK) {
        std::cout << "[ModLoader] MH_Initialize failed!\n";
        return 1;
    }

    // Replace with real address!
    uintptr_t updateAddr = 0x00228000;

    if (MH_CreateHook((LPVOID)updateAddr, &hkSWorldUpdate, reinterpret_cast<LPVOID*>(&oSWorldUpdate)) != MH_OK) {
        std::cout << "[ModLoader] MH_CreateHook failed!\n";
        return 1;
    }

    if (MH_EnableHook((LPVOID)updateAddr) != MH_OK) {
        std::cout << "[ModLoader] MH_EnableHook failed!\n";
        return 1;
    }

    std::cout << "[ModLoader] Hooked SWorld::Update!\n";

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hModule);
        CreateThread(nullptr, 0, InitThread, nullptr, 0, nullptr);
    }
    return TRUE;
}

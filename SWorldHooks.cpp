// SWorldHooks.cpp
#include "MinHook.h"
#include <Windows.h>
#include <cstdio>

// Function pointer to the original function
typedef void(__thiscall* SWorldNew_t)(void* thisptr, int xsize, int zsize, int tileset);
SWorldNew_t originalSWorldNew = nullptr;

// Our detour function
void __fastcall HookedSWorldNew(void* thisptr, void* edx, int xsize, int zsize, int tileset)
{
    MessageBoxA(0, "SWorld::New called!", "Hook", 0);
    originalSWorldNew(thisptr, xsize, zsize, tileset);
}

void HookSWorldNew()
{
    // Replace with the actual address of SWorld::New from IDA
    uintptr_t targetAddr = 0x002242C0;

    MH_Initialize();
    MH_CreateHook(reinterpret_cast<LPVOID>(targetAddr), &HookedSWorldNew, reinterpret_cast<LPVOID*>(&originalSWorldNew));
    MH_EnableHook(reinterpret_cast<LPVOID>(targetAddr));
}
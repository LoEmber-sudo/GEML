#include <windows.h>
#include <iostream>
#include "MinHook.h" // assuming you have MinHook integrated

// Example of a function pointer and hook target
typedef void(__fastcall* tSWorldUpdate)(void* thisPtr);
tSWorldUpdate oSWorldUpdate = nullptr;

// Example hook function
void __fastcall hkSWorldUpdate(void* thisPtr) {
    OutputDebugStringA("[MOD] SWorld::Update() hooked!\n");

    // Call original function
    oSWorldUpdate(thisPtr);
}


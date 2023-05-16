// getmodulebase

#ifndef UNICODE
#define UNICODE
#endif

#ifndef _UNICODE
#define _UNICODE
#endif  

#include <vector>
#include <Windows.h>
#include <TlHelp32.h>
#include <string>

const std::vector<DWORD> FL32SA_OFFSET = { 0xC95B64, 0x24, 0xA8C, 0x4, 0x2C, 0x50, 0x264, 0x4C };

DWORD getModuleBase(const wchar_t* moduleName, DWORD processId) {
    // This structure contains lots of goodies about a module
    MODULEENTRY32 ModuleEntry = { 0 };
    // Grab a snapshot of all the modules in the specified process
    HANDLE SnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, processId);

    if (!SnapShot)
        return 0;

    // You have to initialize the size, otherwise it will not work
    ModuleEntry.dwSize = sizeof(ModuleEntry);

    // Get the first module in the process
    if (!Module32First(SnapShot, &ModuleEntry))
        return 0;

    do {
        // Check if the module name matches the one we're looking for
        if (!wcscmp(ModuleEntry.szModule, moduleName)) {
            // If it does, close the snapshot handle and return the base address
            CloseHandle(SnapShot);
            return (DWORD)ModuleEntry.modBaseAddr;
        }
        // Grab the next module in the snapshot
    } while (Module32Next(SnapShot, &ModuleEntry));

    // We couldn't find the specified module, so return NULL
    CloseHandle(SnapShot);
    return 0;
}

void goThroughPointerPath(DWORD &address, int &givenValue, const std::vector<DWORD> offsets, const DWORD &baseAddress, const HANDLE &processHandle) {
    SIZE_T bytesRead;
    givenValue = baseAddress;

    for (DWORD offset : offsets) {
        address = givenValue;
        address += offset;
        ReadProcessMemory(processHandle, (LPVOID)address, &givenValue, sizeof(givenValue), &bytesRead);
    }
}
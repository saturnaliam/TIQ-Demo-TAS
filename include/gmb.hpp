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

const std::vector<DWORD_PTR> FL32SA_OFFSET = { 0xC95B64, 0x24, 0xA8C, 0x4, 0x2C, 0x50, 0x264, 0x4C };

DWORD getDwordFromBytes(BYTE* b)
{
    return (b[0]) | (b[1] << 8) | (b[2] << 16) | (b[3] << 24);
}

uintptr_t getModuleBase(DWORD processId, const WCHAR* windowTitle)
{
    HWND windowHandle = FindWindow(NULL, windowTitle);
    if (!windowHandle)
    {
        return 0;
    }

    DWORD processIdFound = 0;
    GetWindowThreadProcessId(windowHandle, &processIdFound);
    if (processIdFound != processId)
    {
        return 0;
    }

    HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
    if (!processHandle)
    {
        return 0;
    }

    MODULEENTRY32 moduleEntry = { sizeof(moduleEntry) };
    uintptr_t moduleBaseAddress = 0;
    HANDLE snapshotHandle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processId);
    if (Module32First(snapshotHandle, &moduleEntry))
    {
        do
        {
            if (_wcsicmp(moduleEntry.szModule, L"flashplayer_32_sa.exe") == 0)
            {
                moduleBaseAddress = reinterpret_cast<uintptr_t>(moduleEntry.modBaseAddr);
            }
        } while (Module32Next(snapshotHandle, &moduleEntry));
    }

    CloseHandle(snapshotHandle);
    CloseHandle(processHandle);

    return moduleBaseAddress;
}

void goThroughPointerPath(DWORD_PTR &address, int &givenValue, const std::vector<DWORD_PTR> offsets, const DWORD_PTR &baseAddress, const HANDLE &processHandle) {
    SIZE_T bytesRead;
    givenValue = baseAddress;

    for (DWORD_PTR offset : offsets) {
        address = givenValue;
        address += offset;
        ReadProcessMemory(processHandle, (LPVOID)address, &givenValue, sizeof(givenValue), &bytesRead);
    }
}
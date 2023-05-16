#ifndef UNICODE
#define UNICODE
#endif

#ifndef _UNICODE
#define _UNICODE
#endif  

#include <Windows.h>
#include <iostream>
#include "include/tm.hpp"
#include "include/gmb.hpp"

void leftClick() {  
    INPUT Input = {0};
    for(int i = 0; i <= 1; ++i) {
        Input.type = INPUT_MOUSE;
        Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
        ::SendInput(1, &Input, sizeof(INPUT));
        
        ::ZeroMemory(&Input, sizeof(INPUT));
        Input.type = INPUT_MOUSE;
        Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
        ::SendInput(1, &Input, sizeof(INPUT));
    }
}

int main() {
    DWORD PID;
    DWORD address;
    int scene, offsetX, offsetY;

    const HWND windowHandle = FindWindow(nullptr, L"Adobe Flash Player 32");
    GetWindowThreadProcessId(windowHandle, &PID);

    const HANDLE processHandle = OpenProcess(PROCESS_VM_READ, FALSE, PID);

    const DWORD baseAddress = getModuleBase(L"flashplayer_32_sa.exe", PID);

    goThroughPointerPath(address, scene, FL32SA_OFFSET, baseAddress, processHandle);
    
    SIZE_T bytesRead;

    RECT rect = {0};
    GetWindowRect(windowHandle, &rect);

    for (TAS_MOVE movement : movements) {
        offsetX = movement.cursorPosition.x + rect.left + COORD_OFFSET_X;
        offsetY = movement.cursorPosition.y + rect.top + COORD_OFFSET_Y;

        while (scene != movement.scene) ReadProcessMemory(processHandle, (LPVOID)address, &scene, sizeof(scene), &bytesRead);

        SetCursorPos(offsetX, offsetY);
        leftClick();
    }
}
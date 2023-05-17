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

INPUT sendClick = {0};
INPUT sendUp = {0};
inline void leftClick() {  
    INPUT Input = {0};
    for(int i = 0; i <= 1; ++i) {
        ::SendInput(1, &sendClick, sizeof(INPUT));

        ::SendInput(1, &sendUp, sizeof(INPUT));
    }
}

int main() {
    sendClick.type = INPUT_MOUSE;
    sendClick.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    sendUp.type = INPUT_MOUSE;
    sendUp.mi.dwFlags = MOUSEEVENTF_LEFTUP;

    DWORD PID, address;
    int scene, offsetX, offsetY;
    char c;
    
    const HWND windowHandle = FindWindow(nullptr, L"Adobe Flash Player 32");
    GetWindowThreadProcessId(windowHandle, &PID);

    const HANDLE processHandle = OpenProcess(PROCESS_VM_READ, FALSE, PID);

    const DWORD baseAddress = getModuleBase(L"flashplayer_32_sa.exe", PID);

    goThroughPointerPath(address, scene, FL32SA_OFFSET, baseAddress, processHandle);
    
    SIZE_T bytesRead;

    RECT rect = {0};
    GetWindowRect(windowHandle, &rect);

    userInput:
        system("cls");
        printf("Choose [s]afe or [f]ast execution: ");
        scanf("%c", &c);
        if (c == 's') goto safeMove;
        if (c == 'f') goto fastMove;
        goto userInput;


    safeMove:
        for (TAS_MOVE movement : movements) {
            offsetX = movement.cursorPosition.x + rect.left + COORD_OFFSET_X;
            offsetY = movement.cursorPosition.y + rect.top + COORD_OFFSET_Y;

            while (scene != movement.scene) ReadProcessMemory(processHandle, (LPVOID)address, &scene, sizeof(scene), &bytesRead);

            SetCursorPos(offsetX, offsetY);
            leftClick();
        }

        goto endProgram;

    fastMove:
        for (TAS_MOVE movement : movements) {
            offsetX = movement.cursorPosition.x + rect.left + COORD_OFFSET_X;
            offsetY = movement.cursorPosition.y + rect.top + COORD_OFFSET_Y;

            SetCursorPos(offsetX, offsetY);
            leftClick();
        }

    endProgram:
        CloseHandle(processHandle);
}
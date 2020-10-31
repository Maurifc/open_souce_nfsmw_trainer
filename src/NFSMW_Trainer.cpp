#include "memory.h"
#include "proc.h"
#include <iostream>
#include <Windows.h>

int main(void)
{
    HANDLE hProcess;
    DWORD processId;
    DWORD dwExit;
    SHORT keyPressed;
    uintptr_t modBaseAddr;
    uintptr_t firstPointerAddr;
    uintptr_t decreaseMoneyAddr;
    uintptr_t speedTrapAddr;
    const float speedTrapTotal = 2000.0;
    bool toggleNoFees = false;

    processId = Process::getProcessId(L"speed.exe");

    if (processId == 0) {
        std::cout << "Falha ao obter process id!";
        return 1;
    }

    hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, processId);

    if (hProcess == INVALID_HANDLE_VALUE) {
        std::cout << "Falha ao abrir processo ID: " << processId << std::endl;
        return 1;
    }

    modBaseAddr = Process::getModuleBaseAddr(processId, L"speed.exe");
    firstPointerAddr = modBaseAddr + 0x0052FDC4;
    decreaseMoneyAddr = modBaseAddr + 0x16d7b5;
    speedTrapAddr = Process::resolvePointers(hProcess, firstPointerAddr, { 0x138 });

    while (GetExitCodeProcess(hProcess, &dwExit) && dwExit == STILL_ACTIVE) {
        //Speed Trap 99999Km
        if (GetAsyncKeyState(VK_NUMPAD1) & 1) {
            WriteProcessMemory(hProcess, (BYTE*)speedTrapAddr, &speedTrapTotal, sizeof(speedTrapTotal), NULL);
            std::cout << "Total Speed Trap = " << speedTrapTotal << std::endl;
        //No fees
        } else if (GetAsyncKeyState(VK_NUMPAD2) & 1) {
            toggleNoFees = !toggleNoFees;

            if (toggleNoFees) {
                Memory::PatchWithNop(hProcess, (BYTE*)decreaseMoneyAddr, 2);
                std::cout << "No fees cheat enabled" << std::endl;
            } else {
                Memory::Patch(hProcess, (BYTE*)decreaseMoneyAddr, (BYTE*)"\x2b\xc2", 2);
                std::cout << "No fees cheat disabled" << std::endl;
            }
       }

        Sleep(10);
    }

    CloseHandle(hProcess);
    return 0;
}
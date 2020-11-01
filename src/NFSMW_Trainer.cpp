#include <iostream>
#include <Windows.h>
#include "NFSMW.h"

int main(void)
{
    DWORD dwExit;
    NFSMW nfsmw;

    while (GetExitCodeProcess(nfsmw.getProcessHandle(), &dwExit) && dwExit == STILL_ACTIVE) {
        //Speed Trap 99999Km
        if (GetAsyncKeyState(VK_NUMPAD1) & 1) {      
            nfsmw.enableSpeedTrapCheat();
        //No fees
        } else if (GetAsyncKeyState(VK_NUMPAD2) & 1) {
            nfsmw.toggleZeroCostCheat();
        //Infinity Nitro
        } else if (GetAsyncKeyState(VK_NUMPAD3) & 1) {
            nfsmw.toggleInfinityNitroCheat();
       }

       Sleep(10);
    }

    return 0;
}
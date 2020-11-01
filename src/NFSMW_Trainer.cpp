#include <iostream>
#include <Windows.h>
#include "NFSMW.h"

void printWaitingMessage() {
    system("cls");
    std::cout << "Waiting for NFSMW to be opened...\n";
}

void showMenu() {
    system("cls");
    std::cout <<
        "****************************************\n"
        "*                                      *\n"
        "*                                      *\n"
        "*      Open Source NFSMW Trainer       *\n"
        "*           Learn and play!            *\n"
        "*                                      *\n"
        "*                                      *\n"
        "*****************************************\n"
        "*****************************************\n"
        "*                                      *\n"
        "* NUMPAD 1 - Infinity Nitro            *\n"
        "* NUMPAD 2 - No Money Cost             *\n"
        "* NUMPAD 3 - Speed Trap (99.999Kmh)    *\n"
        "*                                      *\n"
        "****************************************\n\n\n";
}
int main(void)
{
    DWORD dwExit;
    NFSMW nfsmw;

    while (1) {
        while (!nfsmw.attach()) {
            Sleep(3000);
            printWaitingMessage();
        }

        showMenu();

        while (GetExitCodeProcess(nfsmw.getProcessHandle(), &dwExit) && dwExit == STILL_ACTIVE) {
            //Infinity Nitro
            if (GetAsyncKeyState(VK_NUMPAD1) & 1) {
                nfsmw.toggleInfinityNitroCheat();

                //Zero Cost
            }
            else if (GetAsyncKeyState(VK_NUMPAD2) & 1) {
                nfsmw.toggleZeroCostCheat();

                //Speed Trap 99999Km
            }
            else if (GetAsyncKeyState(VK_NUMPAD3) & 1) {
                nfsmw.enableSpeedTrapCheat();
            }

            Sleep(10);
        }

        nfsmw.detach();
    }    

    return 0;
}
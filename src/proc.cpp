#include "proc.h"
#include <vector>
#include <Windows.h>
#include <TlHelp32.h>

namespace Process {
	DWORD getProcessId(const wchar_t* processName) {
		DWORD processId = 0;
		HANDLE hSnap;
		PROCESSENTRY32 pe32;

		hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		if (hSnap == INVALID_HANDLE_VALUE) {
			std::cout << "Fail when getting snapshot." << std::endl;
			return 0;
		}

		pe32.dwSize = sizeof(pe32);

		if (!Process32First(hSnap, &pe32)) {
			std::cout << "Fail when getting first process." << std::endl;
			CloseHandle(hSnap);
			return 0;
		}

		do {
			if (_wcsicmp(processName, pe32.szExeFile) == 0) {
				processId = pe32.th32ProcessID;
				break;
			}
		} while (Process32Next(hSnap, &pe32));

		CloseHandle(hSnap);
		return processId;
	}

	uintptr_t getModuleBaseAddr(const DWORD processId, const wchar_t * processName) {
		uintptr_t moduleBaseAddr = 0;
		MODULEENTRY32 me32;
		HANDLE hSnap;

		hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processId);

		if (hSnap == INVALID_HANDLE_VALUE) {
			std::cout << "Fail when getting modules snapshot." << std::endl;
			return 0;
		}

		me32.dwSize = sizeof(me32);

		if (!Module32First(hSnap, &me32)) {
			std::cout << "Fail when getting first module." << std::endl;
			CloseHandle(hSnap);
			return 0;
		}

		do {
			if (_wcsicmp(processName, me32.szModule) == 0) {
				moduleBaseAddr = (uintptr_t) me32.modBaseAddr;
				break;
			}
		} while (Module32Next(hSnap, &me32));

		CloseHandle(hSnap);
		return moduleBaseAddr;
	}

	uintptr_t resolvePointers(const HANDLE hProcess, const uintptr_t addr, const std::vector<UINT32>& offsets) {
		uintptr_t finalPtr = addr;

		for (auto offset : offsets) {
			ReadProcessMemory(hProcess, (BYTE*) finalPtr, &finalPtr, sizeof(addr), NULL);
			finalPtr += offset;
		}

		return finalPtr;
	}
}
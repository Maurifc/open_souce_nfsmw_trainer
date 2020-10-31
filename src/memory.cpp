#include "memory.h"
#include <Windows.h>

namespace Memory {
	void Patch(HANDLE hProcess, BYTE* addr, BYTE* src, size_t size) {
		DWORD oldProtect;

		VirtualProtectEx(hProcess, addr, size, DDL_READWRITE, &oldProtect);
		WriteProcessMemory(hProcess, addr, src, size, NULL);
		VirtualProtectEx(hProcess, addr, size, oldProtect, &oldProtect);
	}

	void PatchWithNop(HANDLE hProcess, BYTE* addr, size_t size) {
		BYTE* nopArray = new BYTE[size];
		memset(nopArray, 0x90, size);

		Patch(hProcess, addr, nopArray, size);
	}
}

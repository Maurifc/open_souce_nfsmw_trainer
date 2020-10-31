#pragma once
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <vector>

namespace Process {
	DWORD getProcessId(const wchar_t* processName);
	uintptr_t getModuleBaseAddr(const DWORD processId, const wchar_t* processName);
	uintptr_t resolvePointers(const HANDLE hProcess, const uintptr_t addr, const std::vector<UINT32>& offsets);
}


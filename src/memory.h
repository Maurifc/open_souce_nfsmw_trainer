#pragma once
#include <Windows.h>

namespace Memory {
	void Patch(HANDLE hProcess, BYTE* addr, BYTE* src, size_t size);
	void PatchWithNop(HANDLE hProcess, BYTE* addr, size_t size);
}


#pragma once
#include <iostream>
#include <Windows.h>

class NFSMW
{
private:
	HANDLE m_hProcess = INVALID_HANDLE_VALUE;
	DWORD m_processId;
	uintptr_t m_modBaseAddr;
	uintptr_t m_firstPointerAddr;
	uintptr_t m_zeroCostAddr;
	uintptr_t m_speedTrapAddr;
	uintptr_t m_infinityNitroAddr;
	const float m_speedTrapTotal = 99999.0;
	bool m_bZeroCostEnabled = false;
	bool m_bInfinityNitroEnabled = false;

public:
	NFSMW();
	~NFSMW();

	HANDLE& getProcessHandle() { return m_hProcess; }

	void enableSpeedTrapCheat();

	void toggleZeroCostCheat();

	void toggleInfinityNitroCheat();
};
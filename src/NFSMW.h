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
	uintptr_t m_unlockCarsAddr;
	const float m_speedTrapTotal = 99999.0;
	bool m_bZeroCostEnabled = false;
	bool m_bInfinityNitroEnabled = false;
	bool m_unlockCarsEnabled = false;
	bool m_isAttached = false;

public:
	NFSMW() {};
	~NFSMW();

	HANDLE& getProcessHandle() { return m_hProcess; }
	bool isAttached() { return m_isAttached; }

	bool attach();
	void detach();

	void enableSpeedTrapCheat();
	void toggleZeroCostCheat();
	void toggleInfinityNitroCheat();
	void toggleUnlockCars();
};
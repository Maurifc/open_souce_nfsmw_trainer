#pragma once
#include <iostream>
#include <Windows.h>

class NFSMW
{
private:
	HANDLE m_hProcess = INVALID_HANDLE_VALUE;
	DWORD m_processId;
	uintptr_t m_modBaseAddr;
	bool m_zeroCostEnabled = false;
	bool m_infinityNitroEnabled = false;
	bool m_unlockCarsEnabled = false;
	bool m_isAttached = false;

public:
	NFSMW() {};
	~NFSMW();

	HANDLE& getProcessHandle() { return m_hProcess; }
	bool isAttached() { return m_isAttached; }

	bool attach();
	void detach();

	void setSpeedTrapTotalSpeed(const float totalSpeed);
	void toggleZeroCostCheat();
	void toggleInfinityNitroCheat();
	void toggleUnlockAllSellingCars();
	void addMoney(UINT32 count);
};
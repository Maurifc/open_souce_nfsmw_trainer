#include <cassert>
#include <iostream>
#include <Windows.h>
#include "proc.h"
#include "memory.h"
#include "NFSMW.h"

NFSMW::~NFSMW() {
	if (m_hProcess != INVALID_HANDLE_VALUE)
		CloseHandle(m_hProcess);
}

bool NFSMW::attach() {
	if (m_isAttached) {
		std::cout << "Already attached!" << std::endl;
		return false;
	}

	m_processId = Process::getProcessId(L"speed.exe");

	if (m_processId == 0) {
		std::cout << "Failed when getting process Id!";
		return false;
	}

	m_hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, m_processId);

	if (m_hProcess == INVALID_HANDLE_VALUE) {
		std::cout << "Failed when opening process ID: " << m_processId << std::endl;
		return false;
	}

	//Base Address
	m_modBaseAddr = Process::getModuleBaseAddr(m_processId, L"speed.exe");

	//Instructions' adresses to be patched
	m_zeroCostAddr = m_modBaseAddr + 0x16d7b5;
	m_infinityNitroAddr = m_modBaseAddr + 0x292B01;
	m_unlockCarsAddr = m_modBaseAddr + 0x18a644;

	m_isAttached = true;
	return true;
}

void NFSMW::detach() {
	m_isAttached = false;
}

void NFSMW::enableSpeedTrapCheat() {
	assert(this->isAttached());

	//Resolving multipointers
	m_firstPointerAddr = m_modBaseAddr + 0x52FDC4;
	m_speedTrapAddr = Process::resolvePointers(m_hProcess, m_firstPointerAddr, { 0x138 });

	WriteProcessMemory(m_hProcess, (BYTE*)m_speedTrapAddr, &m_speedTrapTotal, sizeof(m_speedTrapTotal), NULL);
	std::cout << "Speed Trap Cheat Enabled " << std::endl;
}

void NFSMW::toggleZeroCostCheat() {
	assert(this->isAttached());

	m_bZeroCostEnabled = !m_bZeroCostEnabled;

	if (m_bZeroCostEnabled) {
		Memory::PatchWithNop(m_hProcess, (BYTE*)m_zeroCostAddr, 2);
		std::cout << "Zero Cost Cheat Enabled" << std::endl;
	}
	else {
		// Old Instruction (sub eax,edx) = 2B C2
		Memory::Patch(m_hProcess, (BYTE*)m_zeroCostAddr, (BYTE*)"\x2b\xc2", 2);
		std::cout << "Zero Cost Cheat Disabled" << std::endl;
	}
}

void NFSMW::toggleInfinityNitroCheat() {
	assert(this->isAttached());

	m_bInfinityNitroEnabled = !m_bInfinityNitroEnabled;

	if (m_bInfinityNitroEnabled) {
		Memory::PatchWithNop(m_hProcess, (BYTE*)m_infinityNitroAddr, 4);
		std::cout << "Infinity Nitro Cheat Enabled" << std::endl;
	}
	else {
		// Old Instruction (fsub dword ptr [esp+2C]) = D8 64 24 2C
		Memory::Patch(m_hProcess, (BYTE*)m_infinityNitroAddr, (BYTE*)"\xd8\x64\x24\x2c", 4);
		std::cout << "Infinity Nitro Cheat Disabled" << std::endl;
	}
}

void NFSMW::toggleUnlockCars() {
	assert(this->isAttached());

	m_unlockCarsEnabled = !m_unlockCarsEnabled;

	if (m_unlockCarsEnabled) {
		//New instruction: mov bl,01 = b3 01 90 90 90 90
		Memory::Patch(m_hProcess, (BYTE*)m_unlockCarsAddr, (BYTE*)"\xb3\x01\x90\x90\x90\x90", 6);
		std::cout << "Unlock all Career's Cars Cheat Enabled" << std::endl;
	}
	else {
		// Old Instruction: mov bl,[eax+000000B0] = 8A 98 B0 00 00 00
		Memory::Patch(m_hProcess, (BYTE*)m_unlockCarsAddr, (BYTE*)"\x8A\x98\xB0\x00\x00\x00", 6);
		std::cout << "Unlock all Career's Cars Cheat Disabled" << std::endl;
	}
}
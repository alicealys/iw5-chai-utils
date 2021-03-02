// Copyright 2020 xensik. All Rights Reserved.

#include "stdinc.hpp"

namespace utils::hook
{
	void* allocate_stub_memory(size_t size)
	{
		return VirtualAlloc(0, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	}

	detour::detour(std::uintptr_t address, void* hook, int len)
		: detour(address, reinterpret_cast<std::uintptr_t>(hook), len) { }


	detour::~detour()
	{

	}

	detour::detour(std::uintptr_t address, std::uintptr_t hook, int len)
	{
		uintptr_t trampoline = (uintptr_t)allocate_stub_memory(len + 5);

		std::memcpy((void*)trampoline, (void*)address, len);

		*(uint8_t*)(trampoline + len) = 0xE9;
		*(uintptr_t*)(trampoline + len + 1) = (intptr_t)address - (intptr_t)trampoline - 5;

		DWORD oldProtect;
		VirtualProtect((void*)address, len, PAGE_EXECUTE_READWRITE, &oldProtect);

		*(uint8_t*)(address) = 0xE9;
		*(uintptr_t*)((uintptr_t)address + 1) = (intptr_t)hook - (intptr_t)address - 5;

		if (len > 5)
		{
			std::memset((void*)((uintptr_t)address + 5), 0x90, len - 5);
		}

		VirtualProtect((void*)address, len, oldProtect, &oldProtect);

		this->target_ = trampoline;
		this->address_ = address;
	}
}
// Copyright 2020 xensik. All Rights Reserved.

#pragma once

namespace utils
{

namespace hook
{
	static void* allocate_stub_memory(size_t size);

	template<typename value_type, typename addr_type>
	static inline value_type get(addr_type address)
	{
		return *static_cast<value_type*>(address);
	}

	template<typename value_type, typename addr_type>
	static inline void set(addr_type address, value_type value)
	{
		DWORD oldProtect;
		VirtualProtect((void*)address, sizeof(value), PAGE_EXECUTE_READWRITE, &oldProtect);

		std::memcpy((void*)address, &value, sizeof(value));

		VirtualProtect((void*)address, sizeof(value), oldProtect, &oldProtect);
	}

	template<typename value_type, typename addr_type>
	static inline void set(addr_type address, const char* data, size_t length)
	{
		DWORD oldProtect;
		VirtualProtect((void*)address, sizeof(value_type) * length, PAGE_EXECUTE_READWRITE, &oldProtect);

		std::memcpy((void*)address, data, sizeof(value_type) * length);

		VirtualProtect((void*)address, sizeof(value_type) * length, oldProtect, &oldProtect);
	}

	template<typename addr_type>
	static inline void nop(addr_type address, size_t length)
	{
		DWORD oldProtect;
		VirtualProtect((void*)address, length, PAGE_EXECUTE_READWRITE, &oldProtect);

		std::memset((void*)address, 0x90, length);

		VirtualProtect((void*)address, length, oldProtect, &oldProtect);
	}

	template<typename func_type, typename addr_type>
	static inline void jump(addr_type address, func_type hook)
	{
		DWORD oldProtect;
		VirtualProtect((void*)address, 5, PAGE_EXECUTE_READWRITE, &oldProtect);

		*(uint8_t*)address = 0xE9;
		*(uintptr_t*)((uintptr_t)address + 1) = (intptr_t)hook - (intptr_t)address - 5;

		VirtualProtect((void*)address, 5, oldProtect, &oldProtect);
	}

	template<typename func_type, typename addr_type>
	static inline void jump(addr_type address, func_type hook, size_t nops)
	{
		DWORD oldProtect;
		VirtualProtect((void*)address, 5 + nops, PAGE_EXECUTE_READWRITE, &oldProtect);

		*(uint8_t*)(address) = 0xE9;
		*(uintptr_t*)((uintptr_t)address + 1) = (intptr_t)hook - (intptr_t)address - 5;
		std::memset((void*)((uintptr_t)address + 5), 0x90, nops);

		VirtualProtect((void*)address, 5 + nops, oldProtect, &oldProtect);
	}

	template<typename func_type, typename addr_type>
	static inline void call(addr_type address, func_type hook)
	{
		DWORD oldProtect;
		VirtualProtect((void*)address, 5, PAGE_EXECUTE_READWRITE, &oldProtect);

		*(uint8_t*)(address) = 0xE8;
		*(uintptr_t*)((uintptr_t)address + 1) = (intptr_t)hook - (intptr_t)address - 5;

		VirtualProtect((void*)address, 5, oldProtect, &oldProtect);
	}

	template<typename func_type, typename addr_type>
	static inline void call(addr_type address, func_type hook, size_t nops)
	{
		DWORD oldProtect;
		VirtualProtect((void*)address, 5 + nops, PAGE_EXECUTE_READWRITE, &oldProtect);

		*(uint8_t*)(address) = 0xE8;
		*(uintptr_t*)((uintptr_t)address + 1) = (intptr_t)hook - (intptr_t)address - 5;
		std::memset((void*)((uintptr_t)address + 5), 0x90, nops);

		VirtualProtect((void*)address, 5 + nops, oldProtect, &oldProtect);
	}


	class detour
	{
	private:
		std::uintptr_t address_{};
		std::uintptr_t target_{};

	public:
		detour() = default;
		detour(std::uintptr_t address, void* hook, int len = 5);
		detour(std::uintptr_t address, std::uintptr_t hook, int len = 5);
		~detour();

		template <typename T>
		T invoke()
		{
			return reinterpret_cast<T(*)()>(this->target_)();
		}

		template <typename T, typename... Args>
		T invoke(Args... args)
		{
			return reinterpret_cast<T(*)(Args ...)>(this->target_)(args...);
		}
	};

};

} // namesapce xsk

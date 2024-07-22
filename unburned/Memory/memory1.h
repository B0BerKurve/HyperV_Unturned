#pragma once



#define USE_DRIVER
#define WSTR_BUFFER_SIZE 1024

#ifdef _DEBUG
#define WRAP_IF_DEBUG(x) { x };
#else
#define WRAP_IF_DEBUG(x)
#endif
#define ERROR_MESSAGE(x) MessageBoxA(NULL, x, NULL, NULL)

#include "../HyperV/HyperV.h"
#include "../Memory/stdafx.h"
class CMemory
{

private:

	DWORD GetProcessID();

public:

	uintptr_t BaseAddress;
	uintptr_t unity;
	uintptr_t mono;
	uintptr_t gom;



	HWND Window;
	DWORD GamePID;
	HyperV* _HyperV = new HyperV();

	template <class type>
	type read(uintptr_t address)
	{
		return _HyperV->ReadValue64<type>(address);
	}

	template<typename type>
	inline bool write(uintptr_t address, type value)
	{
		return _HyperV->WriteValue64<type>(address, value);
	}

	template<typename type>
	inline type ReadChain(uintptr_t base, std::vector<uintptr_t> chain)
	{
		return _HyperV->ReadChain<type>(base, chain);
	}

	bool read(uintptr_t address, void* buffer, size_t size)
	{
		return _HyperV->ReadMem((PVOID)address, buffer, size);
	}

	std::wstring read_wstr(uintptr_t address)
	{
		wchar_t buffer[WSTR_BUFFER_SIZE * sizeof(wchar_t)];
		read(address, &buffer, WSTR_BUFFER_SIZE * sizeof(wchar_t));
		auto str = std::wstring(buffer);
		if (str.size() > 64)
			return L"None";
		return str;
	}

	template <class type>
	std::vector<type> read_vec(uintptr_t address, int size)
	{
		if (!size || size == 0)
			return std::vector<type>{};
		std::vector<type> temp{};
		temp.resize(sizeof(type) * size);
		if (read(address, &temp[0], sizeof(type) * size))
			return temp;
		return temp;
	}


	bool Initialize();

}; inline CMemory memory;




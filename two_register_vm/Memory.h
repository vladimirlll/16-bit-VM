#pragma once
#include <limits>
#include "Exceptions.h"
#include "Types.h"

class Memory final
{
public:
	Memory()
	{
		constexpr const address_t SIZE = std::numeric_limits<address_t>::max();
		mem = new byte_t[SIZE];
	}
	Memory(const Memory&) = delete;
	Memory(const Memory&&) = delete;
	Memory& operator=(const Memory&) = delete;
	Memory& operator=(const Memory&&) = delete;

	//Константный метод не нужен, так память некуда не передаем
	byte_t& operator[](const address_t& addr) noexcept;

	~Memory()
	{
		delete[] mem;
	}
private:
	byte_t* mem = { nullptr };
};


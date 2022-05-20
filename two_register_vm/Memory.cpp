#include "Memory.h"

byte_t& Memory::operator[](const address_t& addr) noexcept
{
	return mem[addr];
}

#include "Load.h"
#include "Processor.h"

void Load::operator()(Processor& proc)
{
	byte_t bb = proc.GetCurrentCmd().cmd24.bb;
	byte_t b1 = bb & 0x2, b2 = bb & 0x1;
	address_t address = GetAddress(proc);
	DWORD d;
	d.bytes[0] = proc.memory[address]; d.bytes[1] = proc.memory[address + 1];
	d.bytes[2] = proc.memory[address + 2]; d.bytes[3] = proc.memory[address + 3];
	address_t num = (address_t(d.bytes[0]) << 8) | d.bytes[1];
	//Нестандартное использование bb, bb используется в качестве выбора регистра, 
	//в который загружаются данные из памяти
	if (b2)
	{
		//Если bb == 01, то загружаем в первый регистр
		proc.regs[0] = num;
	}
	if (b1)
	{
		//Если bb == 10, то загружаем во второй регистр
		proc.regs[1] = num;
	}
}

#include "Save.h"
#include "Processor.h"

void Save::operator()(Processor& proc)
{
	byte_t bb = proc.GetCurrentCmd().cmd24.bb;
	byte_t b1 = bb & 0x2, b2 = bb & 0x1;
	address_t address = GetAddress(proc);
	DWORD d;
	//Нестандартное использование bb, bb используется в качестве выбора регистра, 
	//в который загружаются данные из памяти
	if (b2)
	{
		//Если bb == 01, то загружаем в первый регистр
		d.inum = proc.regs[0];
		proc.memory[address] = d.bytes[0]; proc.memory[address + 1] = d.bytes[1];
		proc.memory[address + 2] = d.bytes[2]; proc.memory[address + 3] = d.bytes[3];
	}
	if (b1)
	{
		//Если bb == 10, то загружаем во второй регистр
		d.inum = proc.regs[1];
		proc.memory[address] = d.bytes[0]; proc.memory[address + 1] = d.bytes[1];
		proc.memory[address + 2] = d.bytes[2]; proc.memory[address + 3] = d.bytes[3];
	}
}

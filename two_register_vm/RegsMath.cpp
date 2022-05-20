#include "RegsMath.h"
#include "Processor.h"

void RegsMath::operator()(Processor& proc)
{
	byte_t bb = proc.GetCurrentCmd().cmd24.bb;
	byte_t b1 = bb & 0x2, b2 = bb & 0x1;
	address_t op = GetAddress(proc);
	//Нестандартное использование bb, bb используется в качестве выбора регистра, 
	//c которым будем работать
	if (b2)
	{
		//Если bb == 01, то работаем с первым регистром
		proc.regs[0] = exec(proc.regs[0], op);
	}
	if (b1)
	{
		//Если bb == 10, то работаем со вторым регистром
		proc.regs[1] = exec(proc.regs[1], op);
	}
}

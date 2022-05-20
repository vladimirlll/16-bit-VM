#include "RCMP.h"
#include "Processor.h"

void RCMP::operator()(Processor& proc)
{
	//Получение первого и второго операнда команды из памяти
	DWORD fOp, sOp;
	address_t currAddress = proc.GetPSW().IP + 1;
	address_t os1, os2; GetOs1Os2(proc, os1, os2);
	address_t address1 = proc.regs[0] + os1;	//Адрес первого операнда
	address_t address2 = proc.regs[1] + os2;	//Адрес второго операнда
	//Получение операндов из памяти
	fOp.bytes[0] = proc.memory[address1]; fOp.bytes[1] = proc.memory[address1 + 1];
	fOp.bytes[2] = proc.memory[address1 + 2]; fOp.bytes[3] = proc.memory[address1 + 3];

	sOp.bytes[0] = proc.memory[address2]; sOp.bytes[1] = proc.memory[address2 + 1];
	sOp.bytes[2] = proc.memory[address2 + 2]; sOp.bytes[3] = proc.memory[address2 + 3];

	double fOpDBL = fOp.rnum, sOpDBL = sOp.rnum;

	//Вычисление результата
	double resDBL = fOpDBL - sOpDBL;

	//Установка флагов
	set_flags(proc, resDBL);
}
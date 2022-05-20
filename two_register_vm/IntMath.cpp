#include "IntMath.h"
#include "Processor.h"

void IntMath::operator()(Processor& proc)
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

	int64_t fOp64 = fOp.inum, sOp64 = sOp.inum;

	//Вычисление результата
	int64_t res64 = exec(fOp64, sOp64);
	DWORD dwRes; dwRes.inum = res64;
	//Запись результата в память
	proc.memory[address1] = dwRes.bytes[0]; proc.memory[address1 + 1] = dwRes.bytes[1];
	proc.memory[address1 + 2] = dwRes.bytes[2]; proc.memory[address1 + 3] = dwRes.bytes[3];

	//Установка флагов
	set_flags(proc, res64);
}

void IntMath::set_flags(Processor& proc, int64_t num)
{
	proc.GetPSW().set_NF(num);
	proc.GetPSW().set_OF(num);
	proc.GetPSW().set_ZF(num);
}

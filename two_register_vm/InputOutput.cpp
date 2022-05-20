#include "InputOutput.h"
#include "Processor.h"

void Input::operator()(Processor& proc)
{
	byte_t bb = proc.GetCurrentCmd().cmd24.bb;
	byte_t b1 = bb & 0b10, b2 = bb & 0b01;
	//Адрес на ячейку, куда вводим число
	address_t address = GetAddress(proc);
	//Нестандартное использование bb, bb используется в качестве выбора типа вводимого числа
	if (b2)
	{
		//Если bb == 01, то записываем int32
		DWORD d;
		std::cout << "Введите целое число: ";
		std::cin >> d.inum;
		//Запись введенного числа в память
		proc.memory[address] = d.bytes[0];	proc.memory[address + 1] = d.bytes[1];
		proc.memory[address + 2] = d.bytes[2];	proc.memory[address + 3] = d.bytes[3];
	}
	if (b1)
	{
		//Если bb == 10, то записываем real32
		DWORD d;
		std::cout << "Введите дробное число: ";
		std::cin >> d.rnum;
		//Запись введенного числа в память
		proc.memory[address] = d.bytes[0];	proc.memory[address + 1] = d.bytes[1];
		proc.memory[address + 2] = d.bytes[2];	proc.memory[address + 3] = d.bytes[3];
	}
}



void Output::operator()(Processor& proc)
{
	byte_t bb = proc.GetCurrentCmd().cmd24.bb;
	byte_t b1 = bb & 0b10, b2 = bb & 0b01;
	//Адрес на ячейку, откуда берем значение на вывод
	address_t address = GetAddress(proc);
	//Нестандартное использование bb, bb используется в качестве выбора типа выводимого числа
	if (b2)
	{
		//Если bb == 01, то выводим int32
		DWORD d;
		d.bytes[0] = proc.memory[address]; d.bytes[1] = proc.memory[address + 1];
		d.bytes[2] = proc.memory[address + 2]; d.bytes[3] = proc.memory[address + 3];
		std::cout << "целое число: " << d.inum << std::endl;
	}
	if (b1)
	{
		//Если bb == 10, то выводим real32
		DWORD d;
		d.bytes[0] = proc.memory[address]; d.bytes[1] = proc.memory[address + 1];
		d.bytes[2] = proc.memory[address + 2]; d.bytes[3] = proc.memory[address + 3];
		std::cout << "дробное число: " << d.rnum << std::endl;
	}
}
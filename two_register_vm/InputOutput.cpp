#include "InputOutput.h"
#include "Processor.h"

void Input::operator()(Processor& proc)
{
	byte_t bb = proc.GetCurrentCmd().cmd24.bb;
	byte_t b1 = bb & 0b10, b2 = bb & 0b01;
	//����� �� ������, ���� ������ �����
	address_t address = GetAddress(proc);
	//������������� ������������� bb, bb ������������ � �������� ������ ���� ��������� �����
	if (b2)
	{
		//���� bb == 01, �� ���������� int32
		DWORD d;
		std::cout << "������� ����� �����: ";
		std::cin >> d.inum;
		//������ ���������� ����� � ������
		proc.memory[address] = d.bytes[0];	proc.memory[address + 1] = d.bytes[1];
		proc.memory[address + 2] = d.bytes[2];	proc.memory[address + 3] = d.bytes[3];
	}
	if (b1)
	{
		//���� bb == 10, �� ���������� real32
		DWORD d;
		std::cout << "������� ������� �����: ";
		std::cin >> d.rnum;
		//������ ���������� ����� � ������
		proc.memory[address] = d.bytes[0];	proc.memory[address + 1] = d.bytes[1];
		proc.memory[address + 2] = d.bytes[2];	proc.memory[address + 3] = d.bytes[3];
	}
}



void Output::operator()(Processor& proc)
{
	byte_t bb = proc.GetCurrentCmd().cmd24.bb;
	byte_t b1 = bb & 0b10, b2 = bb & 0b01;
	//����� �� ������, ������ ����� �������� �� �����
	address_t address = GetAddress(proc);
	//������������� ������������� bb, bb ������������ � �������� ������ ���� ���������� �����
	if (b2)
	{
		//���� bb == 01, �� ������� int32
		DWORD d;
		d.bytes[0] = proc.memory[address]; d.bytes[1] = proc.memory[address + 1];
		d.bytes[2] = proc.memory[address + 2]; d.bytes[3] = proc.memory[address + 3];
		std::cout << "����� �����: " << d.inum << std::endl;
	}
	if (b1)
	{
		//���� bb == 10, �� ������� real32
		DWORD d;
		d.bytes[0] = proc.memory[address]; d.bytes[1] = proc.memory[address + 1];
		d.bytes[2] = proc.memory[address + 2]; d.bytes[3] = proc.memory[address + 3];
		std::cout << "������� �����: " << d.rnum << std::endl;
	}
}
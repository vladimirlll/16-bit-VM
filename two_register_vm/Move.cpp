#include "Move.h"
#include "Processor.h"

void Move::operator()(Processor& proc)
{
	byte_t bb = proc.GetCurrentCmd().cmd32.bb;
	byte_t b1 = bb & 0x2, b2 = bb & 0x1;
	//������������� ������������� bb, bb ������������ � �������� ������ ����� ��� ���������� ��������� 
	if (b1 && b2)
	{
		//���� bb == 11, �� �����������: ������-������, � ���������� � ������ ������
		//1-�� ������� - �������� 1, 2-�� ������� - �������� 2
		address_t os1, os2;
		GetOs1Os2(proc, os1, os2);
		address_t address1 = proc.regs[0] + os1;	//����� ������� ��������
		address_t address2 = proc.regs[1] + os2;	//����� ������� ��������
		proc.memory[address1] = proc.memory[address2]; proc.memory[address1 + 1] = proc.memory[address2 + 1];
		proc.memory[address1 + 2] = proc.memory[address2 + 2]; proc.memory[address1 + 3] = proc.memory[address2 + 2];
	}
	else
	{
		//����� - ������ ������� ��������
		throw invalid_command_format("����� �������� ������ �������");
	}
}

#include "RegsMath.h"
#include "Processor.h"

void RegsMath::operator()(Processor& proc)
{
	byte_t bb = proc.GetCurrentCmd().cmd24.bb;
	byte_t b1 = bb & 0x2, b2 = bb & 0x1;
	address_t op = GetAddress(proc);
	//������������� ������������� bb, bb ������������ � �������� ������ ��������, 
	//c ������� ����� ��������
	if (b2)
	{
		//���� bb == 01, �� �������� � ������ ���������
		proc.regs[0] = exec(proc.regs[0], op);
	}
	if (b1)
	{
		//���� bb == 10, �� �������� �� ������ ���������
		proc.regs[1] = exec(proc.regs[1], op);
	}
}

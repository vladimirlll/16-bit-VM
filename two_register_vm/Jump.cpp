#include "Jump.h"
#include "Processor.h"

void Jump::go_to(Processor& proc) noexcept
{
    byte_t bb = proc.GetCurrentCmd().cmd24.bb;
    byte_t b1 = bb & 0b10, b2 = bb & 0b01;
    char os = GetAddress(proc);
    if (!b1 && !b2)
    {
        //���� bb = 00, �� IP = IP + �������� (�� �����, ��� �� 127-128 ����)
        proc.SetIP(proc.GetPSW().IP + os);
    }
    else if (!b1 && b2)
    {
        //���� bb = 01, �� IP = a1 + ��������
        proc.SetIP(proc.regs[0] + os);
    }
    else if (b1 && !b2)
    {
        //���� bb = 10, �� IP = a2 + ��������
        proc.SetIP(proc.regs[1] + os);
    }
    else
    {
        //����� - ������ ������� ��������
        throw invalid_command_format("����� �������� ������ �������");
    }
}

void Jump::operator()(Processor& proc) noexcept
{
	if (execute(proc)) go_to(proc);
}

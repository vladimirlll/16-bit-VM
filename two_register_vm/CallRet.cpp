#include "CallRet.h"
#include "Processor.h"

void Call::operator()(Processor& proc) noexcept
{
    address_t newIp, returnIp; GetOs1Os2(proc, newIp, returnIp);
    newIp -= 4; //��� ��� ���������� ���������� IP �� 4 ����� ���������� ������� Call � Processor::run()
    proc.regs[1] = returnIp;
    proc.SetIP(newIp);
}

void Return::operator()(Processor& proc) noexcept
{
    address_t returnIp = proc.regs[1];
    proc.SetIP(returnIp);
}
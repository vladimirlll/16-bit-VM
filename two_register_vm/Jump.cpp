#include "Jump.h"
#include "Processor.h"

void Jump::go_to(Processor& proc) noexcept
{
    byte_t bb = proc.GetCurrentCmd().cmd24.bb;
    byte_t b1 = bb & 0b10, b2 = bb & 0b01;
    char os = GetAddress(proc);
    if (!b1 && !b2)
    {
        //Если bb = 00, то IP = IP + смещение (не далее, как на 127-128 слов)
        proc.SetIP(proc.GetPSW().IP + os);
    }
    else if (!b1 && b2)
    {
        //Если bb = 01, то IP = a1 + смещение
        proc.SetIP(proc.regs[0] + os);
    }
    else if (b1 && !b2)
    {
        //Если bb = 10, то IP = a2 + смещение
        proc.SetIP(proc.regs[1] + os);
    }
    else
    {
        //Иначе - формат команды неверный
        throw invalid_command_format("Задан неверный формат команды");
    }
}

void Jump::operator()(Processor& proc) noexcept
{
	if (execute(proc)) go_to(proc);
}

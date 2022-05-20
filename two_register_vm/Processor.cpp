#include "Processor.h"
#include "Move.h"
#include "IntMath.h"
#include "RealMath.h"
#include "ICMP.h"
#include "RCMP.h"
#include "Load.h"
#include "Save.h"
#include "Jump.h"
#include "CallRet.h"
#include "InputOutput.h"
#include "RegsMath.h"

void Processor::SetIP(address_t IP) noexcept 
{
	psw.IP = IP;
}

Processor::PSW Processor::GetPSW() const noexcept
{
	return psw;
}

void Processor::PSW::set_ZF(double num)
{
	ZF = (fabs(num) < std::numeric_limits<double>::epsilon());
}

void Processor::PSW::set_NF(double num)
{
	NF = (num < 0);
}

void Processor::PSW::set_ZF(int64_t num)
{
	ZF = (num == 0);
}

void Processor::PSW::set_NF(int64_t num)
{
	NF = (num < 0);
}

void Processor::PSW::set_OF(int64_t num)
{
	OF = (num < std::numeric_limits<int32_t>::min() || num > std::numeric_limits<int32_t>::max());
}

void Processor::PSW::set_OF(double num)
{
	//Используется std::numeric_limits<float>::lowest(), чтобы получить минимальное отрицательное значение
	OF = (num < std::numeric_limits<float>::lowest() || num > std::numeric_limits<float>::max());
}

void Processor::PSW::reset_flags()
{
	NF = ZF = OF = 0;
}

void Processor::reset() noexcept
{
	psw.reset_flags();
	psw.IP = startIp;
}

Processor::Processor()
{
	commands[stop] = nullptr; 
	commands[move] = new class Move();
	commands[iAdd] = new class IntMath([](int a, int b) { return (a + b); }); 
	commands[iSub] = new class IntMath([](int a, int b) { return (a - b); }); 
	commands[iMul] = new class IntMath([](int a, int b) { return (a * b); }); 
	commands[iDiv] = new class IntMath([](int a, int b) { return (a / b); }); 
	commands[iMod] = new class IntMath([](int a, int b) { return (a % b); }); 
	commands[iInc] = new class IntMath([](int a, int b) { return (a + 1); });
	commands[iDec] = new class IntMath([](int a, int b) { return (a - 1); }); 
	commands[iAnd] = new class IntMath([](int a, int b) { return (a & b); }); 
	commands[iOr] = new class IntMath([](int a, int b) { return (a | b); });  
	commands[iNot] = new class IntMath([](int a, int b) { return (~a); });    
	commands[iXor] = new class IntMath([](int a, int b) {return (a ^ b); });  

	commands[rAdd] = new class RealMath([](float a, float b) { return (a + b); }); 
	commands[rSub] = new class RealMath([](float a, float b) { return (a - b); }); 
	commands[rMul] = new class RealMath([](float a, float b) { return (a * b); }); 
	commands[rDiv] = new class RealMath([](float a, float b) { return (a / b); }); 

	commands[rgAdd] = new class RegsMath([](address_t a, address_t b) {return (a + b); }); 
	commands[rgSub] = new class RegsMath([](address_t a, address_t b) {return (a - b); }); 

	commands[call] = new class Call(); 
	commands[ret] = new class Return(); 

	commands[icmp] = new class ICMP([](int a, int b) { return (a - b); });
	commands[rcmp] = new class RCMP([](float a, float b) { return (a - b); });

	commands[save] = new class Save();
	commands[load] = new class Load(); 

	commands[input] = new class Input(); 
	commands[output] = new class Output(); 

	commands[jmp] = new class Jump([](Processor& p) { return true; }); 
	commands[je] = new class Jump([](Processor& p) {return (p.GetPSW().ZF == 1); }); 
	commands[jne] = new class Jump([](Processor& p) {return (p.GetPSW().ZF == 0); }); 
	commands[jg] = new class Jump([](Processor& p) {return ((p.GetPSW().ZF == 0) && (p.GetPSW().NF == p.GetPSW().OF)); }); 
	commands[jge] = new class Jump([](Processor& p) {return (p.GetPSW().NF == p.GetPSW().OF); });
	commands[jl] = new class Jump([](Processor& p) {return (p.GetPSW().NF != p.GetPSW().OF); });
	commands[jle] = new class Jump([](Processor& p) {return (p.GetPSW().ZF == 1 || p.GetPSW().NF != p.GetPSW().OF); });
}

cmd_t Processor::GetCurrentCmd() const noexcept
{
	return cmd;
}

void Processor::load_next_cmd()
{
	byte_t code_bb = memory[psw.IP];
	cmd.cmd32.code = code_bb >> 2, cmd.cmd32.bb = code_bb & 0x03;
}

void Processor::run()
{
	load_next_cmd();
	while (cmd.cmd32.code != stop)
	{
		commands[cmd.cmd32.code]->operator()(*this);
		if (cmd.cmd32.code < 30) psw.IP += Command32::size;
		else psw.IP += Command24::size;
		load_next_cmd();
	}
}

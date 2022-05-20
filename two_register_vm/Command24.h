#ifndef COMMAND24_H
#define COMMAND24_H
#include "Command.h"
#include "Types.h"

class Command24 : public Command
{
public:
	static const byte_t size = 3;
	//ѕолучает адрес (константу) из пам€ти дл€ команды
	static address_t GetAddress(Processor& proc);
};

#endif // !COMMAND24_H


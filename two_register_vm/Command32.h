#ifndef COMMAND32_H
#define COMMAND32_H
#include "Command.h"
#include "Types.h"

class Command32 : public Command
{
public:
	static const byte_t size = 4;
	//Получает os1, os2 из памяти для команды
	static void GetOs1Os2(Processor& proc, address_t& os1, address_t& os2);
};

#endif // !COMMAND32_H


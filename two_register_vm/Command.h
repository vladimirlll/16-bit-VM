#ifndef COMMAND_H
#define COMMAND_H

#include "Exceptions.h"

class Processor;

class Command
{
public:
	virtual void operator()(Processor& processor) = 0;
	virtual ~Command() = default;
};

#endif // !COMMAND_H
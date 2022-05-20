#ifndef CALLRET_H
#define CALLRET_H
#include <functional>
#include "Command32.h"

class Call : public Command32
{
public:
	void operator()(Processor& processor) noexcept;
};

class Return : public Command32
{
public:
	void operator()(Processor& processor) noexcept;
};

#endif // !CALLRET_H


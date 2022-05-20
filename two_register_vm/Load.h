#ifndef LOAD_H
#define LOAD_H
#include "Command24.h"

class Load : public Command24
{
public:
	void operator()(Processor& proc);
};

#endif // !LOAD_H


#ifndef SAVE_H
#define SAVE_H
#include "Command24.h"

class Save : public Command24
{
public:
	void operator()(Processor& proc);
};

#endif // !SAVE_H


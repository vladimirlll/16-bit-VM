#ifndef MOVE_H
#define MOVE_H
#include "Command32.h"

class Move : public Command32
{
public:
	void operator()(Processor& proc);
};

#endif // !MOVE_H


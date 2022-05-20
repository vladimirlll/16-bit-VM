#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H
#include <iostream>
#include "Command24.h"

class Input : public Command24
{
public:
	void operator()(Processor& proc);
};

class Output : public Command24
{
public:
	void operator()(Processor& proc);
};


#endif // !INPUT_OUTPUT_H


#ifndef REGSMATH_H
#define REGSMATH_H
#include <functional>
#include "Command24.h"

class RegsMath : public Command24
{
public:
	RegsMath(std::function<address_t(address_t, address_t)> f) : exec(f) {}
	void operator()(Processor& proc) override;

private:
	//функциональный объект с необходимым арифметическим действием
	std::function<address_t(address_t, address_t)> exec;
};

#endif // !REGSMATH_H


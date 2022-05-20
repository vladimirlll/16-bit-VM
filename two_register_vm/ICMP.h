#ifndef ICMP_H
#define ICMP_H
#include "IntMath.h"

class ICMP : public IntMath
{
public:
	ICMP(std::function<int64_t(int64_t, int64_t)> f) : IntMath(f) {}
	void operator()(Processor& proc);
};

#endif // !ICMP_H



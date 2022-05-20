#ifndef RCMP_H
#define RCMP_H
#include "RealMath.h"

class RCMP : public RealMath
{
public:
	RCMP(std::function<double(double, double)> f) : RealMath(f) {}
	void operator()(Processor& proc);
};

#endif // !RCMP_H

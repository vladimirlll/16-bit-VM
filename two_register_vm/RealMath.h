#ifndef REALMATH_H
#define REALMATH_H
#include <functional>
#include "Command32.h"

class RealMath : public Command32
{
public:
	//В конструктор можно передавать лямбда-выражение, 
	//возвращающее результат того или иного арифметического действия
	RealMath(std::function<double(double, double)> f) : exec(f) {}
	virtual void operator()(Processor& proc);

private:
	//функциональный объект с выбранным арифметическим действием
	std::function<double(double, double)> exec;
protected:
	//Установка флагов
	static void set_flags(Processor& proc, double num);
};

#endif // !REALMATH_H


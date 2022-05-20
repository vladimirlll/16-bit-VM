#ifndef INTMATH_H
#define INTMATH_H
#include <functional>
#include "Command32.h"

class IntMath : public Command32
{
public:
	//В конструктор можно передавать лямбда-выражение, 
	//возвращающее результат того или иного арифметического действия
	IntMath(std::function<int64_t(int64_t, int64_t)> f) : exec(f) {}
	virtual void operator()(Processor& proc);

private:
	//функциональный объект с выбранным арифметическим действием
	std::function<int64_t(int64_t, int64_t)> exec;
protected:
	//Установка флагов
	static void set_flags(Processor& proc, int64_t num);
};

#endif // !INTMATH_H


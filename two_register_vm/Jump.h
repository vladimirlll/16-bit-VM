#ifndef JUMP_H
#define JUMP_H

#include <functional>
#include "Command24.h"

class Jump : public Command24
{
public:
	//В конструктор можно передавать лямбда-выражение. 
	//Если это условный переход, то передается лямба-выражение с проверкой
	//соответствующих флагов. Если безусловный переход, то лямба-выражение, 
	//возвращающее истину
	Jump(std::function<bool(Processor&)> f) : execute(f) {}
	void go_to(Processor& proc) noexcept;
	void operator()(Processor& proc) noexcept;

private:
	//Функциональный объект с выбранным прыжком
	std::function<bool(Processor&)> execute;
};

#endif // !JUMP_H


#ifndef INTMATH_H
#define INTMATH_H
#include <functional>
#include "Command32.h"

class IntMath : public Command32
{
public:
	//� ����������� ����� ���������� ������-���������, 
	//������������ ��������� ���� ��� ����� ��������������� ��������
	IntMath(std::function<int64_t(int64_t, int64_t)> f) : exec(f) {}
	virtual void operator()(Processor& proc);

private:
	//�������������� ������ � ��������� �������������� ���������
	std::function<int64_t(int64_t, int64_t)> exec;
protected:
	//��������� ������
	static void set_flags(Processor& proc, int64_t num);
};

#endif // !INTMATH_H


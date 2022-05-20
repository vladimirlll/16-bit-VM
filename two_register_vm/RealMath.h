#ifndef REALMATH_H
#define REALMATH_H
#include <functional>
#include "Command32.h"

class RealMath : public Command32
{
public:
	//� ����������� ����� ���������� ������-���������, 
	//������������ ��������� ���� ��� ����� ��������������� ��������
	RealMath(std::function<double(double, double)> f) : exec(f) {}
	virtual void operator()(Processor& proc);

private:
	//�������������� ������ � ��������� �������������� ���������
	std::function<double(double, double)> exec;
protected:
	//��������� ������
	static void set_flags(Processor& proc, double num);
};

#endif // !REALMATH_H


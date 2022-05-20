#ifndef JUMP_H
#define JUMP_H

#include <functional>
#include "Command24.h"

class Jump : public Command24
{
public:
	//� ����������� ����� ���������� ������-���������. 
	//���� ��� �������� �������, �� ���������� �����-��������� � ���������
	//��������������� ������. ���� ����������� �������, �� �����-���������, 
	//������������ ������
	Jump(std::function<bool(Processor&)> f) : execute(f) {}
	void go_to(Processor& proc) noexcept;
	void operator()(Processor& proc) noexcept;

private:
	//�������������� ������ � ��������� �������
	std::function<bool(Processor&)> execute;
};

#endif // !JUMP_H


#pragma once
#include <string>
#include <stdexcept>

//������� ����� ����������
class base_exception : public std::exception
{
private:
	std::string text;			//����� ����������

public:
	explicit base_exception(std::string ex_text) : text(ex_text) {}

	const char* what() const noexcept final { return text.c_str(); }
};

//����� ���������� ��� ������������ ���� � ����� � ����� ���������
class invalid_path : public base_exception
{
public:
	explicit invalid_path(const std::string& ex_text) : base_exception(ex_text) {}
};

//����� ���������� ��� ����� ������������� ������� �������
class invalid_command_format : public base_exception
{
public:
	explicit invalid_command_format(const std::string& ex_text) : base_exception(ex_text) {}
};

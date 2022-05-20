#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstring>
#include "Processor.h"

class Loader
{
public:
	//��������� ��� ��������� �� ����� fname
	static void Load(const std::string& fname, Processor& processor);

private:
	//��������� ������ ���� ��������� �� ����� �� delim
	static std::vector<std::string> split(const std::string& str, char delim);
	//������� �� ������ ����� ���� ������� � �����������
	static void RemoveNotCode(std::vector<std::string>& cmd);

	//��������� ��������� ������ ��� ������
	static void ReadAddress(std::istringstream& is, address_t &baseAddress) noexcept;
	//���������� ����� ����� � ������
	static void ReadInt(std::istringstream& is, Processor& proc, address_t& address) noexcept;
	//���������� ������������ ����� � ������
	static void ReadReal(std::istringstream& is, Processor& proc, address_t& address) noexcept;
	//���������� 32-������ ������� � ������
	static void ReadCommand32(const std::vector<std::string> &cmdVec, Processor& proc, address_t& address) noexcept;
	//���������� 24-������ ������� � ������
	static void ReadCommand24(const std::vector<std::string>& cmdVec, Processor& proc, address_t& address) noexcept;
	//���������� ������� �������� � �����
	static void ReadLoadCommand(const std::vector<std::string>& cmdVec, Processor& proc, address_t& address) noexcept;
	//���������� ������� � ������
	static void ReadCommand(std::istringstream& is, Processor& proc, address_t &address) noexcept;
	//��������� ��������� �������, ���������� � ������ ������� stop � ���������� IP
	static void ReadExec(std::istringstream& is, Processor& proc, address_t& address) noexcept;
};


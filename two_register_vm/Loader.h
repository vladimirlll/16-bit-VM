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
	//Загружает код программы из файла fname
	static void Load(const std::string& fname, Processor& processor);

private:
	//Разделяет строку кода программы на части по delim
	static std::vector<std::string> split(const std::string& str, char delim);
	//Удаляет из частей строк кода пробелы и комментарии
	static void RemoveNotCode(std::vector<std::string>& cmd);

	//Считывает начальный адресс для памяти
	static void ReadAddress(std::istringstream& is, address_t &baseAddress) noexcept;
	//Записывает целое число в память
	static void ReadInt(std::istringstream& is, Processor& proc, address_t& address) noexcept;
	//Записывает вещественное число в память
	static void ReadReal(std::istringstream& is, Processor& proc, address_t& address) noexcept;
	//Записывает 32-битную команду в память
	static void ReadCommand32(const std::vector<std::string> &cmdVec, Processor& proc, address_t& address) noexcept;
	//Записывает 24-битную команду в память
	static void ReadCommand24(const std::vector<std::string>& cmdVec, Processor& proc, address_t& address) noexcept;
	//Записывает команду загрузки в паять
	static void ReadLoadCommand(const std::vector<std::string>& cmdVec, Processor& proc, address_t& address) noexcept;
	//Записывает команду в память
	static void ReadCommand(std::istringstream& is, Processor& proc, address_t &address) noexcept;
	//Считывает последнюю команду, записывает в память команду stop и выставляет IP
	static void ReadExec(std::istringstream& is, Processor& proc, address_t& address) noexcept;
};


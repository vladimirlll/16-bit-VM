#pragma once
#include <string>
#include <stdexcept>

//Базовый класс исключений
class base_exception : public std::exception
{
private:
	std::string text;			//текст исключения

public:
	explicit base_exception(std::string ex_text) : text(ex_text) {}

	const char* what() const noexcept final { return text.c_str(); }
};

//Класс исключения при неправильном пути к файлу с кодом программы
class invalid_path : public base_exception
{
public:
	explicit invalid_path(const std::string& ex_text) : base_exception(ex_text) {}
};

//Класс исключения при вводе неправильного формата команды
class invalid_command_format : public base_exception
{
public:
	explicit invalid_command_format(const std::string& ex_text) : base_exception(ex_text) {}
};

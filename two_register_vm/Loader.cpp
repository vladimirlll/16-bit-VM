#include "Loader.h"
using namespace std;

void Loader::Load(const std::string& fname, Processor& processor)
{
    ifstream fin(fname);
    if (!fin)   throw invalid_path("Задан неверный путь к файлу с программой");

    address_t baseAddress = 0;              //Начальный индекс в массиве памяти для записи
    address_t address = 0;                  //Текущий индекс в массиве памяти для записи

    char sym = ' ';
    while (sym != 'e')
    {
        string str;
        getline(fin, str);
        istringstream is(str);
        is >> sym;

        switch (sym)
        {
        case 'a':
            ReadAddress(is, address);
            baseAddress = address;
            break;
        case 'i':
            ReadInt(is, processor, address);
            break;
        case 'r':
            ReadReal(is, processor, address);
            break;
        case 'c':
            ReadCommand(is, processor, address);
            break;
        case 'e':
            ReadExec(is, processor, address);
            break;
        default:
            break;
        }
    }
}

void Loader::ReadAddress(std::istringstream& is, address_t &baseAddress) noexcept
{
    is >> baseAddress;
}

void Loader::ReadInt(std::istringstream& strm, Processor& proc, address_t& address) noexcept
{
    dword word;
    strm >> word.int32;
    byte_t* bytes = (byte_t*)&word.int32;
    for (size_t i = 0; i < 4; i++)
    {
        proc.memory[address] = bytes[i];
        ++address;
    }
}

void Loader::ReadReal(std::istringstream& strm, Processor& proc, address_t& address) noexcept
{
    dword word;
    strm >> word.real32;
    byte_t* bytes = (byte_t*)&word.real32;
    for (size_t i = 0; i < 4; i++)
    {
        proc.memory[address] = bytes[i];
        ++address;
    }
}

void Loader::ReadCommand32(const vector<string>& cmdVec, Processor& proc, address_t& address) noexcept
{
    cmd_t command;                                                  //Считываемая команда
    command.cmd32.code = byte_t(std::stoi(cmdVec[0]));
    command.cmd32.bb = byte_t(std::stoi(cmdVec[1], nullptr, 2));
    command.cmd32.os1 = address_t(std::stoi(cmdVec[2]));
    command.cmd32.os2 = address_t(std::stoi(cmdVec[3]));
    data_t data;
    data.cmd = command;
    byte_t* bytes = (byte_t*)&data;
    for (size_t i = 0; i < 5; i++)
    {
        proc.memory[address++] = bytes[i];
    }
}

void Loader::ReadCommand24(const vector<string> &cmdVec, Processor& proc, address_t& address) noexcept
{
    //cmd_t command;                                                  //Считываемая команда
    //command.cmd24.code = byte_t(std::stoi(cmdVec[0]));
    //command.cmd24.bb = byte_t(std::stoi(cmdVec[1], nullptr, 2));
    //command.cmd24.os = address_t(std::stoi(cmdVec[2]));
    //data_t data;
    //data.cmd = command;
    //byte_t* bytes = (byte_t*)&data;
    //for (size_t i = 0; i < 3; i++)
    //{
    //    proc.memory[address++] = bytes[i];
    //}
    //address = address_t(std::stoi(cmdVec[2]));
}

void Loader::ReadLoadCommand(const std::vector<std::string>& cmdVec, Processor& proc, address_t& address) noexcept
{
    cmd_t command;
    command.cmd24.code = byte_t(std::stoi(cmdVec[0]));
    command.cmd24.bb = byte_t(std::stoi(cmdVec[1], nullptr, 2));
    command.cmd24.address = address_t(std::stoi(cmdVec[2]));
    data_t data;
    data.cmd = command;
    byte_t* bytes = (byte_t*)&data;
    for (size_t i = 0; i < 3; i++)
    {
        proc.memory[address++] = bytes[i];
    }
}

void Loader::ReadCommand(std::istringstream& strm, Processor& proc, address_t &address) noexcept
{
    std::vector<std::string> cmdVec = split(strm.str(), ' ');       //Команда, разделенная на части по пробелу
    cmdVec.erase(cmdVec.begin());
    RemoveNotCode(cmdVec);
    //byte commandCode = byte(std::stoi(cmdVec[1]));

    string commandCode = cmdVec[1];

    if (commandCode == "01" || commandCode == "10")
    {
        ReadCommand24(cmdVec, proc, address);
    }
    else if (commandCode == "11")
    {
        ReadCommand32(cmdVec, proc, address);
    }
    else
    {
        ReadLoadCommand(cmdVec, proc, address);
    }

    /*if (commandCode == 1)
    {
        ReadCommand24(cmdVec, proc, address);
    }
    else
    {
        ReadCommand32(cmdVec, proc, address);
    }*/
}

void Loader::ReadExec(std::istringstream& is, Processor& proc, address_t& address) noexcept
{
    data_t data;
    //data.cmd.cmd24.code = 0;
    byte_t* bytes = (byte_t*)&data;
    for (size_t i = 0; i < 3; i++)
    {
        proc.memory[address++] = bytes[i];
    }
    address_t IP;
    is >> IP;
    proc.SetIP(IP);
}

std::vector<std::string> Loader::split(const std::string& str, char delim)
{
    vector<string> els;
    stringstream  ss(str);
    string el;
    while (getline(ss, el, delim))  els.push_back(el);
    return els;
}

void Loader::RemoveNotCode(std::vector<std::string>& cmd)
{
    bool commsChecked = false;
    int i = 0;
    while (i < cmd.size() && !commsChecked)
    {
        if (cmd[i] == ";")
        {
            cmd.erase(cmd.begin() + i, cmd.end());
            commsChecked = true;
        }
        ++i;
    }

    i = 0;
    while (i < cmd.size())
    {
        if (cmd[i] == "") cmd.erase(cmd.begin() + i);
        else ++i;
    }
}

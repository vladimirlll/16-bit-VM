#include <iostream>
#include "Loader.h"

using namespace std;

std::vector<std::string> split(const std::string& str, char delim)
{
    vector<string> els;
    stringstream  ss(str);
    string el;
    while (getline(ss, el, delim))  els.push_back(el);
    return els;
}

void RemoveNotCode(std::vector<std::string>& cmd)
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

void ReadInt(std::istringstream& strm, Processor& proc, address_t& address) noexcept
{
    int32_t num;  strm >> num;
    DWORD d; d.inum = num;
    proc.memory[address++] = d.bytes[0];
    proc.memory[address++] = d.bytes[1];
    proc.memory[address++] = d.bytes[2];
    proc.memory[address++] = d.bytes[3];
}

void ReadReal(std::istringstream& strm, Processor& proc, address_t& address) noexcept
{
    float num;  strm >> num;
    DWORD d; d.rnum = num;
    proc.memory[address++] = d.bytes[0];
    proc.memory[address++] = d.bytes[1];
    proc.memory[address++] = d.bytes[2];
    proc.memory[address++] = d.bytes[3];
}

void ReadCommand32(vector<string>& cmdVec, Processor& proc, address_t& address) noexcept
{
    cmd_t command;                                          //����������� �������
    command.cmd32.code = byte_t(std::stoi(cmdVec[0]));
    command.cmd32.bb = byte_t(std::stoi(cmdVec[1], nullptr, 2));
    command.cmd32.os1 = command.cmd32.os2 = 0;
    byte_t b1 = command.cmd32.bb & 0b10, b2 = command.cmd32.bb & 0b01;
    if (b1)
    {
        command.cmd32.os1 = address_t(std::stoi(cmdVec[2]));
        cmdVec.erase(cmdVec.begin() + 2);
    }
    if (b2)
    {
        command.cmd32.os2 = address_t(std::stoi(cmdVec[2]));
        cmdVec.erase(cmdVec.begin() + 2);
    }
    byte_t code_bb_tomem = command.cmd32.code;			    //������ ���� ��� ������ (code + bb)
    code_bb_tomem <<= 2; code_bb_tomem |= command.cmd32.bb;
    proc.memory[address++] = code_bb_tomem;
    byte_t fOppart = ((command.cmd32.os1 & 0xFFF0) >> 4);	//������ ���� ��� ������ (������ 8 ��� ������� ��������)
    proc.memory[address++] = fOppart;
    byte_t fOpSopParts = ((command.cmd32.os1 & 0x000F) << 4) 
        | ((command.cmd32.os2 & 0x0F00) >> 8);	            //������ ���� (��������� 4 ���� ������� �������� + 
                                                            //������ 4 ���� ������� ��������)
    proc.memory[address++] = fOpSopParts;
    byte_t sOpPart = command.cmd32.os2 & 0x00FF;			//��������� ���� ��� ������ (��������� 8 ��� ������� ��������)
    proc.memory[address++] = sOpPart;
}

void ReadCommand24(const vector<string>& cmdVec, Processor& proc, address_t& address) noexcept
{
    cmd_t command;                                                  //����������� �������
    command.cmd24.code = byte_t(std::stoi(cmdVec[0]));
    command.cmd24.bb = byte_t(std::stoi(cmdVec[1], nullptr, 2));
    command.cmd24.address = address_t(std::stoi(cmdVec[2]));
    byte_t code_bb_tomem = command.cmd24.code;			            //������ ���� ��� ������ (code + bb)
    code_bb_tomem <<= 2; code_bb_tomem |= command.cmd24.bb;
    proc.memory[address++] = code_bb_tomem;
    byte_t fOpPart = ((command.cmd24.address & 0xFF00) >> 8);	    //������ ���� ��� ������ (������ 8 ��� ������)
    proc.memory[address++] = fOpPart;
    byte_t fOpPart2 = command.cmd24.address;	                    //������ ���� ��� ������ (��������� 8 ��� ������)
    proc.memory[address++] = fOpPart2;
}

void ReadCommand(std::istringstream& strm, Processor& proc, address_t& address) noexcept
{
    std::vector<std::string> cmdVec = split(strm.str(), ' ');       //�������, ����������� �� ����� �� �������
    cmdVec.erase(cmdVec.begin());
    RemoveNotCode(cmdVec);
    byte_t commandCode = byte_t(std::stoi(cmdVec[0]));
    if (commandCode < 30) ReadCommand32(cmdVec, proc, address);
    else ReadCommand24(cmdVec, proc, address);
}

void ReadExec(std::istringstream& is, Processor& proc, address_t& address) noexcept
{
    //������ ������� stop � ������
    proc.memory[address++] = 0;
    proc.memory[address++] = 0;
    proc.memory[address++] = 0;
    proc.memory[address++] = 0;
    address_t IP;
    //��������� � ��������� IP
    is >> IP;
    proc.SetIP(IP);
}

void Load(const std::string& fname, Processor& processor)
{
    ifstream fin(fname);
    if (!fin)   throw invalid_path("����� �������� ���� � ����� � ����������");

    address_t baseAddress = 0;              //��������� ������ � ������� ������ ��� ������
    address_t address = 0;                  //������� ������ � ������� ������ ��� ������

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
            is >> address;
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

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "ru");
	Processor processor;

    if (argc > 1)
    {
        try
        {
            Load(argv[1], processor);
        }
        catch (const invalid_path& ex)
        {
            cout << ex.what() << endl;
            return 1;
        }
        try
        {
            processor.run();
        }
        catch (const base_exception& ex)
        {
            cout << ex.what() << endl;
            return 1;
        }
    }

	return 0;
}

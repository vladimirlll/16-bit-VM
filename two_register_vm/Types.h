#ifndef TYPES_H
#define TYPES_H

#include <cinttypes>

using byte_t = uint8_t;
using address_t = uint16_t;

#pragma pack(push, 1)
struct cmd32
{
    byte_t code : 6;              //Код операции
    byte_t bb : 2;                //Формат команды
    address_t os1 : 12;           //Смещение 1
    address_t os2 : 12;           //Смещение 2
};
#pragma pack(pop)

#pragma pack(push, 1)
struct cmd24
{
    byte_t code : 6;              //Код операции
    byte_t bb : 2;                //Формат команды
    address_t address;            //Адрес (константа)
};
#pragma pack(pop)

union cmd_t
{
    cmd32 cmd32;
    cmd24 cmd24;
};

union DWORD
{
    int32_t inum;
    float rnum;
    byte_t bytes[4];
};


#endif // !TYPES_H
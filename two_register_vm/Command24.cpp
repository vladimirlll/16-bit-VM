#include "Command24.h"
#include "Processor.h"

address_t Command24::GetAddress(Processor& proc)
{
    address_t currAddress = proc.GetPSW().IP + 1;
    address_t address = (address_t(proc.memory[currAddress]) << 8) | proc.memory[currAddress + 1];
    return address;
}

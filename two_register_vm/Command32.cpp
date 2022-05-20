#include "Command32.h"
#include "Processor.h"

void Command32::GetOs1Os2(Processor& proc, address_t& os1, address_t& os2)
{
	address_t currAddress = proc.GetPSW().IP + 1;
	byte_t fOppart_read = proc.memory[currAddress], fOpSopParts_read = proc.memory[currAddress + 1],
		sOpPart_read = proc.memory[currAddress + 2];
	os1 = (address_t(fOppart_read) << 4) | ((fOpSopParts_read & 0xF0) >> 4);
	os2 = (((address_t)fOpSopParts_read & 0x000F) << 8) | sOpPart_read;
}

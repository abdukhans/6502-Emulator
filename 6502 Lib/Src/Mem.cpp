#include "Mem.h"

void Mem::Init() {
	for (size_t i = 0; i < MAX_MEM; i++)
	{
		Data[i] = 0;
	}

}

Byte& Mem::operator[](u32 addr) const
{
	return Data[addr];
}

Byte& Mem::operator[](u32 addr)
{
	return Data[addr];

}

void Mem::WriteWord(Word val, Byte Addr, u32& Cycles)
{
		Data[Addr] = val;
		Data[Addr + 1] = val >> 8;
		Cycles -= 2;
}

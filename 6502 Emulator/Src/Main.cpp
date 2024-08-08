#include "6502.h"

int main() {

	Mem mem;
	CPU cpu;

	cpu.Reset(mem);

	
	unsigned char d;
	unsigned short a =  256 ;



	Byte L[3] = {0};

	L[0] = cpu.PC;
	L[1] = cpu.PC >> 8 ;



	d = a;

	mem[0xFFFC] = CPU::INS_JSR_ABS;
	mem[0xFFFD] = 0x42;
	mem[0xFFFE] = 0x43;
	mem[0x4342] = CPU::INS_LDA_IM;
	mem[0x4343] = 0x84;




	int val = (int)mem[(char)120];
	LOG(val)
	std::cout << 0xFFFF << std::endl;

	cpu.Execute(9, mem);
	return 0;
}
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

using Byte = unsigned char;   // 8 bits 
using Word = unsigned short;  // 16 bits


#define LOG(X)\
std::cout<< X <<std::endl;


using u32 = unsigned int;
struct Mem {

	// MAX_MEM = 2^16, 
	static u32  constexpr MAX_MEM = 1 << 16;

	Byte Data[MAX_MEM];

	void Init() {


		for (size_t i = 0; i < MAX_MEM; i++)
		{
			Data[i] = 0;
		}

	}


	//Byte operator[] (u32 addr) const {
	//	//std::cout << "USED" << std::endl;
	//	return Data[addr];
	//}

	Byte& operator[] (u32 addr) {


		//std::cout << "USED2" << std::endl;
		return Data[addr];
	}

	void WriteWord(Word val, Byte Addr, u32& Cycles) {

		Data[Addr] = val;
		Data[Addr + 1] = val >> 8;
		Cycles -= 2;

	}

};



struct CPU
{
	Byte SP;     // Stack pointer
	Word PC;     // Program Counter

	Byte A, X, Y; // Registers


	// The fields below are all status 
	// registers
	Byte C : 1;
	Byte Z : 1;
	Byte I : 1;
	Byte D : 1;
	Byte B : 1;
	Byte O : 1;
	Byte V : 1;
	Byte N : 1;


	void StackPushByte(Mem& mem, Byte val, u32& Cycles) {
		const unsigned int pageNumber = 1 << 8;
		mem[pageNumber + SP] = val;
		SP++;

		Cycles--;
	}


	void StackPushWord(Mem& mem, Word val, u32& Cycles) {
		const unsigned int pageNumber = 1 << 8;

		Byte lower8 = val;
		Byte upper8 = val >> 8;
		mem[pageNumber + SP] = lower8;
		SP++;
		mem[pageNumber + SP] = upper8;
		SP++;
		Cycles -= 2;
	}
	void Reset(Mem& mem) {

		PC = 0xFFFC;
		SP = 0x0100;

		C = Z = I = D = B = V = N = 0;

		A = X = Y = 0;


		mem.Init();

	}


	Byte ReadByte(u32& Cycles,
		Mem& mem,
		const Byte addr,
		const Byte page) {

		const unsigned int page_addr = page << 8;

		Byte data = mem[page_addr + addr];

		Cycles--;

		return data;
	}

	Byte FetchByte(u32& Cycles, Mem& mem) {

		Byte data = mem[PC];

		PC++;

		Cycles--;

		return data;
	}

	Word FetchWord(u32& Cycles, Mem& mem) {



		Byte lower8 = mem[PC];
		PC++;
		Byte higher8 = mem[PC];

		PC++;



		Cycles -= 2;


		Word val = (higher8 << 8) + lower8;

		return val;
	}

	void WriteWord(u32& Cycles, Word addr, Word val, Mem& mem) {

		mem[addr] = val;
		mem[addr + 1] = val >> 8;

		Cycles -= 2;


	}

	Word PopWord(u32& Cycles, Mem& mem) {


		Cycles -= 2;


		Word ret = mem[SP] << 8 + mem[SP - 1];
		SP -= 2;

		return  ret;

	}


	static constexpr Byte INS_LDA_IM = 0xAB;
	static constexpr Byte INS_LDA_ZP = 0xA5;
	static constexpr Byte INS_LDA_ZPX = 0xB5;
	static constexpr Byte INS_JSR_ABS = 0x20;


	void LDAsetStatus() {
		Z = (A == 0);
		N = (A & (1 << 7)) == 0;
	}

	void Execute(u32 NumCycles, Mem& mem) {

		while (NumCycles > 0)
		{

			Byte Ins = FetchByte(NumCycles, mem);

			switch (Ins) {


			case INS_LDA_IM:
			{
				Byte val = FetchByte(NumCycles, mem);


				A = val;

				LDAsetStatus();




			} break;

			case INS_LDA_ZP:
			{

				Byte ZeroPageAddr = FetchByte(NumCycles, mem);
				A = ReadByte(NumCycles, mem, ZeroPageAddr, 0);

				LDAsetStatus();

			} break;

			case INS_LDA_ZPX:
			{

				Byte ZeroPageAddr = FetchByte(NumCycles, mem);
				ZeroPageAddr += X;
				NumCycles--;
				A = ReadByte(NumCycles, mem, ZeroPageAddr, 0);
				LDAsetStatus();

			}case INS_JSR_ABS: {



				Word targetAddr = FetchWord(NumCycles, mem);
				StackPushWord(mem, PC - 1, NumCycles);


				PC = targetAddr;

				NumCycles -= 1;







			}

			default: {
				std::cout << "Instruction not implemented" << std::endl;
			}break;

			}


		}


	}

};

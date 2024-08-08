#pragma once
using Byte = unsigned char;   // 8 bits 
using Word = unsigned short;  // 16 bits
using u32 = unsigned int;

static u32  constexpr MAX_MEM = 1 << 16;
Byte Data[MAX_MEM];

struct Mem {

	void Init();
	Byte& operator[] (u32 addr) const;


	

	Byte& operator[] (u32 addr);
	void WriteWord(Word val, Byte Addr, u32& Cycles);

};

#define LOG(X)\
std::cout<< X <<std::endl;

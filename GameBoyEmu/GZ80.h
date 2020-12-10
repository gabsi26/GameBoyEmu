#pragma once
#include <cstdint>
#include "memory.h"

namespace GZ80
{
#ifndef BYTE_WORD
#define BYTE_WORD
	using Byte = uint8_t;
	using Word = uint16_t;
#endif
	struct Cycles
	{
		Word mc; // machine cycles
		Word cc; // clock cycles

		void increment_cycles(int machine_cycles);

		void reset();
	};
		
	struct Regs
	{
		union
		{
			struct
			{
				union
				{
					struct
					{
						Byte unused : 4;
						Byte carry : 1;
						Byte half_carry : 1;
						Byte negative : 1;
						Byte zero : 1;
					};
					Byte F : 8;
				};
				Byte A : 8;
			};
			Word AF;
		};

		union
		{
			struct
			{
				Byte C : 8;
				Byte B : 8;
			};
			Word BC;
		};

		union
		{
			struct
			{
				Byte E : 8;
				Byte D : 8;
			};
			Word DE;
		};

		union
		{
			struct
			{
				Byte L : 8;
				Byte H : 8;
			};
			Word HL;
		};

		Word sp, pc;

		void reset();
	};
	
	class CPU
	{
	public:
		Cycles* cycles;
		Regs* regs;
		Memory* mem;

		void load_8_bit_value(Word& reg, Byte value);
		static constexpr Byte
			// 8 bit loads
			INS_LD_Bn = 0x06,
			INS_LD_Cn = 0x0E,
			INS_LD_Dn = 0x16,
			INS_LD_En = 0x1E,
			INS_LD_Hn = 0x26,
			INS_LD_Ln = 0x2E,

			INS_LD_AA = 0x7F;

	public:
		CPU();
		Byte fetch_byte();
		void execute(Byte opcode, Word clock_cycles);


		~CPU() {};
	};
	
};
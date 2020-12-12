#pragma once
#include <cstdint>
#include "memory.h"

namespace GZ80
{
#ifndef BYTE_WORD
#define BYTE_WORD
	using Bit = bool;
	using Byte = uint8_t;
	using SByte = int8_t;
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
		Bit bit_add(Bit first, Bit second, bool& carry);
		Byte four_bit_add(Byte first, Byte second, bool& carry);
		Byte byte_add(Byte first, Byte second, bool& carry, bool& half_carry);
		Word word_add_lower_flags(Word first, Byte second, bool& carry, bool& half_carry);
		Word word_add_higher_flags(Word first, Byte second, bool& carry, bool& half_carry);
		void load_8_bit_value(Word& reg, Byte value);
		static constexpr Byte
			// ###### 8 bit loads ######
			// immediate
			INS_LD_Bn = 0x06,
			INS_LD_Cn = 0x0E,
			INS_LD_Dn = 0x16,
			INS_LD_En = 0x1E,
			INS_LD_Hn = 0x26,
			INS_LD_Ln = 0x2E,
			INS_LD_HLn = 0x36,
			INS_LD_An = 0x3E,
			// store in A
			INS_LD_AA = 0x7F,
			INS_LD_AB = 0x78,
			INS_LD_AC = 0x79,
			INS_LD_AD = 0x7A,
			INS_LD_AE = 0x7B,
			INS_LD_AH = 0x7C,
			INS_LD_AL = 0x7D,
			INS_LD_AHL = 0x7E,
			INS_LD_ABC = 0x0A,
			INS_LD_ADE = 0x1A,
			INS_LD_Ann = 0xFA,
			INS_LD_A_C_ = 0xF2,
			// load from A
			INS_LD_BA = 0x47,
			INS_LD_CA = 0x4F,
			INS_LD_DA = 0x57,
			INS_LD_EA = 0x5F,
			INS_LD_HA = 0x67,
			INS_LD_LA = 0x6F,
			INS_LD_BCA = 0x02,
			INS_LD_DEA = 0x12,
			INS_LD_HLA = 0x77,
			INS_LD_nnA = 0xEA,
			INS_LD_C_A = 0xE2,
			// store in B
			INS_LD_BB = 0x40,
			INS_LD_BC = 0x41,
			INS_LD_BD = 0x42,
			INS_LD_BE = 0x43,
			INS_LD_BH = 0x44,
			INS_LD_BL = 0x45,
			INS_LD_BHL = 0x46,
			// store in C
			INS_LD_CB = 0x48,
			INS_LD_CC = 0x49,
			INS_LD_CD = 0x4A,
			INS_LD_CE = 0x4B,
			INS_LD_CH = 0x4C,
			INS_LD_CL = 0x4D,
			INS_LD_CHL = 0x4E,
			// store in D
			INS_LD_DB = 0x50,
			INS_LD_DC = 0x51,
			INS_LD_DD = 0x52,
			INS_LD_DE = 0x53,
			INS_LD_DH = 0x54,
			INS_LD_DL = 0x55,
			INS_LD_DHL = 0x56,
			// store in E
			INS_LD_EB = 0x58,
			INS_LD_EC = 0x59,
			INS_LD_ED = 0x5A,
			INS_LD_EE = 0x5B,
			INS_LD_EH = 0x5C,
			INS_LD_EL = 0x5D,
			INS_LD_EHL = 0x5E,
			// store in H
			INS_LD_HB = 0x60,
			INS_LD_HC = 0x61,
			INS_LD_HD = 0x62,
			INS_LD_HE = 0x63,
			INS_LD_HH = 0x64,
			INS_LD_HL = 0x65,
			INS_LD_HHL = 0x66,
			// store in L
			INS_LD_LB = 0x68,
			INS_LD_LC = 0x69,
			INS_LD_LD = 0x6A,
			INS_LD_LE = 0x6B,
			INS_LD_LH = 0x6C,
			INS_LD_LL = 0x6D,
			INS_LD_LHL = 0x6E,
			// store at Address HL
			INS_LD_HLB = 0x70,
			INS_LD_HLC = 0x71,
			INS_LD_HLD = 0x72,
			INS_LD_HLE = 0x73,
			INS_LD_HLH = 0x74,
			INS_LD_HLL = 0x75,
			// store and decrement/increment
			INS_LDD_A_HL_ = 0x3A,
			INS_LDD_HL_A = 0x32,
			INS_LDI_A_HL_ = 0x2A,
			INS_LDI_HL_A = 0x22,
			// store and load at 0xFF00 + n
			INS_LDH_nA = 0xE0,
			INS_LDH_An = 0xF0,
			// ###### 16 bit loads ######
			// immediate
			INS_LD_BCnn = 0x01,
			INS_LD_DEnn = 0x11,
			INS_LD_HLnn = 0x21,
			INS_LD_SPnn = 0x31,
			// stack load and store operations
			INS_LD_SPHL = 0xF9,
			INS_LDHL_SPn = 0xF8;
	public:
		CPU();
		Byte fetch_byte(bool increment_cycles = true);
		Word fetch_word();
		void execute(Byte opcode, Word clock_cycles);


		~CPU() {};
	};
	
};
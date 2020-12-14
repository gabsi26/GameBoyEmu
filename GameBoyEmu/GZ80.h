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
	using SWord = int16_t;
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
		void set_carries(Word reg, Word value, Word result, bool lo_carry = true);
		void set_carries(Byte reg, Byte value, Byte result);
		void set_carries_borrow(Byte reg, Byte value, Byte result);
		void add_to_accumulator(Byte value);
		void addc_to_accumulator(Byte value);
		void subtract_from_accumulator(Byte value);
		void subtractc_from_accumulator(Byte value);
		void and_with_accumulator(Byte value);
		void or_with_accumulator(Byte value);
		void xor_with_accumulator(Byte value);
		void compare_with_accumulator(Byte value);
		Byte increment(Byte value);
		Word increment(Word value);
		Byte decrement(Byte value);
		Word decrement(Word value);
		void add(Word value);
		void push_register_onto_stack(Word reg);
		void pop_value_from_stack(Word& reg);
		void load_8_bit_value(Word& reg, Byte value);
		Byte rotate_left(Byte value, bool through_carry = false);
		Byte rotate_right(Byte value, bool through_carry = false);
		Byte shift_left(Byte value);
		Byte shift_right(Byte value, bool logical = false);
		void test_bit(Byte value, Byte bit);
		Byte set_bit_mask(Byte bit);
		Byte reset_bit_mask(Byte bit);
		void cb_handler();
		static constexpr Byte
			CB_INS = 0xCB,
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
			INS_LDHL_SPn = 0xF8,
			INS_LD_nnSP = 0x08,
			INS_PUSH_AF = 0xF5,
			INS_PUSH_BC = 0xC5,
			INS_PUSH_DE = 0xD5,
			INS_PUSH_HL = 0xE5,
			INS_POP_AF = 0xF1,
			INS_POP_BC = 0xC1,
			INS_POP_DE = 0xD1,
			INS_POP_HL = 0xE1,
			// ###### 8 bit ALU #######
			// ADD
			INS_ADD_AA = 0x87,
			INS_ADD_AB = 0x80,
			INS_ADD_AC = 0x81,
			INS_ADD_AD = 0x82,
			INS_ADD_AE = 0x83,
			INS_ADD_AH = 0x84,
			INS_ADD_AL = 0x85,
			INS_ADD_AHL = 0x86,
			INS_ADD_AIM = 0xC6,
			// ADDC
			INS_ADC_AA = 0x8F,
			INS_ADC_AB = 0x88,
			INS_ADC_AC = 0x89,
			INS_ADC_AD = 0x8A,
			INS_ADC_AE = 0x8B,
			INS_ADC_AH = 0x8C,
			INS_ADC_AL = 0x8D,
			INS_ADC_AHL = 0x8E,
			INS_ADC_AIM = 0xCE,
			// SUB
			INS_SUB_AA = 0x97,
			INS_SUB_AB = 0x90,
			INS_SUB_AC = 0x91,
			INS_SUB_AD = 0x92,
			INS_SUB_AE = 0x93,
			INS_SUB_AH = 0x94,
			INS_SUB_AL = 0x95,
			INS_SUB_AHL = 0x96,
			INS_SUB_AIM = 0xD6,
			// SBC
			INS_SBC_AA = 0x9F,
			INS_SBC_AB = 0x98,
			INS_SBC_AC = 0x99,
			INS_SBC_AD = 0x9A,
			INS_SBC_AE = 0x9B,
			INS_SBC_AH = 0x9C,
			INS_SBC_AL = 0x9D,
			INS_SBC_AHL = 0x9E,
			INS_SBC_AIM = 0xDE,
			// AND
			INS_AND_AA = 0xA7,
			INS_AND_AB = 0xA0,
			INS_AND_AC = 0xA1,
			INS_AND_AD = 0xA2,
			INS_AND_AE = 0xA3,
			INS_AND_AH = 0xA4,
			INS_AND_AL = 0xA5,
			INS_AND_AHL = 0xA6,
			INS_AND_AIM = 0xE6,
			// OR
			INS_OR_AA = 0xB7,
			INS_OR_AB = 0xB0,
			INS_OR_AC = 0xB1,
			INS_OR_AD = 0xB2,
			INS_OR_AE = 0xB3,
			INS_OR_AH = 0xB4,
			INS_OR_AL = 0xB5,
			INS_OR_AHL = 0xB6,
			INS_OR_AIM = 0xF6,
			// XOR
			INS_XOR_AA = 0xAF,
			INS_XOR_AB = 0xA8,
			INS_XOR_AC = 0xA9,
			INS_XOR_AD = 0xAA,
			INS_XOR_AE = 0xAB,
			INS_XOR_AH = 0xAC,
			INS_XOR_AL = 0xAD,
			INS_XOR_AHL = 0xAE,
			INS_XOR_AIM = 0xEE,
			// CP
			INS_CP_AA = 0xBF,
			INS_CP_AB = 0xB8,
			INS_CP_AC = 0xB9,
			INS_CP_AD = 0xBA,
			INS_CP_AE = 0xBB,
			INS_CP_AH = 0xBC,
			INS_CP_AL = 0xBD,
			INS_CP_AHL = 0xBE,
			INS_CP_AIM = 0xFE,
			// INC
			INS_INC_A = 0x3C,
			INS_INC_B = 0x04,
			INS_INC_C = 0x0C,
			INS_INC_D = 0x14,
			INS_INC_E = 0x1C,
			INS_INC_H = 0x24,
			INS_INC_L = 0x2C,
			INS_INC_HL_ = 0x34,
			// DEC
			INS_DEC_A = 0x3D,
			INS_DEC_B = 0x05,
			INS_DEC_C = 0x0D,
			INS_DEC_D = 0x15,
			INS_DEC_E = 0x1D,
			INS_DEC_H = 0x25,
			INS_DEC_L = 0x2D,
			INS_DEC_HL_ = 0x35,
			// ###### 16 bit ALU #######
			// ADD_HL
			INS_ADD_HLBC = 0x09,
			INS_ADD_HLDE = 0x19,
			INS_ADD_HLHL = 0x29,
			INS_ADD_HLSP = 0x39,
			// ADD_SPIM
			INS_ADD_SPIM = 0xE8,
			// INC
			INS_INC_BC = 0x03,
			INS_INC_DE = 0x13,
			INS_INC_HL = 0x23,
			INS_INC_SP = 0x33,
			// INC
			INS_DEC_BC = 0x0B,
			INS_DEC_DE = 0x1B,
			INS_DEC_HL = 0x2B,
			INS_DEC_SP = 0x3B,
			// ###### Rotates and Shifts #########
			INS_RLCA = 0x07,
			INS_RLA = 0x17,
			INS_RRCA = 0x0F,
			INS_RRA = 0x1F,
			// RLC
			INS_RLC_A = 0x07,
			INS_RLC_B = 0x00,
			INS_RLC_C = 0x01,
			INS_RLC_D = 0x02,
			INS_RLC_E = 0x03,
			INS_RLC_H = 0x04,
			INS_RLC_L = 0x05,
			INS_RLC_HL_ = 0x06,
			// RL
			INS_RL_A = 0x17,
			INS_RL_B = 0x10,
			INS_RL_C = 0x11,
			INS_RL_D = 0x12,
			INS_RL_E = 0x13,
			INS_RL_H = 0x14,
			INS_RL_L = 0x15,
			INS_RL_HL_ = 0x16,
			// RRC
			INS_RRC_A = 0x0F,
			INS_RRC_B = 0x08,
			INS_RRC_C = 0x09,
			INS_RRC_D = 0x0A,
			INS_RRC_E = 0x0B,
			INS_RRC_H = 0x0C,
			INS_RRC_L = 0x0D,
			INS_RRC_HL_ = 0x0E,
			// RR
			INS_RR_A = 0x1F,
			INS_RR_B = 0x18,
			INS_RR_C = 0x19,
			INS_RR_D = 0x1A,
			INS_RR_E = 0x1B,
			INS_RR_H = 0x1C,
			INS_RR_L = 0x1D,
			INS_RR_HL_ = 0x1E,
			// SLA
			INS_SLA_A = 0x27,
			INS_SLA_B = 0x20,
			INS_SLA_C = 0x21,
			INS_SLA_D = 0x22,
			INS_SLA_E = 0x23,
			INS_SLA_H = 0x24,
			INS_SLA_L = 0x25,
			INS_SLA_HL_ = 0x26,
			// SRA
			INS_SRA_A = 0x2F,
			INS_SRA_B = 0x28,
			INS_SRA_C = 0x29,
			INS_SRA_D = 0x2A,
			INS_SRA_E = 0x2B,
			INS_SRA_H = 0x2C,
			INS_SRA_L = 0x2D,
			INS_SRA_HL_ = 0x2E,
			// SRL
			INS_SRL_A = 0x3F,
			INS_SRL_B = 0x38,
			INS_SRL_C = 0x39,
			INS_SRL_D = 0x3A,
			INS_SRL_E = 0x3B,
			INS_SRL_H = 0x3C,
			INS_SRL_L = 0x3D,
			INS_SRL_HL_ = 0x3E,
			// BIT 0
			INS_BIT_0A = 0x47,
			INS_BIT_0B = 0x40,
			INS_BIT_0C = 0x41,
			INS_BIT_0D = 0x42,
			INS_BIT_0E = 0x43,
			INS_BIT_0H = 0x44,
			INS_BIT_0L = 0x45,
			INS_BIT_0_HL_ = 0x46,
			// BIT 1
			INS_BIT_1A = 0x4F,
			INS_BIT_1B = 0x48,
			INS_BIT_1C = 0x49,
			INS_BIT_1D = 0x4A,
			INS_BIT_1E = 0x4B,
			INS_BIT_1H = 0x4C,
			INS_BIT_1L = 0x4D,
			INS_BIT_1_HL_ = 0x4E,
			// BIT 2
			INS_BIT_2A = 0x57,
			INS_BIT_2B = 0x50,
			INS_BIT_2C = 0x51,
			INS_BIT_2D = 0x52,
			INS_BIT_2E = 0x53,
			INS_BIT_2H = 0x54,
			INS_BIT_2L = 0x55,
			INS_BIT_2_HL_ = 0x56,
			// BIT 3
			INS_BIT_3A = 0x5F,
			INS_BIT_3B = 0x58,
			INS_BIT_3C = 0x59,
			INS_BIT_3D = 0x5A,
			INS_BIT_3E = 0x5B,
			INS_BIT_3H = 0x5C,
			INS_BIT_3L = 0x5D,
			INS_BIT_3_HL_ = 0x5E,
			// BIT 4
			INS_BIT_4A = 0x67,
			INS_BIT_4B = 0x60,
			INS_BIT_4C = 0x61,
			INS_BIT_4D = 0x62,
			INS_BIT_4E = 0x63,
			INS_BIT_4H = 0x64,
			INS_BIT_4L = 0x65,
			INS_BIT_4_HL_ = 0x66,
			// BIT 5
			INS_BIT_5A = 0x6F,
			INS_BIT_5B = 0x68,
			INS_BIT_5C = 0x69,
			INS_BIT_5D = 0x6A,
			INS_BIT_5E = 0x6B,
			INS_BIT_5H = 0x6C,
			INS_BIT_5L = 0x6D,
			INS_BIT_5_HL_ = 0x6E,
			// BIT 6
			INS_BIT_6A = 0x77,
			INS_BIT_6B = 0x70,
			INS_BIT_6C = 0x71,
			INS_BIT_6D = 0x72,
			INS_BIT_6E = 0x73,
			INS_BIT_6H = 0x74,
			INS_BIT_6L = 0x75,
			INS_BIT_6_HL_ = 0x76,
			// BIT 7
			INS_BIT_7A = 0x7F,
			INS_BIT_7B = 0x78,
			INS_BIT_7C = 0x79,
			INS_BIT_7D = 0x7A,
			INS_BIT_7E = 0x7B,
			INS_BIT_7H = 0x7C,
			INS_BIT_7L = 0x7D,
			INS_BIT_7_HL_ = 0x7E,
			// RES 0
			INS_RES_0A = 0x87,
			INS_RES_0B = 0x80,
			INS_RES_0C = 0x81,
			INS_RES_0D = 0x82,
			INS_RES_0E = 0x83,
			INS_RES_0H = 0x84,
			INS_RES_0L = 0x85,
			INS_RES_0_HL_ = 0x86,
			// RES 1
			INS_RES_1A = 0x8F,
			INS_RES_1B = 0x88,
			INS_RES_1C = 0x89,
			INS_RES_1D = 0x8A,
			INS_RES_1E = 0x8B,
			INS_RES_1H = 0x8C,
			INS_RES_1L = 0x8D,
			INS_RES_1_HL_ = 0x8E,
			// RES 2
			INS_RES_2A = 0x97,
			INS_RES_2B = 0x90,
			INS_RES_2C = 0x91,
			INS_RES_2D = 0x92,
			INS_RES_2E = 0x93,
			INS_RES_2H = 0x94,
			INS_RES_2L = 0x95,
			INS_RES_2_HL_ = 0x96,
			// RES 3
			INS_RES_3A = 0x9F,
			INS_RES_3B = 0x98,
			INS_RES_3C = 0x99,
			INS_RES_3D = 0x9A,
			INS_RES_3E = 0x9B,
			INS_RES_3H = 0x9C,
			INS_RES_3L = 0x9D,
			INS_RES_3_HL_ = 0x9E,
			// RES 4
			INS_RES_4A = 0xA7,
			INS_RES_4B = 0xA0,
			INS_RES_4C = 0xA1,
			INS_RES_4D = 0xA2,
			INS_RES_4E = 0xA3,
			INS_RES_4H = 0xA4,
			INS_RES_4L = 0xA5,
			INS_RES_4_HL_ = 0xA6,
			// RES 5
			INS_RES_5A = 0xAF,
			INS_RES_5B = 0xA8,
			INS_RES_5C = 0xA9,
			INS_RES_5D = 0xAA,
			INS_RES_5E = 0xAB,
			INS_RES_5H = 0xAC,
			INS_RES_5L = 0xAD,
			INS_RES_5_HL_ = 0xAE,
			// RES 6
			INS_RES_6A = 0xB7,
			INS_RES_6B = 0xB0,
			INS_RES_6C = 0xB1,
			INS_RES_6D = 0xB2,
			INS_RES_6E = 0xB3,
			INS_RES_6H = 0xB4,
			INS_RES_6L = 0xB5,
			INS_RES_6_HL_ = 0xB6,
			// RES 7
			INS_RES_7A = 0xBF,
			INS_RES_7B = 0xB8,
			INS_RES_7C = 0xB9,
			INS_RES_7D = 0xBA,
			INS_RES_7E = 0xBB,
			INS_RES_7H = 0xBC,
			INS_RES_7L = 0xBD,
			INS_RES_7_HL_ = 0xBE,
			// SET 0
			INS_SET_0A = 0xC7,
			INS_SET_0B = 0xC0,
			INS_SET_0C = 0xC1,
			INS_SET_0D = 0xC2,
			INS_SET_0E = 0xC3,
			INS_SET_0H = 0xC4,
			INS_SET_0L = 0xC5,
			INS_SET_0_HL_ = 0xC6,
			// SET 1
			INS_SET_1A = 0xCF,
			INS_SET_1B = 0xC8,
			INS_SET_1C = 0xC9,
			INS_SET_1D = 0xCA,
			INS_SET_1E = 0xCB,
			INS_SET_1H = 0xCC,
			INS_SET_1L = 0xCD,
			INS_SET_1_HL_ = 0xCE,
			// SET 2
			INS_SET_2A = 0xD7,
			INS_SET_2B = 0xD0,
			INS_SET_2C = 0xD1,
			INS_SET_2D = 0xD2,
			INS_SET_2E = 0xD3,
			INS_SET_2H = 0xD4,
			INS_SET_2L = 0xD5,
			INS_SET_2_HL_ = 0xD6,
			// SET 3
			INS_SET_3A = 0xDF,
			INS_SET_3B = 0xD8,
			INS_SET_3C = 0xD9,
			INS_SET_3D = 0xDA,
			INS_SET_3E = 0xDB,
			INS_SET_3H = 0xDC,
			INS_SET_3L = 0xDD,
			INS_SET_3_HL_ = 0xDE,
			// SET 4
			INS_SET_4A = 0xE7,
			INS_SET_4B = 0xE0,
			INS_SET_4C = 0xE1,
			INS_SET_4D = 0xE2,
			INS_SET_4E = 0xE3,
			INS_SET_4H = 0xE4,
			INS_SET_4L = 0xE5,
			INS_SET_4_HL_ = 0xE6,
			// SET 5
			INS_SET_5A = 0xEF,
			INS_SET_5B = 0xE8,
			INS_SET_5C = 0xE9,
			INS_SET_5D = 0xEA,
			INS_SET_5E = 0xEB,
			INS_SET_5H = 0xEC,
			INS_SET_5L = 0xED,
			INS_SET_5_HL_ = 0xEE,
			// SET 6
			INS_SET_6A = 0xF7,
			INS_SET_6B = 0xF0,
			INS_SET_6C = 0xF1,
			INS_SET_6D = 0xF2,
			INS_SET_6E = 0xF3,
			INS_SET_6H = 0xF4,
			INS_SET_6L = 0xF5,
			INS_SET_6_HL_ = 0xF6,
			// SET 7
			INS_SET_7A = 0xFF,
			INS_SET_7B = 0xF8,
			INS_SET_7C = 0xF9,
			INS_SET_7D = 0xFA,
			INS_SET_7E = 0xFB,
			INS_SET_7H = 0xFC,
			INS_SET_7L = 0xFD,
			INS_SET_7_HL_ = 0xFE;

	public:
		CPU();
		Byte fetch_byte(bool increment_cycles = true);
		Word fetch_word();
		void execute(Byte opcode, Word clock_cycles);


		~CPU() {};
	};
	
};
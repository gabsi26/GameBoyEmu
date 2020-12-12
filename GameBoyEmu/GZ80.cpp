#include <stdio.h>
#include "GZ80.h"

void GZ80::Cycles::increment_cycles(int machine_cycles)
{
	mc += machine_cycles;
	cc += machine_cycles * 4;
}

void GZ80::Cycles::reset()
{
	mc = 0;
	cc = 0;
}

void GZ80::Regs::reset()
{
	AF = BC = DE = HL = 0;
	sp = 0xFFFE;
	pc = 0x100;
}

GZ80::CPU::CPU()
{
	cycles = new Cycles();
	regs = new Regs();
	mem = new Memory();
	cycles->reset();
	regs->reset();
}

GZ80::Byte GZ80::CPU::fetch_byte(bool increment_cycles)
{
	if (increment_cycles)
		cycles->increment_cycles(1);
	return mem->read_from_address(regs->pc++);
}

GZ80::Word GZ80::CPU::fetch_word()
{
	Byte lsB = fetch_byte();
	Byte msB = fetch_byte();
	return ((Word)msB << 8) | (Word)lsB;
}
GZ80::Bit GZ80::CPU::bit_add(Bit first, Bit second, bool& carry)
{
	Bit result = first ^ second ^ carry;
	carry = (first && second) || (first && carry) || (second && carry);
	return result;
}

GZ80::Byte GZ80::CPU::four_bit_add(Byte first, Byte second, bool& carry)
{
	Byte result = bit_add(first & 0b1, second & 0b1, carry);
	for (int i = 1; i < 4; i++)
	{
		result += (bit_add(first & (0b1 << i), second & (0b1 << i), carry) << i);
	}
	return result;
}

GZ80::Byte GZ80::CPU::byte_add(Byte first, Byte second, bool& carry, bool& half_carry)
{
	Byte result = four_bit_add(first & 0xF, second & 0xF, half_carry);
	carry = half_carry;
	result += (four_bit_add((first & 0xF0) >> 4, (second & 0xF0) >> 4, carry) << 4);
	return result;
}

GZ80::Word GZ80::CPU::word_add_lower_flags(Word first, Byte second, bool& carry, bool& half_carry)
{
	bool carries[] = { false, false };
	Word result = byte_add(first & 0xFF, second, carry, half_carry);
	carries[0] = half_carry;
	carries[1] = carry;
	result += (byte_add((first & 0xFF00) >> 8, 0, carry, half_carry) << 8);
	carry = carries[1];
	half_carry = carries[0];
	return result;
}

GZ80::Word GZ80::CPU::word_add_higher_flags(Word first, Byte second, bool& carry, bool& half_carry)
{
	Byte result = four_bit_add(first & 0xF, second & 0xF, half_carry);
	carry = half_carry;
	result += (bit_add(first & 0xF0, second & 0xF0, carry) << 0x4);
	return result;
}

void GZ80::CPU::execute(Byte opcode, Word machine_cycles)
{
	while (cycles->mc < machine_cycles)
	{
		switch (opcode)
		{
			// ######### 8 bit loads ###########
			// immediate
			case INS_LD_Bn:
			{
				Byte value = fetch_byte();
				regs->B = value;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_Cn:
			{
				Byte value = fetch_byte();
				regs->C = value;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_Dn:
			{
				Byte value = fetch_byte();
				regs->D = value;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_En:
			{
				Byte value = fetch_byte();
				regs->E = value;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_Hn:
			{
				Byte value = fetch_byte();
				regs->H = value;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_Ln:
			{
				Byte value = fetch_byte();
				regs->L = value;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_HLn:
			{
				Byte value = fetch_byte();
				mem->write_to_address(regs->HL, value);
				cycles->increment_cycles(2);
			} break;
			case INS_LD_An:
			{
				Byte value = fetch_byte();
				regs->A = value;
				cycles->increment_cycles(1);
			} break;

			// store into A
			case INS_LD_AA:
			{
				regs->A = regs->A;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_AB:
			{
				regs->A = regs->B;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_AC:
			{
				regs->A = regs->C;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_AD:
			{
				regs->A = regs->D;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_AE:
			{
				regs->A = regs->E;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_AH:
			{
				regs->A = regs->H;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_AL:
			{
				regs->A = regs->L;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_AHL:
			{
				regs->A = mem->read_from_address(regs->HL);
				cycles->increment_cycles(2);
			} break;
			case INS_LD_ABC:
			{
				regs->A = mem->read_from_address(regs->BC);
				cycles->increment_cycles(2);
			} break;
			case INS_LD_ADE:
			{
				regs->A = mem->read_from_address(regs->DE);
				cycles->increment_cycles(2);
			} break;

			case INS_LD_Ann:
			{
				Word address = fetch_word();
				regs->A = mem->read_from_address(address);
				cycles->increment_cycles(2);
			} break;

			case INS_LD_A_C_:
			{
				regs->A = mem->read_from_address(0xFF00 + regs->C);
				cycles->increment_cycles(2);
			} break;

			//load from A
			case INS_LD_BA:
			{
				regs->B = regs->A;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_CA:
			{
				regs->C = regs->A;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_DA:
			{
				regs->D = regs->A;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_EA:
			{
				regs->E = regs->A;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_HA:
			{
				regs->H = regs->A;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_LA:
			{
				regs->L = regs->A;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_BCA:
			{
				mem->write_to_address(regs->BC, regs->A);
				cycles->increment_cycles(2);
			} break;
			case INS_LD_DEA:
			{
				mem->write_to_address(regs->DE, regs->A);
				cycles->increment_cycles(2);
			} break;
			case INS_LD_HLA:
			{
				mem->write_to_address(regs->HL, regs->A);
				cycles->increment_cycles(2);
			} break;
			case INS_LD_nnA:
			{
				Word address = fetch_word();
				mem->write_to_address(address, regs->A);
				cycles->increment_cycles(2);
			} break;
			case INS_LD_C_A:
			{
				mem->write_to_address(0xFF00 + regs->C, regs->A);
				cycles->increment_cycles(2);
			} break;

			// store into B
			case INS_LD_BB:
			{
				regs->B = regs->B;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_BC:
			{
				regs->B = regs->C;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_BD:
			{
				regs->B = regs->D;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_BE:
			{
				regs->B = regs->E;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_BH:
			{
				regs->B = regs->H;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_BL:
			{
				regs->B = regs->L;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_BHL:
			{
				regs->B = mem->read_from_address(regs->HL);
				cycles->increment_cycles(2);
			} break;

			// store into C
			case INS_LD_CB:
			{
				regs->C = regs->B;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_CC:
			{
				regs->C = regs->C;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_CD:
			{
				regs->C = regs->D;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_CE:
			{
				regs->C = regs->E;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_CH:
			{
				regs->C = regs->H;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_CL:
			{
				regs->C = regs->L;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_CHL:
			{
				regs->C = mem->read_from_address(regs->HL);
				cycles->increment_cycles(2);
			} break;

			// store into D
			case INS_LD_DB:
			{
				regs->D = regs->B;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_DC:
			{
				regs->D = regs->C;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_DD:
			{
				regs->D = regs->D;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_DE:
			{
				regs->D = regs->E;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_DH:
			{
				regs->D = regs->H;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_DL:
			{
				regs->D = regs->L;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_DHL:
			{
				regs->D = mem->read_from_address(regs->HL);
				cycles->increment_cycles(2);
			} break;

			// store into E
			case INS_LD_EB:
			{
				regs->E = regs->B;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_EC:
			{
				regs->E = regs->C;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_ED:
			{
				regs->E = regs->D;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_EE:
			{
				regs->E = regs->E;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_EH:
			{
				regs->E = regs->H;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_EL:
			{
				regs->E = regs->L;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_EHL:
			{
				regs->E = mem->read_from_address(regs->HL);
				cycles->increment_cycles(2);
			} break;

			// store into H
			case INS_LD_HB:
			{
				regs->H = regs->B;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_HC:
			{
				regs->H = regs->C;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_HD:
			{
				regs->H = regs->D;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_HE:
			{
				regs->H = regs->E;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_HH:
			{
				regs->H = regs->H;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_HL:
			{
				regs->H = regs->L;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_HHL:
			{
				regs->H = mem->read_from_address(regs->HL);
				cycles->increment_cycles(2);
			} break;

			// store into L
			case INS_LD_LB:
			{
				regs->L = regs->B;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_LC:
			{
				regs->L = regs->C;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_LD:
			{
				regs->L = regs->D;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_LE:
			{
				regs->L = regs->E;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_LH:
			{
				regs->L = regs->H;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_LL:
			{
				regs->L = regs->L;
				cycles->increment_cycles(1);
			} break;
			case INS_LD_LHL:
			{
				regs->L = mem->read_from_address(regs->HL);
				cycles->increment_cycles(2);
			} break;
			case INS_LD_HLB:
			{
				mem->write_to_address(regs->HL, regs->B);
				cycles->increment_cycles(2);
			} break;

			// store into address _HL_
			case INS_LD_HLC:
			{
				mem->write_to_address(regs->HL, regs->BC);
				cycles->increment_cycles(2);
			} break;
			case INS_LD_HLD:
			{
				mem->write_to_address(regs->HL, regs->D);
				cycles->increment_cycles(2);
			} break;
			case INS_LD_HLE:
			{
				mem->write_to_address(regs->HL, regs->E);
				cycles->increment_cycles(2);
			} break;
			case INS_LD_HLH:
			{
				mem->write_to_address(regs->HL, regs->H);
				cycles->increment_cycles(2);
			} break;
			case INS_LD_HLL:
			{
				mem->write_to_address(regs->HL, regs->L);
				cycles->increment_cycles(2);
			} break;
			
			// store and decrement/increment 
			case INS_LDD_A_HL_:
			{
				regs->A = mem->read_from_address(regs->HL--);
				cycles->increment_cycles(2);
			} break;
			case INS_LDD_HL_A:
			{
				mem->write_to_address(regs->HL--, regs->A);
				cycles->increment_cycles(2);
			} break;
			case INS_LDI_A_HL_:
			{
				regs->A = mem->read_from_address(regs->HL++);
				cycles->increment_cycles(2);
			} break;
			case INS_LDI_HL_A:
			{
				mem->write_to_address(regs->HL++, regs->A);
				cycles->increment_cycles(2);
			} break;

			// store and load at 0xFF00 + n
			case INS_LDH_nA:
			{
				Byte lo = fetch_byte();
				mem->write_to_address(0xFF00 + lo, regs->A);
				cycles->increment_cycles(2);
			} break;
			case INS_LDH_An:
			{
				Byte lo = fetch_byte();
				regs->A = mem->read_from_address(0xFF00 + lo);
				cycles->increment_cycles(2);
			} break;

			// ######### 16 bit loads ###########
			// immediate
			case INS_LD_BCnn:
			{
				regs->BC = fetch_word();
				cycles->increment_cycles(1);
			} break;
			case INS_LD_DEnn:
			{
				regs->DE = fetch_word();
				cycles->increment_cycles(1);
			} break;
			case INS_LD_HLnn:
			{
				regs->HL = fetch_word();
				cycles->increment_cycles(1);
			} break;
			case INS_LD_SPnn:
			{
				regs->sp = fetch_word();
				cycles->increment_cycles(1);
			} break;
			// stack load and store operations
			case INS_LD_SPHL:
			{
				regs->sp = regs->HL;
				cycles->increment_cycles(2);
			} break;
			case INS_LDHL_SPn:
			{
				SByte value = fetch_byte();
				bool carry = regs->carry;
				bool half_carry = regs->half_carry;
				regs->HL = word_add_lower_flags(regs->sp, value, carry, half_carry);
				regs->zero = 0;
				regs->negative = 0;
				regs->half_carry = half_carry;
				regs->carry = carry;
				cycles->increment_cycles(2);
			} break;

			default:
				return;
				break;
		}
	}
	
}


void GZ80::CPU::load_8_bit_value(Word& reg, Byte value)
{
	reg = value;
}
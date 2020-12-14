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

void GZ80::CPU::set_carries(Word reg, Word value, Word result, bool lo_carry)
{
	if (lo_carry)
	{
		regs->carry = (((reg >> 8) & 0b1) ^ ((value >> 8) & 0b1)) != ((result >> 8) & 0b1);
		regs->half_carry = (((reg >> 4) & 0b1) ^ ((value >> 4)) & 0b1) != ((result >> 4) & 0b1);
	}
	else
	{
		int sum = reg + value;
		regs->carry = sum != result;
		regs->half_carry = (((reg >> 12) & 0b1) ^ ((value >> 12)) & 0b1) != ((result >> 12) & 0b1);
	}
}

void GZ80::CPU::set_carries(Byte reg, Byte value, Byte result)
{
	Word sum = reg + value;
	regs->carry = sum != result;
	regs->half_carry = (((reg >> 4) & 0b1) ^ (value >> 4)) != ((result >> 4) & 0b1);
}

void GZ80::CPU::set_carries_borrow(Byte reg, Byte value, Byte result)
{
	regs->carry = (reg >= value) ? 1 : 0;
	regs->half_carry = (reg & 0xF) >= (value & 0xF);
}

void GZ80::CPU::add_to_accumulator(Byte value)
{
	Byte result = regs->A + value;
	set_carries(regs->A, value, result);
	regs->zero = result == 0;
	regs->negative = 0;
	regs->A = result;
	cycles->increment_cycles(1);
}

void GZ80::CPU::addc_to_accumulator(Byte value)
{
	Byte result = regs->A + value + regs->carry;
	set_carries(regs->A, value + regs->carry, result);
	regs->zero = result == 0;
	regs->negative = 0;
	regs->A = result;
	cycles->increment_cycles(1);
}

void GZ80::CPU::subtract_from_accumulator(Byte value)
{
	Byte result = regs->A - value;
	set_carries_borrow(regs->A, value, result);
	regs->zero = result == 0;
	regs->negative = 1;
	regs->A = result;
	cycles->increment_cycles(1);
}

void GZ80::CPU::subtractc_from_accumulator(Byte value)
{
	Byte result = regs->A - (value + regs->carry);
	set_carries_borrow(regs->A, value + regs->carry, result);
	regs->zero = result == 0;
	regs->negative = 1;
	regs->A = result;
	cycles->increment_cycles(1);
}

void GZ80::CPU::and_with_accumulator(Byte value)
{
	regs->negative = regs->carry = 0;
	regs->half_carry = 1;
	regs->A = regs->A & value;
	regs->zero = regs->A == 0;
	cycles->increment_cycles(1);
}

void GZ80::CPU::or_with_accumulator(Byte value)
{
	regs->negative = regs->carry = regs->half_carry = 0;
	regs->A = regs->A | value;
	regs->zero = regs->A == 0;
	cycles->increment_cycles(1);
}

void GZ80::CPU::xor_with_accumulator(Byte value)
{
	regs->negative = regs->carry = regs->half_carry = 0;
	regs->A = regs->A ^ value;
	regs->zero = regs->A == 0;
	cycles->increment_cycles(1);
}

void GZ80::CPU::compare_with_accumulator(Byte value)
{
	Byte result = regs->A - value;
	set_carries_borrow(regs->A, value, result);
	regs->zero = result == 0;
	regs->negative = 1;
	cycles->increment_cycles(1);
}

GZ80::Byte GZ80::CPU::increment(Byte value)
{
	regs->negative = 0;
	regs->half_carry = (value & 0xF) == 0xF;
	value++;
	regs->zero = value == 0;
	cycles->increment_cycles(1);
	return value;
}

GZ80::Word GZ80::CPU::increment(Word value)
{
	cycles->increment_cycles(2);
	return ++value;
}

GZ80::Byte GZ80::CPU::decrement(Byte value)
{
	regs->negative = 1;
	regs->half_carry = (value & 0xF) != 0x0;
	value--;
	regs->zero = value == 0;
	cycles->increment_cycles(1);
	return value;
}

GZ80::Word GZ80::CPU::decrement(Word value)
{
	cycles->increment_cycles(2);
	return --value;
}

void GZ80::CPU::add(Word value)
{
	Word result = regs->HL + value;
	set_carries(regs->HL, value, result, false);
	regs->negative = 0;
	regs->HL = result;
	cycles->increment_cycles(2);
}

void GZ80::CPU::push_register_onto_stack(Word reg)
{
	mem->write_to_address(regs->sp--, reg & 0xFF);
	mem->write_to_address(regs->sp--, reg >> 8);
	cycles->increment_cycles(4);
}

void GZ80::CPU::pop_value_from_stack(Word& reg)
{
	Word value = mem->read_from_address(++regs->sp) << 8;
	value += mem->read_from_address(++regs->sp);
	reg = value;
	cycles->increment_cycles(3);
}

GZ80::Byte GZ80::CPU::rotate_left(Byte value, bool through_carry)
{
	cycles->increment_cycles(1);
	regs->half_carry = regs->negative = 0;
	Byte old_carry = regs->carry;
	regs->carry = (value & 0x80) >> 7;
	Byte result;
	if (!through_carry)
	{
		result = (value << 1) + regs->carry;
	}
	else
	{
		result = ((value << 1) + old_carry);
	}
	regs->zero = result == 0;
	return result;
}

GZ80::Byte GZ80::CPU::rotate_right(Byte value, bool through_carry)
{
	cycles->increment_cycles(1);
	regs->half_carry = regs->negative = 0;
	Byte old_carry = regs->carry;
	regs->carry = (value & 0x01);
	Byte result;
	if (!through_carry)
	{
		result = (value >> 1) + (regs->carry << 7);
	}
	else
	{
		result = ((value >> 1) + (old_carry << 7));
	}
	regs->zero = result == 0;
	return result;
}

GZ80::Byte GZ80::CPU::shift_left(Byte value)
{
	cycles->increment_cycles(1);
	regs->half_carry = regs->negative = 0;
	regs->carry = (value & 0x80) >> 7;
	Byte result = (value << 1);
	regs->zero = result == 0;
	return result;
}

GZ80::Byte GZ80::CPU::shift_right(Byte value, bool logical)
{
	cycles->increment_cycles(1);
	regs->half_carry = regs->negative = 0;
	Byte bit_7 = (value & 0x80) >> 7;
	regs->carry = (value & 0x01);
	Byte result;
	if (logical)
	{
		result = (value >> 1);
	}
	else
	{
		result = ((value >> 1) + (bit_7 << 7));
	}
	regs->zero = result == 0;
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
				regs->HL = regs->sp + value;
				set_carries(regs->sp, value, regs->HL);
				regs->zero = 0;
				regs->negative = 0;
				cycles->increment_cycles(2);
			} break;
			case INS_LD_nnSP:
			{
				Word address = fetch_word();
				mem->write_to_address(address, (Byte)(regs->sp >> 7));
				mem->write_to_address(address + 1, (Byte)(regs->sp & 0xFF));
				cycles->increment_cycles(3);
			} break;
			case INS_PUSH_AF:
			{
				push_register_onto_stack(regs->AF);
			} break;
			case INS_PUSH_BC:
			{
				push_register_onto_stack(regs->BC);
			} break;
			case INS_PUSH_DE:
			{
				push_register_onto_stack(regs->DE);
			} break;
			case INS_PUSH_HL:
			{
				push_register_onto_stack(regs->HL);
			} break;
			case INS_POP_AF:
			{
				pop_value_from_stack(regs->AF);
			} break;
			case INS_POP_BC:
			{
				pop_value_from_stack(regs->BC);
			} break;
			case INS_POP_DE:
			{
				pop_value_from_stack(regs->DE);
			} break;
			case INS_POP_HL:
			{
				pop_value_from_stack(regs->HL);
			} break;
			// ###### 8 bit ALU #######
			// ADD
			case INS_ADD_AA:
			{
				add_to_accumulator(regs->A);
			} break;
			case INS_ADD_AB:
			{
				add_to_accumulator(regs->B);
			} break;
			case INS_ADD_AC:
			{
				add_to_accumulator(regs->C);
			} break;
			case INS_ADD_AD:
			{
				add_to_accumulator(regs->D);
			} break;
			case INS_ADD_AE:
			{
				add_to_accumulator(regs->E);
			} break;
			case INS_ADD_AH:
			{
				add_to_accumulator(regs->H);
			} break;
			case INS_ADD_AL:
			{
				add_to_accumulator(regs->L);
			} break;
			case INS_ADD_AHL:
			{
				add_to_accumulator(mem->read_from_address(regs->HL));
				cycles->increment_cycles(1);
			} break;
			case INS_ADD_AIM:
			{
				Byte value = fetch_byte();
				add_to_accumulator(value);
			} break;
			// ADC
			case INS_ADC_AA:
			{
				addc_to_accumulator(regs->A);
			} break;
			case INS_ADC_AB:
			{
				addc_to_accumulator(regs->B);
			} break;
			case INS_ADC_AC:
			{
				addc_to_accumulator(regs->C);
			} break;
			case INS_ADC_AD:
			{
				addc_to_accumulator(regs->D);
			} break;
			case INS_ADC_AE:
			{
				addc_to_accumulator(regs->E);
			} break;
			case INS_ADC_AH:
			{
				addc_to_accumulator(regs->H);
			} break;
			case INS_ADC_AL:
			{
				addc_to_accumulator(regs->L);
			} break;
			case INS_ADC_AHL:
			{
				addc_to_accumulator(mem->read_from_address(regs->HL));
				cycles->increment_cycles(1);
			} break;
			case INS_ADC_AIM:
			{
				Byte value = fetch_byte();
				addc_to_accumulator(value);
			} break;
			// SUB
			case INS_SUB_AA:
			{
				subtract_from_accumulator(regs->A);
			} break;
			case INS_SUB_AB:
			{
				subtract_from_accumulator(regs->B);
			} break;
			case INS_SUB_AC:
			{
				subtract_from_accumulator(regs->C);
			} break;
			case INS_SUB_AD:
			{
				subtract_from_accumulator(regs->D);
			} break;
			case INS_SUB_AE:
			{
				subtract_from_accumulator(regs->E);
			} break;
			case INS_SUB_AH:
			{
				subtract_from_accumulator(regs->H);
			} break;
			case INS_SUB_AL:
			{
				subtract_from_accumulator(regs->L);
			} break;
			case INS_SUB_AHL:
			{
				subtract_from_accumulator(mem->read_from_address(regs->HL));
				cycles->increment_cycles(1);
			} break;
			case INS_SUB_AIM:
			{
				Byte value = fetch_byte();
				subtract_from_accumulator(value);
			} break;
			// SBC
			case INS_SBC_AA:
			{
				subtractc_from_accumulator(regs->A);
			} break;
			case INS_SBC_AB:
			{
				subtractc_from_accumulator(regs->B);
			} break;
			case INS_SBC_AC:
			{
				subtractc_from_accumulator(regs->C);
			} break;
			case INS_SBC_AD:
			{
				subtractc_from_accumulator(regs->D);
			} break;
			case INS_SBC_AE:
			{
				subtractc_from_accumulator(regs->E);
			} break;
			case INS_SBC_AH:
			{
				subtractc_from_accumulator(regs->H);
			} break;
			case INS_SBC_AL:
			{
				subtractc_from_accumulator(regs->L);
			} break;
			case INS_SBC_AHL:
			{
				subtractc_from_accumulator(mem->read_from_address(regs->HL));
				cycles->increment_cycles(1);
			} break;
			case INS_SBC_AIM:
			{
				Byte value = fetch_byte();
				subtractc_from_accumulator(value);
			} break;
			// AND
			case INS_AND_AA:
			{
				and_with_accumulator(regs->A);
			} break;
			case INS_AND_AB:
			{
				and_with_accumulator(regs->B);
			} break;
			case INS_AND_AC:
			{
				and_with_accumulator(regs->C);
			} break;
			case INS_AND_AD:
			{
				and_with_accumulator(regs->D);
			} break;
			case INS_AND_AE:
			{
				and_with_accumulator(regs->E);
			} break;
			case INS_AND_AH:
			{
				and_with_accumulator(regs->H);
			} break;
			case INS_AND_AL:
			{
				and_with_accumulator(regs->L);
			} break;
			case INS_AND_AHL:
			{
				and_with_accumulator(mem->read_from_address(regs->HL));
				cycles->increment_cycles(1);
			} break;
			case INS_AND_AIM:
			{
				Byte value = fetch_byte();
				and_with_accumulator(value);
			} break;
			// OR
			case INS_OR_AA:
			{
				or_with_accumulator(regs->A);
			} break;
			case INS_OR_AB:
			{
				or_with_accumulator(regs->B);
			} break;
			case INS_OR_AC:
			{
				or_with_accumulator(regs->C);
			} break;
			case INS_OR_AD:
			{
				or_with_accumulator(regs->D);
			} break;
			case INS_OR_AE:
			{
				or_with_accumulator(regs->E);
			} break;
			case INS_OR_AH:
			{
				or_with_accumulator(regs->H);
			} break;
			case INS_OR_AL:
			{
				or_with_accumulator(regs->L);
			} break;
			case INS_OR_AHL:
			{
				or_with_accumulator(mem->read_from_address(regs->HL));
				cycles->increment_cycles(1);
			} break;
			case INS_OR_AIM:
			{
				Byte value = fetch_byte();
				or_with_accumulator(value);
			} break;
			// XOR
			case INS_XOR_AA:
			{
				xor_with_accumulator(regs->A);
			} break;
			case INS_XOR_AB:
			{
				xor_with_accumulator(regs->B);
			} break;
			case INS_XOR_AC:
			{
				xor_with_accumulator(regs->C);
			} break;
			case INS_XOR_AD:
			{
				xor_with_accumulator(regs->D);
			} break;
			case INS_XOR_AE:
			{
				xor_with_accumulator(regs->E);
			} break;
			case INS_XOR_AH:
			{
				xor_with_accumulator(regs->H);
			} break;
			case INS_XOR_AL:
			{
				xor_with_accumulator(regs->L);
			} break;
			case INS_XOR_AHL:
			{
				xor_with_accumulator(mem->read_from_address(regs->HL));
				cycles->increment_cycles(1);
			} break;
			case INS_XOR_AIM:
			{
				Byte value = fetch_byte();
				xor_with_accumulator(value);
			} break;
			// CP
			case INS_CP_AA:
			{
				compare_with_accumulator(regs->A);
			} break;
			case INS_CP_AB:
			{
				compare_with_accumulator(regs->B);
			} break;
			case INS_CP_AC:
			{
				compare_with_accumulator(regs->C);
			} break;
			case INS_CP_AD:
			{
				compare_with_accumulator(regs->D);
			} break;
			case INS_CP_AE:
			{
				compare_with_accumulator(regs->E);
			} break;
			case INS_CP_AH:
			{
				compare_with_accumulator(regs->H);
			} break;
			case INS_CP_AL:
			{
				compare_with_accumulator(regs->L);
			} break;
			case INS_CP_AHL:
			{
				compare_with_accumulator(mem->read_from_address(regs->HL));
				cycles->increment_cycles(1);
			} break;
			case INS_CP_AIM:
			{
				Byte value = fetch_byte();
				compare_with_accumulator(value);
			} break;
			// INC
			case INS_INC_A:
			{
				regs->A = increment(regs->A);
			} break;
			case INS_INC_B:
			{
				regs->B = increment(regs->B);
			} break;
			case INS_INC_C:
			{
				regs->C = increment(regs->C);
			} break;
			case INS_INC_D:
			{
				regs->D = increment(regs->D);
			} break;
			case INS_INC_E:
			{
				regs->E = increment(regs->E);
			} break;
			case INS_INC_H:
			{
				regs->H = increment(regs->H);
			} break;
			case INS_INC_L:
			{
				regs->L = increment(regs->L);
			} break;
			case INS_INC_HL_:
			{
				mem->write_to_address(regs->HL, increment(mem->read_from_address(regs->HL)));
				cycles->increment_cycles(2);
			} break;
			// DEC
			case INS_DEC_A:
			{
				regs->A = decrement(regs->A);
			} break;
			case INS_DEC_B:
			{
				regs->B = decrement(regs->B);
			} break;
			case INS_DEC_C:
			{
				regs->C = decrement(regs->C);
			} break;
			case INS_DEC_D:
			{
				regs->D = decrement(regs->D);
			} break;
			case INS_DEC_E:
			{
				regs->E = decrement(regs->E);
			} break;
			case INS_DEC_H:
			{
				regs->H = decrement(regs->H);
			} break;
			case INS_DEC_L:
			{
				regs->L = decrement(regs->L);
			} break;
			case INS_DEC_HL_:
			{
				mem->write_to_address(regs->HL, decrement(mem->read_from_address(regs->HL)));
				cycles->increment_cycles(2);
			} break;
			// ##### 16 bit ALU #######
			// ADD_HL
			case INS_ADD_HLBC:
			{
				add(regs->BC);
			} break;
			case INS_ADD_HLDE:
			{
				add(regs->DE);
			} break;
			case INS_ADD_HLHL:
			{
				add(regs->HL);
			} break;
			case INS_ADD_HLSP:
			{
				add(regs->sp);
			} break;
			// ADD_SPIM
			case INS_ADD_SPIM:
			{
				SByte value = fetch_byte();
				Word result = regs->sp + value;
				set_carries(regs->sp, value, result);
				regs->sp = result;
				regs->zero = 0;
				regs->negative = 0;
				cycles->increment_cycles(3);
			} break;
			// INC
			case INS_INC_BC:
			{
				regs->BC = increment(regs->BC);
			} break;
			case INS_INC_DE:
			{
				regs->DE = increment(regs->DE);
			} break;
			case INS_INC_HL:
			{
				regs->HL = increment(regs->HL);
			} break;
			case INS_INC_SP:
			{
				regs->sp = increment(regs->sp);
			} break;
			// DEC
			case INS_DEC_BC:
			{
				regs->BC = decrement(regs->BC);
			} break;
			case INS_DEC_DE:
			{
				regs->DE = decrement(regs->DE);
			} break;
			case INS_DEC_HL:
			{
				regs->HL = decrement(regs->HL);
			} break;
			case INS_DEC_SP:
			{
				regs->sp = decrement(regs->sp);
			} break;
			// ###### Rotates and Shifts #########
			case INS_RLCA:
			{
				regs->A = rotate_left(regs->A);
			} break;
			case INS_RLA:
			{
				regs->A = rotate_left(regs->A, true);
			} break;
			case INS_RRCA:
			{
				regs->A = rotate_right(regs->A);
			} break;
			case INS_RRA:
			{
				regs->A = rotate_right(regs->A, true);
			} break;



			case CB_INS:
			{
				cb_handler();
			} break;
			default:
				return;
				break;
		}
	}
	
}

void GZ80::CPU::cb_handler()
{
	Byte opcode = fetch_byte();
	switch (opcode)
	{
		// ######### Rotations and shifts #############
		// RLC
		case INS_RLC_A:
		{
			regs->A = rotate_left(regs->A);
		} break;
		case INS_RLC_B:
		{
			regs->B = rotate_left(regs->B);
		} break;
		case INS_RLC_C:
		{
			regs->C = rotate_left(regs->C);
		} break;
		case INS_RLC_D:
		{
			regs->D = rotate_left(regs->D);
		} break;
		case INS_RLC_E:
		{
			regs->E = rotate_left(regs->E);
		} break;
		case INS_RLC_H:
		{
			regs->H = rotate_left(regs->H);
		} break;
		case INS_RLC_L:
		{
			regs->L = rotate_left(regs->L);
		} break;
		case INS_RLC_HL_:
		{
			mem->write_to_address(regs->HL, rotate_left(mem->read_from_address(regs->HL)));
			cycles->increment_cycles(2);
		} break;
		// RL
		case INS_RL_A:
		{
			regs->A = rotate_left(regs->A, true);
		} break;
		case INS_RL_B:
		{
			regs->B = rotate_left(regs->B, true);
		} break;
		case INS_RL_C:
		{
			regs->C = rotate_left(regs->C, true);
		} break;
		case INS_RL_D:
		{
			regs->D = rotate_left(regs->D, true);
		} break;
		case INS_RL_E:
		{
			regs->E = rotate_left(regs->E, true);
		} break;
		case INS_RL_H:
		{
			regs->H = rotate_left(regs->H, true);
		} break;
		case INS_RL_L:
		{
			regs->L = rotate_left(regs->L, true);
		} break;
		case INS_RL_HL_:
		{
			mem->write_to_address(regs->HL, rotate_left(mem->read_from_address(regs->HL), true));
			cycles->increment_cycles(2);
		} break;
		//RRC
		case INS_RRC_A:
		{
			regs->A = rotate_right(regs->A);
		} break;
		case INS_RRC_B:
		{
			regs->B = rotate_right(regs->B);
		} break;
		case INS_RRC_C:
		{
			regs->C = rotate_right(regs->C);
		} break;
		case INS_RRC_D:
		{
			regs->D = rotate_right(regs->D);
		} break;
		case INS_RRC_E:
		{
			regs->E = rotate_right(regs->E);
		} break;
		case INS_RRC_H:
		{
			regs->H = rotate_right(regs->H);
		} break;
		case INS_RRC_L:
		{
			regs->L = rotate_right(regs->L);
		} break;
		case INS_RRC_HL_:
		{
			mem->write_to_address(regs->HL, rotate_right(mem->read_from_address(regs->HL)));
			cycles->increment_cycles(2);
		} break;
		// RR
		case INS_RR_A:
		{
			regs->A = rotate_right(regs->A, true);
		} break;
		case INS_RR_B:
		{
			regs->B = rotate_right(regs->B, true);
		} break;
		case INS_RR_C:
		{
			regs->C = rotate_right(regs->C, true);
		} break;
		case INS_RR_D:
		{
			regs->D = rotate_right(regs->D, true);
		} break;
		case INS_RR_E:
		{
			regs->E = rotate_right(regs->E, true);
		} break;
		case INS_RR_H:
		{
			regs->H = rotate_right(regs->H, true);
		} break;
		case INS_RR_L:
		{
			regs->L = rotate_right(regs->L, true);
		} break;
		case INS_RR_HL_:
		{
			mem->write_to_address(regs->HL, rotate_right(mem->read_from_address(regs->HL), true));
			cycles->increment_cycles(2);
		} break;
		// SLA
		case INS_SLA_A:
		{
			regs->A = shift_left(regs->A);
		} break;
		case INS_SLA_B:
		{
			regs->B = shift_left(regs->B);
		} break;
		case INS_SLA_C:
		{
			regs->C = shift_left(regs->C);
		} break;
		case INS_SLA_D:
		{
			regs->D = shift_left(regs->D);
		} break;
		case INS_SLA_E:
		{
			regs->E = shift_left(regs->E);
		} break;
		case INS_SLA_H:
		{
			regs->H = shift_left(regs->H);
		} break;
		case INS_SLA_L:
		{
			regs->L = shift_left(regs->L);
		} break;
		case INS_SLA_HL_:
		{
			mem->write_to_address(regs->HL, shift_left(mem->read_from_address(regs->HL)));
			cycles->increment_cycles(2);
		} break;
		// SRA
		case INS_SRA_A:
		{
			regs->A = shift_right(regs->A);
		} break;
		case INS_SRA_B:
		{
			regs->B = shift_right(regs->B);
		} break;
		case INS_SRA_C:
		{
			regs->C = shift_right(regs->C);
		} break;
		case INS_SRA_D:
		{
			regs->D = shift_right(regs->D);
		} break;
		case INS_SRA_E:
		{
			regs->E = shift_right(regs->E);
		} break;
		case INS_SRA_H:
		{
			regs->H = shift_right(regs->H);
		} break;
		case INS_SRA_L:
		{
			regs->L = shift_right(regs->L);
		} break;
		case INS_SRA_HL_:
		{
			mem->write_to_address(regs->HL, shift_right(mem->read_from_address(regs->HL)));
			cycles->increment_cycles(2);
		} break;
		// SRL
		case INS_SRL_A:
		{
			regs->A = shift_right(regs->A, true);
		} break;
		case INS_SRL_B:
		{
			regs->B = shift_right(regs->B, true);
		} break;
		case INS_SRL_C:
		{
			regs->C = shift_right(regs->C, true);
		} break;
		case INS_SRL_D:
		{
			regs->D = shift_right(regs->D, true);
		} break;
		case INS_SRL_E:
		{
			regs->E = shift_right(regs->E, true);
		} break;
		case INS_SRL_H:
		{
			regs->H = shift_right(regs->H, true);
		} break;
		case INS_SRL_L:
		{
			regs->L = shift_right(regs->L, true);
		} break;
		case INS_SRL_HL_:
		{
			mem->write_to_address(regs->HL, shift_right(mem->read_from_address(regs->HL), true));
			cycles->increment_cycles(2);
		} break;
		default:
			return;
			break;
	}
}


void GZ80::CPU::load_8_bit_value(Word& reg, Byte value)
{
	reg = value;
}
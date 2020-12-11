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

void GZ80::CPU::execute(Byte opcode, Word machine_cycles)
{
	while (cycles->mc < machine_cycles)
	{
		switch (opcode)
		{
			// 8 bit loads
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
			case INS_LD_HLn:
			{
				Byte value = fetch_byte();
				mem->write_to_address(regs->HL, value);
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
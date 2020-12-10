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

GZ80::Byte GZ80::CPU::fetch_byte()
{
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
		case 0x0E:
		{
			Byte value = fetch_byte();
			regs->C = value;
			cycles->increment_cycles(1);
		} break;
		case 0x16:
		{
			Byte value = fetch_byte();
			regs->D = value;
			cycles->increment_cycles(1);
		} break;
		case 0x1E:
		{
			Byte value = fetch_byte();
			regs->E = value;
			cycles->increment_cycles(1);
		} break;
		case 0x26:
		{
			Byte value = fetch_byte();
			regs->H = value;
			cycles->increment_cycles(1);
		} break;

		case 0x2E:
		{
			Byte value = fetch_byte();
			regs->L = value;
			cycles->increment_cycles(1);
		} break;
		default:
			break;
		}
	}
	
}


void GZ80::CPU::load_8_bit_value(Word& reg, Byte value)
{
	reg = value;
}
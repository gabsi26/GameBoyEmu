#include <cstdio>
#include "GZ80.h"

int main()
{
	GZ80::CPU cpu;
	cpu.regs->AF = 0xFFEE;
	printf("%d\n", cpu.regs->A);
	printf("%d\n",cpu.regs->F);
	printf("%d\n", cpu.regs->carry);
	printf("%d\n", cpu.regs->half_carry);
	printf("%d\n", cpu.regs->negative);
	printf("%d\n", cpu.regs->zero);
}
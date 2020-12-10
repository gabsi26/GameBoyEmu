#include "pch.h"
#include "../GameBoyEmu/GZ80.h"
#include "../GameBoyEmu/memory.h"
using namespace GZ80;
class _8BitLoadTests : public testing::Test
{
public:
	GZ80::CPU cpu;
	virtual void SetUp()
	{
	}

	virtual void TearDown()
	{
	}
};

TEST_F(_8BitLoadTests, LDBnCanLoadAValueIntoRegisterB)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_Bn);
	cpu.mem->write_to_address(0x101, 0x42);
	cpu.regs->B = 0x00;
	cpu.regs->pc = 0x100;
	// when
	Byte opcode = cpu.fetch_byte();
	cpu.execute(opcode, 2);
	// then
	EXPECT_EQ(cpu.regs->B, 0x42);
	EXPECT_EQ(cpu.regs->pc, 0x102);
}

TEST_F(_8BitLoadTests, LDCnCanLoadAValueIntoRegisterC)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_Cn);
	cpu.mem->write_to_address(0x101, 0x42);
	cpu.regs->C = 0x00;
	cpu.regs->pc = 0x100;
	// when
	Byte opcode = cpu.fetch_byte();
	cpu.execute(opcode, 2);
	// then
	EXPECT_EQ(cpu.regs->C, 0x42);
	EXPECT_EQ(cpu.regs->pc, 0x102);
}

TEST_F(_8BitLoadTests, LDDnCanLoadAValueIntoRegisterD)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_Dn);
	cpu.mem->write_to_address(0x101, 0x42);
	cpu.regs->D = 0x00;
	cpu.regs->pc = 0x100;
	// when
	Byte opcode = cpu.fetch_byte();
	cpu.execute(opcode, 2);
	// then
	EXPECT_EQ(cpu.regs->D, 0x42);
	EXPECT_EQ(cpu.regs->pc, 0x102);
}

TEST_F(_8BitLoadTests, LDEnCanLoadAValueIntoRegisterE)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_En);
	cpu.mem->write_to_address(0x101, 0x42);
	cpu.regs->E = 0x00;
	cpu.regs->pc = 0x100;
	// when
	Byte opcode = cpu.fetch_byte();
	cpu.execute(opcode, 2);
	// then
	EXPECT_EQ(cpu.regs->E, 0x42);
	EXPECT_EQ(cpu.regs->pc, 0x102);
}

TEST_F(_8BitLoadTests, LDHnCanLoadAValueIntoRegisterH)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_Hn);
	cpu.mem->write_to_address(0x101, 0x42);
	cpu.regs->H = 0x00;
	cpu.regs->pc = 0x100;
	// when
	Byte opcode = cpu.fetch_byte();
	cpu.execute(opcode, 2);
	// then
	EXPECT_EQ(cpu.regs->H, 0x42);
	EXPECT_EQ(cpu.regs->pc, 0x102);
}

TEST_F(_8BitLoadTests, LDLnCanLoadAValueIntoRegisterL)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_Ln);
	cpu.mem->write_to_address(0x101, 0x42);
	cpu.regs->L = 0x00;
	cpu.regs->pc = 0x100;
	// when
	Byte opcode = cpu.fetch_byte();
	cpu.execute(opcode, 2);
	// then
	EXPECT_EQ(cpu.regs->L, 0x42);
	EXPECT_EQ(cpu.regs->pc, 0x102);
}

TEST_F(_8BitLoadTests, LDAACanLoadAValueFromRegisterAIntoRegisterA)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_AA);
	cpu.regs->A = 0x10;
	cpu.regs->pc = 0x100;
	// when
	Byte opcode = cpu.fetch_byte();
	cpu.execute(opcode, 1);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x101);
}
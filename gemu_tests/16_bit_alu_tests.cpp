#include "pch.h"
#include "../GameBoyEmu/GZ80.h"
#include "../GameBoyEmu/memory.h"
using namespace GZ80;
class _16BitALUTests : public testing::Test
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

// ################## ADD_HL #####################
TEST_F(_16BitALUTests, ADDHLBCCanAddRegisterBCToRegisterHL)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_ADD_HLBC);
	cpu.regs->HL = 0x0002;
	cpu.regs->BC = 0x0100;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	cpu.regs->negative = 1;
	cpu.regs->carry = 1;
	cpu.regs->half_carry = 1;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->HL, 0x0102);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_16BitALUTests, ADDHLBCCanAddRegisterBCToRegisterHLWithHalfCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_ADD_HLBC);
	cpu.regs->HL = 0x0102;
	cpu.regs->BC = 0x0F00;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	cpu.regs->negative = 1;
	cpu.regs->carry = 1;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->HL, 0x1002);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_16BitALUTests, ADDHLBCCanAddRegisterBCToRegisterHLWithCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_ADD_HLBC);
	cpu.regs->HL = 0xF000;
	cpu.regs->BC = 0x1000;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 1;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->HL, 0x0000);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_16BitALUTests, ADDHLBCCanAddRegisterBCToRegisterHLWithCarryAndHalfCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_ADD_HLBC);
	cpu.regs->HL = 0xFF00;
	cpu.regs->BC = 0x1100;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->HL, 0x1000);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// ######### ADD_SPIM ################
TEST_F(_16BitALUTests, ADD_SPIMCanAddImmediateValueToSPWithoutSettingAnyFlag)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_ADD_SPIM);
	cpu.mem->write_to_address(0x101, 0x02);
	cpu.regs->sp = 0xFFF8;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = cpu.regs->negative = 1;
	cpu.regs->half_carry = cpu.regs->carry = 0;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->sp, 0xFFFA);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
	EXPECT_EQ(cpu.regs->zero, 0);
	EXPECT_EQ(cpu.regs->negative, 0);
	EXPECT_EQ(cpu.regs->half_carry, 0);
	EXPECT_EQ(cpu.regs->carry, 0);
}

TEST_F(_16BitALUTests, ADD_SPIMCanAddImmediateValueToSPWhileSettingCarryAndHalfCarryFlags)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_ADD_SPIM);
	cpu.mem->write_to_address(0x101, 0xFF);
	cpu.regs->sp = 0xFFFF;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = cpu.regs->negative = 1;
	cpu.regs->half_carry = cpu.regs->carry = 0;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->sp, 0xFFFE);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
	EXPECT_EQ(cpu.regs->zero, 0);
	EXPECT_EQ(cpu.regs->negative, 0);
	EXPECT_EQ(cpu.regs->half_carry, 1);
	EXPECT_EQ(cpu.regs->carry, 1);
}

// ################## INC #################
TEST_F(_16BitALUTests, INC_BCCanIncreaseBC)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_INC_BC);
	cpu.regs->BC = 0x0000;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->BC, 0x0001);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_16BitALUTests, INC_BCCanIncreaseBCAndWrap)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_INC_BC);
	cpu.regs->BC = 0xFFFF;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->BC, 0x0000);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_16BitALUTests, INC_DECanIncreaseDE)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_INC_DE);
	cpu.regs->DE = 0x0000;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->DE, 0x0001);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_16BitALUTests, INC_HLCanIncreaseHL)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_INC_HL);
	cpu.regs->HL = 0x0000;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->HL, 0x0001);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_16BitALUTests, INC_SPCanIncreaseSP)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_INC_SP);
	cpu.regs->sp = 0x0000;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->sp, 0x0001);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// ################### DEC #####################
TEST_F(_16BitALUTests, DEC_BCCanDecreaseBC)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_DEC_BC);
	cpu.regs->BC = 0x0002;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->BC, 0x0001);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_16BitALUTests, DEC_BCCanDecreaseBCAndWrap)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_DEC_BC);
	cpu.regs->BC = 0x0000;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->BC, 0xFFFF);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_16BitALUTests, DEC_DECanDecreaseDE)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_DEC_DE);
	cpu.regs->DE = 0x0002;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->DE, 0x0001);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_16BitALUTests, DEC_HLCanDecreaseHL)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_DEC_HL);
	cpu.regs->HL = 0x0002;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->HL, 0x0001);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_16BitALUTests, DEC_SPCanDecreaseSP)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_DEC_SP);
	cpu.regs->sp = 0x0002;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->sp, 0x0001);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}
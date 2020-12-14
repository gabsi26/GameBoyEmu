#include "pch.h"
#include "../GameBoyEmu/GZ80.h"
#include "../GameBoyEmu/memory.h"
using namespace GZ80;
class BitTests : public testing::Test
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

// ################## BIT0 #####################
TEST_F(BitTests, BIT0ACanTestBit0OfRegisterANonZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_BIT_0A);
	cpu.regs->A = 0x01;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, BIT0ACanTestBit0OfRegisterAZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_BIT_0A);
	cpu.regs->A = 0x00;
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
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, BIT0_HL_CanTestBit0OfAddress_HL_NonZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_BIT_0_HL_);
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x0200, 0x01);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, BIT0_HL_CanTestBit0OfAddress_HL_Zero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_BIT_0_HL_);
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x0200, 0x00);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// ################## BIT1 #####################
TEST_F(BitTests, BIT1ACanTestBit1OfRegisterANonZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_BIT_1A);
	cpu.regs->A = 0x02;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, BIT1ACanTestBit1OfRegisterAZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_BIT_1A);
	cpu.regs->A = 0x00;
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
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, BIT1_HL_CanTestBit1OfAddress_HL_NonZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_BIT_1_HL_);
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x0200, 0x02);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, BIT1_HL_CanTestBit1OfAddress_HL_Zero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_BIT_1_HL_);
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x0200, 0x00);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// ################## BIT2 #####################
TEST_F(BitTests, BIT2ACanTestBit2OfRegisterANonZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_BIT_2A);
	cpu.regs->A = 0x04;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, BIT2ACanTestBit2OfRegisterAZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_BIT_2A);
	cpu.regs->A = 0x00;
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
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, BIT2_HL_CanTestBit2OfAddress_HL_NonZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_BIT_2_HL_);
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x0200, 0x04);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, BIT2_HL_CanTestBit2OfAddress_HL_Zero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_BIT_2_HL_);
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x0200, 0x00);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// ################## BIT3 #####################
TEST_F(BitTests, BIT3ACanTestBit3OfRegisterANonZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_BIT_3A);
	cpu.regs->A = 0x08;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, BIT3ACanTestBit3OfRegisterAZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_BIT_3A);
	cpu.regs->A = 0x00;
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
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, BIT3_HL_CanTestBit3OfAddress_HL_NonZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_BIT_3_HL_);
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x0200, 0x08);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, BIT3_HL_CanTestBit3OfAddress_HL_Zero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_BIT_3_HL_);
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x0200, 0x00);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// ################## BIT4 #####################
TEST_F(BitTests, BIT4ACanTestBit4OfRegisterANonZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_BIT_4A);
	cpu.regs->A = 0x10;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, BIT4ACanTestBit4OfRegisterAZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_BIT_4A);
	cpu.regs->A = 0x00;
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
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, BIT4_HL_CanTestBit4OfAddress_HL_NonZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_BIT_4_HL_);
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x0200, 0x10);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, BIT4_HL_CanTestBit4OfAddress_HL_Zero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_BIT_4_HL_);
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x0200, 0x00);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// ################## BIT5 #####################
TEST_F(BitTests, BIT5ACanTestBit5OfRegisterANonZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_BIT_5A);
	cpu.regs->A = 0x20;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, BIT5ACanTestBit5OfRegisterAZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_BIT_5A);
	cpu.regs->A = 0x00;
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
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, BIT5_HL_CanTestBit5OfAddress_HL_NonZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_BIT_5_HL_);
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x0200, 0x20);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, BIT5_HL_CanTestBit5OfAddress_HL_Zero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_BIT_5_HL_);
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x0200, 0x00);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// ################## BIT6 #####################
TEST_F(BitTests, BIT6ACanTestBit6OfRegisterANonZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_BIT_6A);
	cpu.regs->A = 0x40;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, BIT6ACanTestBit6OfRegisterAZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_BIT_6A);
	cpu.regs->A = 0x00;
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
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, BIT6_HL_CanTestBit6OfAddress_HL_NonZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_BIT_6_HL_);
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x0200, 0x40);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, BIT6_HL_CanTestBit6OfAddress_HL_Zero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_BIT_6_HL_);
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x0200, 0x00);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// ################## BIT7 #####################
TEST_F(BitTests, BIT7ACanTestBit7OfRegisterANonZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_BIT_7A);
	cpu.regs->A = 0x80;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, BIT7ACanTestBit7OfRegisterAZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_BIT_7A);
	cpu.regs->A = 0x00;
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
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, BIT7_HL_CanTestBit7OfAddress_HL_NonZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_BIT_7_HL_);
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x0200, 0x80);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, BIT7_HL_CanTestBit7OfAddress_HL_Zero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_BIT_7_HL_);
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x0200, 0x00);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// ################# RES0 #################
TEST_F(BitTests, RES0ACanResetBit0OfRegisterANonZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RES_0A);
	cpu.regs->A = 0x01;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, RES0ACanResetBit0OfRegisterANonZeroDoesntEffectOtherBits)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RES_0A);
	cpu.regs->A = 0x81;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x80);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, RES0ACanResetBit0OfRegisterAZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RES_0A);
	cpu.regs->A = 0x00;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, RES0_HL_CanResetBit0OfAddress_HL_NonZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RES_0_HL_);
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x01);
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, RES0_HL_CanResetBit0OfAddress_HL_Zero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RES_0_HL_);
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x00);
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// ################# RES1 #################
TEST_F(BitTests, RES1ACanResetBit1OfRegisterANonZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RES_1A);
	cpu.regs->A = 0x02;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, RES1ACanResetBit1OfRegisterANonZeroDoesntEffectOtherBits)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RES_1A);
	cpu.regs->A = 0x82;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x80);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, RES1ACanResetBit1OfRegisterAZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RES_1A);
	cpu.regs->A = 0x00;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, RES1_HL_CanResetBit1OfAddress_HL_NonZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RES_1_HL_);
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x02);
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, RES1_HL_CanResetBit1OfAddress_HL_Zero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RES_1_HL_);
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x00);
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// ################# RES2 #################
TEST_F(BitTests, RES2ACanResetBit2OfRegisterANonZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RES_2A);
	cpu.regs->A = 0x04;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, RES2ACanResetBit2OfRegisterANonZeroDoesntEffectOtherBits)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RES_2A);
	cpu.regs->A = 0x84;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x80);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, RES2ACanResetBit2OfRegisterAZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RES_2A);
	cpu.regs->A = 0x00;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, RES2_HL_CanResetBit2OfAddress_HL_NonZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RES_2_HL_);
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x04);
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, RES2_HL_CanResetBit2OfAddress_HL_Zero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RES_2_HL_);
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x00);
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// ################# RES3 #################
TEST_F(BitTests, RES3ACanResetBit3OfRegisterANonZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RES_3A);
	cpu.regs->A = 0x08;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, RES3ACanResetBit3OfRegisterANonZeroDoesntEffectOtherBits)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RES_3A);
	cpu.regs->A = 0x88;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x80);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, RES3ACanResetBit3OfRegisterAZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RES_3A);
	cpu.regs->A = 0x00;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, RES3_HL_CanResetBit3OfAddress_HL_NonZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RES_3_HL_);
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x08);
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, RES3_HL_CanResetBit3OfAddress_HL_Zero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RES_3_HL_);
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x00);
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// ################# RES4 #################
TEST_F(BitTests, RES4ACanResetBit4OfRegisterANonZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RES_4A);
	cpu.regs->A = 0x10;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, RES4ACanResetBit4OfRegisterANonZeroDoesntEffectOtherBits)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RES_4A);
	cpu.regs->A = 0x18;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x08);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, RES4ACanResetBit4OfRegisterAZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RES_4A);
	cpu.regs->A = 0x00;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, RES4_HL_CanResetBit4OfAddress_HL_NonZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RES_4_HL_);
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x10);
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, RES4_HL_CanResetBit4OfAddress_HL_Zero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RES_4_HL_);
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x00);
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// ################# RES5 #################
TEST_F(BitTests, RES5ACanResetBit5OfRegisterANonZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RES_5A);
	cpu.regs->A = 0x20;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, RES5ACanResetBit5OfRegisterANonZeroDoesntEffectOtherBits)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RES_5A);
	cpu.regs->A = 0x28;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x08);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, RES5ACanResetBit5OfRegisterAZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RES_5A);
	cpu.regs->A = 0x00;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, RES5_HL_CanResetBit5OfAddress_HL_NonZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RES_5_HL_);
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x20);
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, RES5_HL_CanResetBit5OfAddress_HL_Zero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RES_5_HL_);
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x00);
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// ################# RES6 #################
TEST_F(BitTests, RES6ACanResetBit6OfRegisterANonZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RES_6A);
	cpu.regs->A = 0x40;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, RES6ACanResetBit6OfRegisterANonZeroDoesntEffectOtherBits)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RES_6A);
	cpu.regs->A = 0x48;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x08);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, RES6ACanResetBit6OfRegisterAZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RES_6A);
	cpu.regs->A = 0x00;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, RES6_HL_CanResetBit6OfAddress_HL_NonZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RES_6_HL_);
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x40);
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, RES6_HL_CanResetBit6OfAddress_HL_Zero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RES_6_HL_);
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x00);
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// ################# RES7 #################
TEST_F(BitTests, RES7ACanResetBit7OfRegisterANonZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RES_7A);
	cpu.regs->A = 0x80;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, RES7ACanResetBit7OfRegisterANonZeroDoesntEffectOtherBits)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RES_7A);
	cpu.regs->A = 0x88;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x08);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, RES7ACanResetBit7OfRegisterAZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RES_7A);
	cpu.regs->A = 0x00;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, RES7_HL_CanResetBit7OfAddress_HL_NonZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RES_7_HL_);
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x80);
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, RES7_HL_CanResetBit7OfAddress_HL_Zero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RES_7_HL_);
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x00);
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}
// ################# SET0 #################
TEST_F(BitTests, SET0ACanSetBit0OfRegisterANotSet)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SET_0A);
	cpu.regs->A = 0x00;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x01);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, SET0ACanSetBit0OfRegisterANotSetDoesntEffectOtherBits)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SET_0A);
	cpu.regs->A = 0x80;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x81);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, SET0ACanSetBit0OfRegisterASet)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SET_0A);
	cpu.regs->A = 0x01;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x01);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, SET0_HL_CanSetBit0OfAddress_HL_NotSet)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SET_0_HL_);
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x00);
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x01);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, SET0_HL_CanSetBit0OfAddress_HL_Set)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SET_0_HL_);
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x01);
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x01);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}
// ################# SET1 #################
TEST_F(BitTests, SET1ACanSetBit1OfRegisterANotSet)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SET_1A);
	cpu.regs->A = 0x00;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x02);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, SET1ACanSetBit1OfRegisterANotSetDoesntEffectOtherBits)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SET_1A);
	cpu.regs->A = 0x80;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x82);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, SET1ACanSetBit1OfRegisterASet)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SET_1A);
	cpu.regs->A = 0x02;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x02);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, SET1_HL_CanSetBit1OfAddress_HL_NotSet)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SET_1_HL_);
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x00);
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x02);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, SET1_HL_CanSetBit1OfAddress_HL_Set)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SET_1_HL_);
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x02);
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x02);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}
// ################# SET2 #################
TEST_F(BitTests, SET2ACanSetBit2OfRegisterANotSet)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SET_2A);
	cpu.regs->A = 0x00;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x04);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, SET2ACanSetBit2OfRegisterANotSetDoesntEffectOtherBits)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SET_2A);
	cpu.regs->A = 0x80;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x84);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, SET2ACanSetBit2OfRegisterASet)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SET_2A);
	cpu.regs->A = 0x04;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x04);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, SET2_HL_CanSetBit2OfAddress_HL_NotSet)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SET_2_HL_);
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x00);
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x04);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, SET2_HL_CanSetBit2OfAddress_HL_Set)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SET_2_HL_);
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x04);
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x04);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}
// ################# SET3 #################
TEST_F(BitTests, SET3ACanSetBit3OfRegisterANotSet)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SET_3A);
	cpu.regs->A = 0x00;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x08);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, SET3ACanSetBit3OfRegisterANotSetDoesntEffectOtherBits)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SET_3A);
	cpu.regs->A = 0x80;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x88);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, SET3ACanSetBit3OfRegisterASet)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SET_3A);
	cpu.regs->A = 0x08;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x08);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, SET3_HL_CanSetBit3OfAddress_HL_NotSet)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SET_3_HL_);
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x00);
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x08);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, SET3_HL_CanSetBit3OfAddress_HL_Set)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SET_3_HL_);
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x08);
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x08);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}
// ################# SET4 #################
TEST_F(BitTests, SET4ACanSetBit4OfRegisterANotSet)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SET_4A);
	cpu.regs->A = 0x00;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x10);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, SET4ACanSetBit4OfRegisterANotSetDoesntEffectOtherBits)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SET_4A);
	cpu.regs->A = 0x08;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x18);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, SET4ACanSetBit4OfRegisterASet)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SET_4A);
	cpu.regs->A = 0x10;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x10);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, SET4_HL_CanSetBit4OfAddress_HL_NotSet)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SET_4_HL_);
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x00);
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x10);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, SET4_HL_CanSetBit4OfAddress_HL_Set)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SET_4_HL_);
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x10);
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x10);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}
// ################# SET5 #################
TEST_F(BitTests, SET5ACanSetBit5OfRegisterANotSet)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SET_5A);
	cpu.regs->A = 0x00;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x20);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, SET5ACanSetBit5OfRegisterANotSetDoesntEffectOtherBits)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SET_5A);
	cpu.regs->A = 0x08;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x28);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, SET5ACanSetBit5OfRegisterASet)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SET_5A);
	cpu.regs->A = 0x20;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x20);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, SET5_HL_CanSetBit5OfAddress_HL_NotSet)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SET_5_HL_);
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x00);
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x20);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, SET5_HL_CanSetBit5OfAddress_HL_Set)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SET_5_HL_);
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x20);
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x20);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}
// ################# SET6 #################
TEST_F(BitTests, SET6ACanSetBit6OfRegisterANotSet)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SET_6A);
	cpu.regs->A = 0x00;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x40);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, SET6ACanSetBit6OfRegisterANotSetDoesntEffectOtherBits)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SET_6A);
	cpu.regs->A = 0x08;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x48);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, SET6ACanSetBit6OfRegisterASet)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SET_6A);
	cpu.regs->A = 0x40;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x40);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, SET6_HL_CanSetBit6OfAddress_HL_NotSet)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SET_6_HL_);
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x00);
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x40);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, SET6_HL_CanSetBit6OfAddress_HL_Set)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SET_6_HL_);
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x40);
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x40);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// ################# SET7 #################
TEST_F(BitTests, SET7ACanSetBit7OfRegisterANotSet)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SET_7A);
	cpu.regs->A = 0x00;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x80);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, SET7ACanSetBit7OfRegisterANotSetDoesntEffectOtherBits)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SET_7A);
	cpu.regs->A = 0x08;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x88);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, SET7ACanSetBit7OfRegisterASet)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SET_7A);
	cpu.regs->A = 0x80;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x80);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, SET7_HL_CanSetBit7OfAddress_HL_NotSet)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SET_7_HL_);
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x00);
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x80);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(BitTests, SET7_HL_CanSetBit7OfAddress_HL_Set)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SET_7_HL_);
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x80);
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x80);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}
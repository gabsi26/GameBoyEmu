#include "pch.h"
#include "../GameBoyEmu/GZ80.h"
#include "../GameBoyEmu/memory.h"
using namespace GZ80;
class RotateAndShiftTests : public testing::Test
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

// ################## RLCA #####################
TEST_F(RotateAndShiftTests, RLCACanLeftRotateAccumulatorAndShift1IntoCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_RLCA);
	cpu.regs->A = 0x80;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 1;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x01);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(RotateAndShiftTests, RLCACanLeftRotateAccumulatorAndShift0IntoCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_RLCA);
	cpu.regs->A = 0x40;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 1;
	cpu.regs->half_carry = 1;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x80);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// ############ RLA ####################
TEST_F(RotateAndShiftTests, RLACanLeftRotateAccumulatorAndShift1IntoCarryAndGet1FromCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_RLA);
	cpu.regs->A = 0x80;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 1;
	cpu.regs->half_carry = 1;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x01);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(RotateAndShiftTests, RLACanLeftRotateAccumulatorAndShift1IntoCarryAndGet0FromCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_RLA);
	cpu.regs->A = 0x80;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 1;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(RotateAndShiftTests, RLACanLeftRotateAccumulatorAndShift0IntoCarryAndGet1FromCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_RLA);
	cpu.regs->A = 0x00;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 1;
	cpu.regs->half_carry = 1;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x01);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// ################## RRCA #####################
TEST_F(RotateAndShiftTests, RRCACanRightRotateAccumulatorAndShift1IntoCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_RRCA);
	cpu.regs->A = 0x01;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 1;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x80);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(RotateAndShiftTests, RRCACanRightRotateAccumulatorAndShift0IntoCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_RRCA);
	cpu.regs->A = 0x40;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 1;
	cpu.regs->half_carry = 1;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x20);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// ############ RRA ####################
TEST_F(RotateAndShiftTests, RRACanRightRotateAccumulatorAndShift1IntoCarryAndGet1FromCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_RRA);
	cpu.regs->A = 0x01;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 1;
	cpu.regs->half_carry = 1;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x80);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(RotateAndShiftTests, RRACanRightRotateAccumulatorAndShift1IntoCarryAndGet0FromCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_RRA);
	cpu.regs->A = 0x01;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 1;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(RotateAndShiftTests, RRACanRightRotateAccumulatorAndShift0IntoCarryAndGet1FromCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_RRA);
	cpu.regs->A = 0x00;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 1;
	cpu.regs->half_carry = 1;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x80);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// ################## RLC #####################
TEST_F(RotateAndShiftTests, RLCCanLeftRotateAccumulatorAndShift1IntoCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RLC_A);
	cpu.regs->A = 0x80;
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
	EXPECT_EQ(cpu.regs->A, 0x01);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(RotateAndShiftTests, RLCCanLeftRotateValueAtAddress_HL_AndShift1IntoCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RLC_HL_);
	cpu.regs->HL = 0x200;
	cpu.mem->write_to_address(0x200, 0x80);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 1;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x01);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(RotateAndShiftTests, RLCCanLeftRotateValueIAtAddress_HL_AndShift0IntoCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RLC_HL_);
	cpu.regs->HL = 0x200;
	cpu.mem->write_to_address(0x200, 0x40);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 1;
	cpu.regs->half_carry = 1;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x80);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// ################## RL #####################
TEST_F(RotateAndShiftTests, RL_ACanLeftRotateAccumulatorAndShift1IntoCarryAndGet1FromCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RL_A);
	cpu.regs->A = 0x80;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 1;
	cpu.regs->half_carry = 1;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x01);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}
TEST_F(RotateAndShiftTests, RLCanLeftRotateValueAtAddress_HL_AndShift1IntoCarryAndGet1FromCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RL_HL_);
	cpu.regs->HL = 0x200;
	cpu.mem->write_to_address(0x200, 0x80);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 1;
	cpu.regs->half_carry = 1;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x01);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(RotateAndShiftTests, RLCanLeftRotateValueAtAddress_HL_AndShift1IntoCarryAndGet0FromCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RL_HL_);
	cpu.regs->HL = 0x200;
	cpu.mem->write_to_address(0x200, 0x80);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 1;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(RotateAndShiftTests, RLCanLeftRotateValueAtAddress_HL_AndShift0IntoCarryAndGet1FromCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RL_HL_);
	cpu.regs->HL = 0x200;
	cpu.mem->write_to_address(0x200, 0x00);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 1;
	cpu.regs->half_carry = 1;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x01);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// ################## RRC #####################
TEST_F(RotateAndShiftTests, RRCCanRightRotateAccumulatorAndShift1IntoCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RRC_A);
	cpu.regs->A = 0x01;
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
	EXPECT_EQ(cpu.regs->A, 0x80);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(RotateAndShiftTests, RRCCanRightRotateValueAtAddress_HL_AndShift1IntoCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RRC_HL_);
	cpu.regs->HL = 0x200;
	cpu.mem->write_to_address(0x200, 0x01);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 1;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x80);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(RotateAndShiftTests, RRCCanRightRotateValueIAtAddress_HL_AndShift0IntoCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RRC_HL_);
	cpu.regs->HL = 0x200;
	cpu.mem->write_to_address(0x200, 0x40);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 1;
	cpu.regs->half_carry = 1;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x20);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// ################## RR #####################
TEST_F(RotateAndShiftTests, RR_ACanRightRotateAccumulatorAndShift1IntoCarryAndGet1FromCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RR_A);
	cpu.regs->A = 0x01;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 1;
	cpu.regs->half_carry = 1;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x80);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}
TEST_F(RotateAndShiftTests, RRCanRightRotateValueAtAddress_HL_AndShift1IntoCarryAndGet1FromCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RR_HL_);
	cpu.regs->HL = 0x200;
	cpu.mem->write_to_address(0x200, 0x01);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 1;
	cpu.regs->half_carry = 1;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x80);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(RotateAndShiftTests, RRCanRightRotateValueAtAddress_HL_AndShift1IntoCarryAndGet0FromCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RR_HL_);
	cpu.regs->HL = 0x200;
	cpu.mem->write_to_address(0x200, 0x01);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 1;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(RotateAndShiftTests, RRCanLeftRotateValueAtAddress_HL_AndShift0IntoCarryAndGet1FromCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_RR_HL_);
	cpu.regs->HL = 0x200;
	cpu.mem->write_to_address(0x200, 0x00);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 1;
	cpu.regs->half_carry = 1;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x80);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// ################## SLA #####################
TEST_F(RotateAndShiftTests, SLACanLeftShiftAccumulatorAndShift1IntoCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SLA_A);
	cpu.regs->A = 0x80;
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
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(RotateAndShiftTests, SLACanLeftShiftValueAtAddress_HL_AndShift1IntoCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SLA_HL_);
	cpu.regs->HL = 0x200;
	cpu.mem->write_to_address(0x200, 0x80);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 1;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(RotateAndShiftTests, SLACanLeftShiftValueIAtAddress_HL_AndShift0IntoCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SLA_HL_);
	cpu.regs->HL = 0x200;
	cpu.mem->write_to_address(0x200, 0x40);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 1;
	cpu.regs->half_carry = 1;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x80);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// ################ SRA #################
TEST_F(RotateAndShiftTests, SRACCanRightShiftAccumulatorAndShift1IntoCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SRA_A);
	cpu.regs->A = 0x01;
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
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(RotateAndShiftTests, SRACCanRightShiftAccumulatorAndShift1IntoCarryAndKeepsBit7)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SRA_A);
	cpu.regs->A = 0x81;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 1;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0xC0);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(RotateAndShiftTests, SRACCanRightShiftValueAtAddress_HL_AndShift1IntoCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SRA_HL_);
	cpu.regs->HL = 0x200;
	cpu.mem->write_to_address(0x200, 0x01);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 1;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(RotateAndShiftTests, SRACanRightShiftValueIAtAddress_HL_AndShift0IntoCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SRA_HL_);
	cpu.regs->HL = 0x200;
	cpu.mem->write_to_address(0x200, 0x40);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 1;
	cpu.regs->half_carry = 1;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x20);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// ################ SRL #################
TEST_F(RotateAndShiftTests, SRLCCanRightShiftAccumulatorAndShift1IntoCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SRL_A);
	cpu.regs->A = 0x01;
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
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(RotateAndShiftTests, SRLCCanRightShiftAccumulatorAndShift1IntoCarryAndPuts0IntoBit7)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SRL_A);
	cpu.regs->A = 0x81;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 1;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x40);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(RotateAndShiftTests, SRLCCanRightShiftValueAtAddress_HL_AndShift1IntoCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SRL_HL_);
	cpu.regs->HL = 0x200;
	cpu.mem->write_to_address(0x200, 0x01);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 1;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(RotateAndShiftTests, SRLCanRightShiftValueIAtAddress_HL_AndShift0IntoCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::CB_INS);
	cpu.mem->write_to_address(0x101, CPU::INS_SRL_HL_);
	cpu.regs->HL = 0x200;
	cpu.mem->write_to_address(0x200, 0x40);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 1;
	cpu.regs->half_carry = 1;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x20);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}
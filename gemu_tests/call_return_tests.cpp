#include "pch.h"
#include "../GameBoyEmu/GZ80.h"
#include "../GameBoyEmu/memory.h"
using namespace GZ80;
class CallAndReturnTests : public testing::Test
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

// ################## Calls #####################
// CALL
TEST_F(CallAndReturnTests, CALLCanCallToImmediateAddressAndSetSPCorrectly)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_CALL);
	cpu.mem->write_to_address(0x101, 0x00);
	cpu.mem->write_to_address(0x102, 0x02);
	cpu.regs->pc = 0x100;
	cpu.regs->sp = 0xFFFE;
	Byte expected_machine_cycles = 6;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x200 + 1);
	EXPECT_EQ(cpu.regs->sp, 0xFFFC);
	EXPECT_EQ(cpu.mem->read_from_address(0xFFFE), 0x03);
	EXPECT_EQ(cpu.mem->read_from_address(0xFFFD), 0x01);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// CALL not Zero
TEST_F(CallAndReturnTests, CALLNonZeroCallsToImmediateAddressIfZeroFlagIsReset)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_CALL_NZ);
	cpu.mem->write_to_address(0x101, 0x00);
	cpu.mem->write_to_address(0x102, 0x02);
	cpu.regs->pc = 0x100;
	cpu.regs->sp = 0xFFFE;
	cpu.regs->zero = 0;
	Byte expected_machine_cycles = 6;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x200 + 1);
	EXPECT_EQ(cpu.regs->sp, 0xFFFC);
	EXPECT_EQ(cpu.mem->read_from_address(0xFFFE), 0x03);
	EXPECT_EQ(cpu.mem->read_from_address(0xFFFD), 0x01);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(CallAndReturnTests, CALLNonZeroDoesntCallToImmediateAddressIfZeroFlagIsSet)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_CALL_NZ);
	cpu.mem->write_to_address(0x101, 0x00);
	cpu.mem->write_to_address(0x102, 0x02);
	cpu.regs->pc = 0x100;
	cpu.regs->sp = 0xFFFE;
	cpu.regs->zero = 1;
	Byte expected_machine_cycles = 3;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x103 + 1);
	EXPECT_EQ(cpu.regs->sp, 0xFFFE);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// CALL Zero
TEST_F(CallAndReturnTests, CALLZeroCallsToImmediateAddressIfZeroFlagIsSet)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_CALL_Z);
	cpu.mem->write_to_address(0x101, 0x00);
	cpu.mem->write_to_address(0x102, 0x02);
	cpu.regs->pc = 0x100;
	cpu.regs->sp = 0xFFFE;
	cpu.regs->zero = 1;
	Byte expected_machine_cycles = 6;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x200 + 1);
	EXPECT_EQ(cpu.regs->sp, 0xFFFC);
	EXPECT_EQ(cpu.mem->read_from_address(0xFFFE), 0x03);
	EXPECT_EQ(cpu.mem->read_from_address(0xFFFD), 0x01);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(CallAndReturnTests, CALLZeroDoesntCallToImmediateAddressIfZeroFlagIsReset)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_CALL_Z);
	cpu.mem->write_to_address(0x101, 0x00);
	cpu.mem->write_to_address(0x102, 0x02);
	cpu.regs->pc = 0x100;
	cpu.regs->sp = 0xFFFE;
	cpu.regs->zero = 0;
	Byte expected_machine_cycles = 3;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x103 + 1);
	EXPECT_EQ(cpu.regs->sp, 0xFFFE);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// CALL not Carry
TEST_F(CallAndReturnTests, CALLNonCarryCallsToImmediateAddressIfCarryFlagIsReset)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_CALL_NC);
	cpu.mem->write_to_address(0x101, 0x00);
	cpu.mem->write_to_address(0x102, 0x02);
	cpu.regs->pc = 0x100;
	cpu.regs->sp = 0xFFFE;
	cpu.regs->carry = 0;
	Byte expected_machine_cycles = 6;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x200 + 1);
	EXPECT_EQ(cpu.regs->sp, 0xFFFC);
	EXPECT_EQ(cpu.mem->read_from_address(0xFFFE), 0x03);
	EXPECT_EQ(cpu.mem->read_from_address(0xFFFD), 0x01);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(CallAndReturnTests, CALLNonCarryDoesntCallToImmediateAddressIfCarryFlagIsSet)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_CALL_NC);
	cpu.mem->write_to_address(0x101, 0x00);
	cpu.mem->write_to_address(0x102, 0x02);
	cpu.regs->pc = 0x100;
	cpu.regs->sp = 0xFFFE;
	cpu.regs->carry = 1;
	Byte expected_machine_cycles = 3;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x103 + 1);
	EXPECT_EQ(cpu.regs->sp, 0xFFFE);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// CALL Carry
TEST_F(CallAndReturnTests, CALLCarryCallsToImmediateAddressIfCarryFlagIsSet)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_CALL_C);
	cpu.mem->write_to_address(0x101, 0x00);
	cpu.mem->write_to_address(0x102, 0x02);
	cpu.regs->pc = 0x100;
	cpu.regs->sp = 0xFFFE;
	cpu.regs->carry = 1;
	Byte expected_machine_cycles = 6;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x200 + 1);
	EXPECT_EQ(cpu.regs->sp, 0xFFFC);
	EXPECT_EQ(cpu.mem->read_from_address(0xFFFE), 0x03);
	EXPECT_EQ(cpu.mem->read_from_address(0xFFFD), 0x01);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(CallAndReturnTests, CALLCarryDoesntCallToImmediateAddressIfCarryFlagIsReset)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_CALL_C);
	cpu.mem->write_to_address(0x101, 0x00);
	cpu.mem->write_to_address(0x102, 0x02);
	cpu.regs->pc = 0x100;
	cpu.regs->sp = 0xFFFE;
	cpu.regs->carry = 0;
	Byte expected_machine_cycles = 3;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x103 + 1);
	EXPECT_EQ(cpu.regs->sp, 0xFFFE);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// ################## Returns ######################
TEST_F(CallAndReturnTests, RETReturnsFromCall)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_CALL);
	cpu.mem->write_to_address(0x101, 0x00);
	cpu.mem->write_to_address(0x102, 0x02);
	cpu.regs->A = 0xEE;
	cpu.regs->HL = 0x0300;
	cpu.mem->write_to_address(0x200, CPU::INS_LD_HLA);
	cpu.mem->write_to_address(0x201, CPU::INS_RET);
	cpu.regs->pc = 0x100;
	cpu.regs->sp = 0xFFFE;
	Byte expected_machine_cycles = 6 + 2 + 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x103 + 1);
	EXPECT_EQ(cpu.regs->sp, 0xFFFE);
	EXPECT_EQ(cpu.mem->read_from_address(0xFFFE), 0x03);
	EXPECT_EQ(cpu.mem->read_from_address(0xFFFD), 0x01);
	EXPECT_EQ(cpu.mem->read_from_address(0x0300), 0xEE);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// RET not Zero
TEST_F(CallAndReturnTests, RET_NZReturnsFromCallIfZeroFlagIsReset)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_CALL);
	cpu.mem->write_to_address(0x101, 0x00);
	cpu.mem->write_to_address(0x102, 0x02);
	cpu.regs->zero = 0;
	cpu.regs->A = 0xEE;
	cpu.regs->HL = 0x0300;
	cpu.mem->write_to_address(0x200, CPU::INS_LD_HLA);
	cpu.mem->write_to_address(0x201, CPU::INS_RET_NZ);
	cpu.regs->pc = 0x100;
	cpu.regs->sp = 0xFFFE;
	Byte expected_machine_cycles = 6 + 2 + 5;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x103 + 1);
	EXPECT_EQ(cpu.regs->sp, 0xFFFE);
	EXPECT_EQ(cpu.mem->read_from_address(0xFFFE), 0x03);
	EXPECT_EQ(cpu.mem->read_from_address(0xFFFD), 0x01);
	EXPECT_EQ(cpu.mem->read_from_address(0x0300), 0xEE);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(CallAndReturnTests, RET_NZDoesntReturnFromCallIfZeroFlagIsSet)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_CALL);
	cpu.mem->write_to_address(0x101, 0x00);
	cpu.mem->write_to_address(0x102, 0x02);
	cpu.regs->zero = 1;
	cpu.regs->A = 0xEE;
	cpu.regs->HL = 0x0300;
	cpu.mem->write_to_address(0x200, CPU::INS_LD_HLA);
	cpu.mem->write_to_address(0x201, CPU::INS_RET_NZ);
	cpu.regs->pc = 0x100;
	cpu.regs->sp = 0xFFFE;
	Byte expected_machine_cycles = 6 + 2 + 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x202 + 1);
	EXPECT_EQ(cpu.regs->sp, 0xFFFC);
	EXPECT_EQ(cpu.mem->read_from_address(0xFFFE), 0x03);
	EXPECT_EQ(cpu.mem->read_from_address(0xFFFD), 0x01);
	EXPECT_EQ(cpu.mem->read_from_address(0x0300), 0xEE);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// RET Zero
TEST_F(CallAndReturnTests, RET_ZReturnsFromCallIfZeroFlagIsSet)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_CALL);
	cpu.mem->write_to_address(0x101, 0x00);
	cpu.mem->write_to_address(0x102, 0x02);
	cpu.regs->zero = 1;
	cpu.regs->A = 0xEE;
	cpu.regs->HL = 0x0300;
	cpu.mem->write_to_address(0x200, CPU::INS_LD_HLA);
	cpu.mem->write_to_address(0x201, CPU::INS_RET_Z);
	cpu.regs->pc = 0x100;
	cpu.regs->sp = 0xFFFE;
	Byte expected_machine_cycles = 6 + 2 + 5;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x103 + 1);
	EXPECT_EQ(cpu.regs->sp, 0xFFFE);
	EXPECT_EQ(cpu.mem->read_from_address(0xFFFE), 0x03);
	EXPECT_EQ(cpu.mem->read_from_address(0xFFFD), 0x01);
	EXPECT_EQ(cpu.mem->read_from_address(0x0300), 0xEE);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(CallAndReturnTests, RET_ZDoesntReturnFromCallIfZeroFlagIsReset)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_CALL);
	cpu.mem->write_to_address(0x101, 0x00);
	cpu.mem->write_to_address(0x102, 0x02);
	cpu.regs->zero = 0;
	cpu.regs->A = 0xEE;
	cpu.regs->HL = 0x0300;
	cpu.mem->write_to_address(0x200, CPU::INS_LD_HLA);
	cpu.mem->write_to_address(0x201, CPU::INS_RET_Z);
	cpu.regs->pc = 0x100;
	cpu.regs->sp = 0xFFFE;
	Byte expected_machine_cycles = 6 + 2 + 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x202 + 1);
	EXPECT_EQ(cpu.regs->sp, 0xFFFC);
	EXPECT_EQ(cpu.mem->read_from_address(0xFFFE), 0x03);
	EXPECT_EQ(cpu.mem->read_from_address(0xFFFD), 0x01);
	EXPECT_EQ(cpu.mem->read_from_address(0x0300), 0xEE);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// RET not Carry
TEST_F(CallAndReturnTests, RET_NCReturnsFromCallIfCarryFlagIsReset)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_CALL);
	cpu.mem->write_to_address(0x101, 0x00);
	cpu.mem->write_to_address(0x102, 0x02);
	cpu.regs->carry = 0;
	cpu.regs->A = 0xEE;
	cpu.regs->HL = 0x0300;
	cpu.mem->write_to_address(0x200, CPU::INS_LD_HLA);
	cpu.mem->write_to_address(0x201, CPU::INS_RET_NC);
	cpu.regs->pc = 0x100;
	cpu.regs->sp = 0xFFFE;
	Byte expected_machine_cycles = 6 + 2 + 5;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x103 + 1);
	EXPECT_EQ(cpu.regs->sp, 0xFFFE);
	EXPECT_EQ(cpu.mem->read_from_address(0xFFFE), 0x03);
	EXPECT_EQ(cpu.mem->read_from_address(0xFFFD), 0x01);
	EXPECT_EQ(cpu.mem->read_from_address(0x0300), 0xEE);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(CallAndReturnTests, RET_NCDoesntReturnFromCallIfCarryFlagIsSet)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_CALL);
	cpu.mem->write_to_address(0x101, 0x00);
	cpu.mem->write_to_address(0x102, 0x02);
	cpu.regs->carry = 1;
	cpu.regs->A = 0xEE;
	cpu.regs->HL = 0x0300;
	cpu.mem->write_to_address(0x200, CPU::INS_LD_HLA);
	cpu.mem->write_to_address(0x201, CPU::INS_RET_NC);
	cpu.regs->pc = 0x100;
	cpu.regs->sp = 0xFFFE;
	Byte expected_machine_cycles = 6 + 2 + 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x202 + 1);
	EXPECT_EQ(cpu.regs->sp, 0xFFFC);
	EXPECT_EQ(cpu.mem->read_from_address(0xFFFE), 0x03);
	EXPECT_EQ(cpu.mem->read_from_address(0xFFFD), 0x01);
	EXPECT_EQ(cpu.mem->read_from_address(0x0300), 0xEE);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// RET Carry
TEST_F(CallAndReturnTests, RET_CReturnsFromCallIfCarryFlagIsSet)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_CALL);
	cpu.mem->write_to_address(0x101, 0x00);
	cpu.mem->write_to_address(0x102, 0x02);
	cpu.regs->carry = 1;
	cpu.regs->A = 0xEE;
	cpu.regs->HL = 0x0300;
	cpu.mem->write_to_address(0x200, CPU::INS_LD_HLA);
	cpu.mem->write_to_address(0x201, CPU::INS_RET_C);
	cpu.regs->pc = 0x100;
	cpu.regs->sp = 0xFFFE;
	Byte expected_machine_cycles = 6 + 2 + 5;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x103 + 1);
	EXPECT_EQ(cpu.regs->sp, 0xFFFE);
	EXPECT_EQ(cpu.mem->read_from_address(0xFFFE), 0x03);
	EXPECT_EQ(cpu.mem->read_from_address(0xFFFD), 0x01);
	EXPECT_EQ(cpu.mem->read_from_address(0x0300), 0xEE);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(CallAndReturnTests, RET_CDoesntReturnFromCallIfCarryFlagIsReset)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_CALL);
	cpu.mem->write_to_address(0x101, 0x00);
	cpu.mem->write_to_address(0x102, 0x02);
	cpu.regs->carry = 0;
	cpu.regs->A = 0xEE;
	cpu.regs->HL = 0x0300;
	cpu.mem->write_to_address(0x200, CPU::INS_LD_HLA);
	cpu.mem->write_to_address(0x201, CPU::INS_RET_C);
	cpu.regs->pc = 0x100;
	cpu.regs->sp = 0xFFFE;
	Byte expected_machine_cycles = 6 + 2 + 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x202 + 1);
	EXPECT_EQ(cpu.regs->sp, 0xFFFC);
	EXPECT_EQ(cpu.mem->read_from_address(0xFFFE), 0x03);
	EXPECT_EQ(cpu.mem->read_from_address(0xFFFD), 0x01);
	EXPECT_EQ(cpu.mem->read_from_address(0x0300), 0xEE);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}
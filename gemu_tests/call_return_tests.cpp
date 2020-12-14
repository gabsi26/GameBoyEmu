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
	void call_tests(Byte instruction, bool use_zero, bool use_carry, bool zero, bool carry, bool zero_wanted, bool carry_wanted, Byte expected_cycles);
	void return_tests(Byte iknstruction, bool use_zero, bool use_carry, bool zero, bool carry, bool zero_wanted, bool carry_wanted, Byte expected_cycles);
};

void CallAndReturnTests::call_tests(Byte instruction, bool use_zero, bool use_carry, bool zero, bool carry, bool zero_wanted, bool carry_wanted, Byte expected_cycles)
{
	cpu.mem->write_to_address(0x100, instruction);
	cpu.mem->write_to_address(0x101, 0x00);
	cpu.mem->write_to_address(0x102, 0x02);
	cpu.regs->pc = 0x100;
	cpu.regs->sp = 0xFFFE;
	if (use_zero)
	{
		cpu.regs->zero = zero;
	}
	else if (use_carry)
	{
		cpu.regs->carry = carry;
	}
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_cycles);
	// then
	if((use_carry && cpu.regs->carry == carry_wanted) || (use_zero && cpu.regs->zero == zero_wanted) || (!use_carry && !use_zero))
	{
		EXPECT_EQ(cpu.regs->pc, 0x200 + 1);
		EXPECT_EQ(cpu.regs->sp, 0xFFFC);
		EXPECT_EQ(cpu.mem->read_from_address(0xFFFE), 0x03);
		EXPECT_EQ(cpu.mem->read_from_address(0xFFFD), 0x01);
	}
	else
	{
		EXPECT_EQ(cpu.regs->pc, 0x103 + 1);
		EXPECT_EQ(cpu.regs->sp, 0xFFFE);
	}
	EXPECT_EQ(cpu.cycles->mc, expected_cycles);
}

void CallAndReturnTests::return_tests(Byte instruction, bool use_zero, bool use_carry, bool zero, bool carry, bool zero_wanted, bool carry_wanted, Byte expected_cycles)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_CALL);
	cpu.mem->write_to_address(0x101, 0x00);
	cpu.mem->write_to_address(0x102, 0x02);
	cpu.regs->A = 0xEE;
	cpu.regs->HL = 0x0300;
	cpu.mem->write_to_address(0x200, CPU::INS_LD_HLA);
	cpu.mem->write_to_address(0x201, instruction);
	cpu.regs->pc = 0x100;
	cpu.regs->sp = 0xFFFE;
	if (use_zero)
	{
		cpu.regs->zero = zero;
	}
	else if (use_carry)
	{
		cpu.regs->carry = carry;
	}
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_cycles);
	// then
	if ((use_carry && cpu.regs->carry == carry_wanted) || (use_zero && cpu.regs->zero == zero_wanted) || (!use_carry && !use_zero))
	{
		EXPECT_EQ(cpu.regs->pc, 0x103 + 1);
		EXPECT_EQ(cpu.regs->sp, 0xFFFE);
	}
	else
	{
		EXPECT_EQ(cpu.regs->pc, 0x202 + 1);
		EXPECT_EQ(cpu.regs->sp, 0xFFFC);
	}

	EXPECT_EQ(cpu.mem->read_from_address(0xFFFE), 0x03);
	EXPECT_EQ(cpu.mem->read_from_address(0xFFFD), 0x01);
	EXPECT_EQ(cpu.mem->read_from_address(0x0300), 0xEE);
	EXPECT_EQ(cpu.cycles->mc, expected_cycles);
}

// ################## Calls #####################
// CALL
TEST_F(CallAndReturnTests, CALLCanCallToImmediateAddressAndSetSPCorrectly)
{
	call_tests(CPU::INS_CALL, 0, 0, 0, 0, 0, 0, 6);
}

// CALL not Zero
TEST_F(CallAndReturnTests, CALLNonZeroCallsToImmediateAddressIfZeroFlagIsReset)
{
	call_tests(CPU::INS_CALL_NZ, 1, 0, 0, 0, 0, 0, 6);
}

TEST_F(CallAndReturnTests, CALLNonZeroDoesntCallToImmediateAddressIfZeroFlagIsSet)
{
	call_tests(CPU::INS_CALL_NZ, 1, 0, 1, 0, 0, 0, 3);
}

// CALL Zero
TEST_F(CallAndReturnTests, CALLZeroCallsToImmediateAddressIfZeroFlagIsSet)
{
	call_tests(CPU::INS_CALL_Z, 1, 0, 1, 0, 1, 0, 6);
}

TEST_F(CallAndReturnTests, CALLZeroDoesntCallToImmediateAddressIfZeroFlagIsReset)
{
	call_tests(CPU::INS_CALL_Z, 1, 0, 0, 0, 1, 0, 3);
}

// CALL not Carry
TEST_F(CallAndReturnTests, CALLNonCarryCallsToImmediateAddressIfCarryFlagIsReset)
{
	call_tests(CPU::INS_CALL_NC, 0, 1, 0, 0, 0, 0, 6);
}

TEST_F(CallAndReturnTests, CALLNonCarryDoesntCallToImmediateAddressIfCarryFlagIsSet)
{
	call_tests(CPU::INS_CALL_NC, 0, 1, 0, 1, 0, 0, 3);
}

// CALL Carry
TEST_F(CallAndReturnTests, CALLCarryCallsToImmediateAddressIfCarryFlagIsSet)
{
	call_tests(CPU::INS_CALL_C, 0, 1, 0, 1, 0, 1, 6);
}

TEST_F(CallAndReturnTests, CALLCarryDoesntCallToImmediateAddressIfCarryFlagIsReset)
{
	call_tests(CPU::INS_CALL_C, 0, 1, 0, 0, 0, 1, 3);
}

// ################## Returns ######################
TEST_F(CallAndReturnTests, RETReturnsFromCall)
{
	return_tests(CPU::INS_RET, 0, 0, 0, 0, 0, 0, 6 + 2 + 4);
}

// RET not Zero
TEST_F(CallAndReturnTests, RET_NZReturnsFromCallIfZeroFlagIsReset)
{
	return_tests(CPU::INS_RET_NZ, 1, 0, 0, 0, 0, 0, 6 + 2 + 5);
}

TEST_F(CallAndReturnTests, RET_NZDoesntReturnFromCallIfZeroFlagIsSet)
{
	return_tests(CPU::INS_RET_NZ, 1, 0, 1, 0, 0, 0, 6 + 2 + 2);
}

// RET Zero
TEST_F(CallAndReturnTests, RET_ZReturnsFromCallIfZeroFlagIsSet)
{
	return_tests(CPU::INS_RET_Z, 1, 0, 1, 0, 1, 0, 6 + 2 + 5);
}

TEST_F(CallAndReturnTests, RET_ZDoesntReturnFromCallIfZeroFlagIsReset)
{
	return_tests(CPU::INS_RET_Z, 1, 0, 0, 0, 1, 0, 6 + 2 + 2);
}

// RET not Carry
TEST_F(CallAndReturnTests, RET_NCReturnsFromCallIfCarryFlagIsReset)
{
	return_tests(CPU::INS_RET_NC, 0, 1, 0, 0, 0, 0, 6 + 2 + 5);
}

TEST_F(CallAndReturnTests, RET_NCDoesntReturnFromCallIfCarryFlagIsSet)
{
	return_tests(CPU::INS_RET_NC, 0, 1, 0, 1, 0, 0, 6 + 2 + 2);
}

// RET Carry
TEST_F(CallAndReturnTests, RET_CReturnsFromCallIfCarryFlagIsSet)
{
	return_tests(CPU::INS_RET_C, 0, 1, 0, 1, 0, 1, 6 + 2 + 5);
}

TEST_F(CallAndReturnTests, RET_CDoesntReturnFromCallIfCarryFlagIsReset)
{
	return_tests(CPU::INS_RET_C, 0, 1, 0, 0, 0, 1, 6 + 2 + 2);
}
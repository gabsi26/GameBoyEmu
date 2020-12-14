#include "pch.h"
#include "../GameBoyEmu/GZ80.h"
#include "../GameBoyEmu/memory.h"
using namespace GZ80;
class _8BitALUTests : public testing::Test
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

// ################## ADD #####################
TEST_F(_8BitALUTests, ADDAACanAddRegisterAToRegisterAWithoutCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_ADD_AA);
	cpu.regs->A = 0x01;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x02);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, ADDAACanAddRegisterAToRegisterAWithHalfCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_ADD_AA);
	cpu.regs->A = 0x08;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x10);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, ADDAACanAddRegisterAToRegisterAWithCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_ADD_AA);
	cpu.regs->A = 0xFF;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0xFE);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, ADDAACanAddRegisterAToRegisterAZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_ADD_AA);
	cpu.regs->A = 0x00;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, ADDABCanAddRegisterBToRegisterAWithoutCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_ADD_AB);
	cpu.regs->A = 0x01;
	cpu.regs->B = 0x01;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x02);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, ADDABCanAddRegisterBToRegisterAWithHalfCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_ADD_AB);
	cpu.regs->A = 0x08;
	cpu.regs->B = 0x08;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x10);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, ADDABCanAddRegisterBToRegisterAWithCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_ADD_AB);
	cpu.regs->A = 0xFF;
	cpu.regs->B = 0xFF;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0xFE);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, ADDABCanAddRegisterBToRegisterAZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_ADD_AB);
	cpu.regs->A = 0x00;
	cpu.regs->B = 0x00;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, ADDAHLCanAddAddress_HL_ToRegisterAWithoutCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_ADD_AHL);
	cpu.regs->A = 0x01;
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x01);
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
	EXPECT_EQ(cpu.regs->A, 0x02);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, ADDAHLCanAddAddress_HL_ToRegisterAWithHalfCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_ADD_AHL);
	cpu.regs->A = 0x08;
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x08);
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
	EXPECT_EQ(cpu.regs->A, 0x10);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, ADDAHLCanAddAddress_HL_ToRegisterAWithCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_ADD_AHL);
	cpu.regs->A = 0xFF;
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0xFF);
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
	EXPECT_EQ(cpu.regs->A, 0xFE);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, ADDAHLCanAddAddress_HL_ToRegisterAZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_ADD_AHL);
	cpu.regs->A = 0x00;
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x00);
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
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, ADDAIMCanAddImmediateValueToRegisterAWithoutCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_ADD_AIM);
	cpu.regs->A = 0x01;
	cpu.mem->write_to_address(0x101, 0x01);
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
	EXPECT_EQ(cpu.regs->A, 0x02);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, ADDAIMCanAddImmediateValueToRegisterAWithHalfCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_ADD_AIM);
	cpu.regs->A = 0x08;
	cpu.mem->write_to_address(0x101, 0x08);
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
	EXPECT_EQ(cpu.regs->A, 0x10);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, ADDAIMCanAddImmediatValueToRegisterAWithCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_ADD_AIM);
	cpu.regs->A = 0xFF;
	cpu.mem->write_to_address(0x101, 0xFF);
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
	EXPECT_EQ(cpu.regs->A, 0xFE);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, ADDAIMCanAddImmediateValueToRegisterAZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_ADD_AIM);
	cpu.regs->A = 0x00;
	cpu.mem->write_to_address(0x101, 0x00);
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
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// ##################### ADC #######################
TEST_F(_8BitALUTests, ADCAACanAddRegisterAToRegisterAWithoutCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_ADC_AA);
	cpu.regs->A = 0x01;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x02);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, ADCAACanAddRegisterAPlusCarryToRegisterAWithoutCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_ADC_AA);
	cpu.regs->A = 0x01;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 1;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x03);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, ADCAACanAddRegisterAToRegisterAWithHalfCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_ADC_AA);
	cpu.regs->A = 0x08;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x10);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, ADCAACanAddRegisterAToRegisterAWithCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_ADC_AA);
	cpu.regs->A = 0xFF;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0xFE);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, ADCAACanAddRegisterAToRegisterAZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_ADC_AA);
	cpu.regs->A = 0x00;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, ADCAACanAddRegisterAPlusToRegisterANonZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_ADC_AA);
	cpu.regs->A = 0x00;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 1;
	cpu.regs->half_carry = 0;
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

TEST_F(_8BitALUTests, ADCABCanAddRegisterBToRegisterAWithoutCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_ADC_AB);
	cpu.regs->A = 0x01;
	cpu.regs->B = 0x01;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x02);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, ADCABCanAddRegisterBPlusCarryToRegisterAWithoutCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_ADC_AB);
	cpu.regs->A = 0x01;
	cpu.regs->B = 0x01;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 1;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x03);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, ADCABCanAddRegisterBToRegisterAWithHalfCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_ADC_AB);
	cpu.regs->A = 0x08;
	cpu.regs->B = 0x08;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x10);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, ADCABCanAddRegisterBPlusCarryToRegisterAWithHalfCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_ADC_AB);
	cpu.regs->A = 0x08;
	cpu.regs->B = 0x07;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 1;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x10);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, ADCABCanAddRegisterBToRegisterAWithCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_ADC_AB);
	cpu.regs->A = 0xFF;
	cpu.regs->B = 0xFF;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0xFE);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, ADCABCanAddRegisterBPlusCarryToRegisterAWithCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_ADC_AB);
	cpu.regs->A = 0xFF;
	cpu.regs->B = 0x00;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	cpu.regs->negative = 1;
	cpu.regs->carry = 1;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, ADCABCanAddRegisterBToRegisterAZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_ADC_AB);
	cpu.regs->A = 0x00;
	cpu.regs->B = 0x00;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, ADCABCanAddRegisterBPlusCarryToRegisterANonZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_ADC_AB);
	cpu.regs->A = 0x00;
	cpu.regs->B = 0x00;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 1;
	cpu.regs->half_carry = 0;
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

TEST_F(_8BitALUTests, ADCAHLCanAddAddress_HL_ToRegisterAWithoutCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_ADC_AHL);
	cpu.regs->A = 0x01;
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x01);
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
	EXPECT_EQ(cpu.regs->A, 0x02);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, ADCAHLCanAddAddress_HL_ToRegisterAWithHalfCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_ADC_AHL);
	cpu.regs->A = 0x08;
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x08);
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
	EXPECT_EQ(cpu.regs->A, 0x10);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, ADCAHLCanAddAddress_HL_ToRegisterAWithCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_ADC_AHL);
	cpu.regs->A = 0xFF;
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0xFF);
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
	EXPECT_EQ(cpu.regs->A, 0xFE);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, ADCAHLCanAddAddress_HL_ToRegisterAZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_ADC_AHL);
	cpu.regs->A = 0x00;
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x00);
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
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, ADCAIMCanAddImmediateValueToRegisterAWithoutCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_ADC_AIM);
	cpu.regs->A = 0x01;
	cpu.mem->write_to_address(0x101, 0x01);
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
	EXPECT_EQ(cpu.regs->A, 0x02);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, ADCAIMCanAddImmediateValueToRegisterAWithHalfCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_ADC_AIM);
	cpu.regs->A = 0x08;
	cpu.mem->write_to_address(0x101, 0x08);
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
	EXPECT_EQ(cpu.regs->A, 0x10);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, ADCAIMCanAddImmediatValueToRegisterAWithCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_ADC_AIM);
	cpu.regs->A = 0xFF;
	cpu.mem->write_to_address(0x101, 0xFF);
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
	EXPECT_EQ(cpu.regs->A, 0xFE);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, ADCAIMCanAddImmediateValueToRegisterAZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_ADC_AIM);
	cpu.regs->A = 0x00;
	cpu.mem->write_to_address(0x101, 0x00);
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
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// ############## SUB ##################
TEST_F(_8BitALUTests, SUBAACanSubtractRegisterAFromRegisterAWithCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_SUB_AA);
	cpu.regs->A = 0x01;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	cpu.regs->negative = 0;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_TRUE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, SUBABCanSubtractRegisterBFromRegisterAWithCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_SUB_AB);
	cpu.regs->A = 0x01;
	cpu.regs->B = 0x01;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	cpu.regs->negative = 0;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_TRUE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, SUBABCanSubtractRegisterBFromRegisterAWithHalfCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_SUB_AB);
	cpu.regs->A = 0x40;
	cpu.regs->B = 0x04;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 0;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x3C);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_TRUE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, SUBABCanSubtractRegisterBFromRegisterAWithoutCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_SUB_AB);
	cpu.regs->A = 0x00;
	cpu.regs->B = 0x01;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 0;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0xFF);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_TRUE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, SUBAHLCanSubtractAddress_HL_FromRegisterAWithCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_SUB_AHL);
	cpu.regs->A = 0x01;
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x1);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	cpu.regs->negative = 0;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_TRUE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, SUBAHLCanSubtractAddress_HL_FromRegisterAWithHalfCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_SUB_AHL);
	cpu.regs->A = 0x40;
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x04);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 0;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x3C);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_TRUE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, SUBAHLCanSubtractAddress_HL_FromRegisterAWithoutCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_SUB_AHL);
	cpu.regs->A = 0x00;
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x01);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 0;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0xFF);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_TRUE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, SUBAIMCanSubtractImmediateValueFromRegisterAWithCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_SUB_AIM);
	cpu.regs->A = 0x01;
	cpu.mem->write_to_address(0x101, 0x1);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	cpu.regs->negative = 0;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_TRUE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, SUBAIMCanSubtractImmediateValueFromRegisterAWithHalfCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_SUB_AIM);
	cpu.regs->A = 0x40;
	cpu.mem->write_to_address(0x101, 0x04);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 0;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x3C);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_TRUE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, SUBAIMCanSubtractImmediateValueFromRegisterAWithoutCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_SUB_AIM);
	cpu.regs->A = 0x00;
	cpu.mem->write_to_address(0x101, 0x01);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 0;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0xFF);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_TRUE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// ############## SBC ##################
TEST_F(_8BitALUTests, SBCAACanSubtractRegisterAFromRegisterAWithCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_SBC_AA);
	cpu.regs->A = 0x01;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	cpu.regs->negative = 0;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_TRUE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, SBCAACanSubtractRegisterAPlusCarryFromRegisterAWithCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_SBC_AA);
	cpu.regs->A = 0x01;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	cpu.regs->negative = 0;
	cpu.regs->carry = 1;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0xFF);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_TRUE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, SBCABCanSubtractRegisterBFromRegisterAWithCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_SBC_AB);
	cpu.regs->A = 0x01;
	cpu.regs->B = 0x01;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	cpu.regs->negative = 0;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_TRUE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, SBCABCanSubtractRegisterBPlusCarryFromRegisterAWithCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_SBC_AB);
	cpu.regs->A = 0x01;
	cpu.regs->B = 0x01;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	cpu.regs->negative = 0;
	cpu.regs->carry = 1;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0xFF);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_TRUE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, SBCABCanSubtractRegisterBFromRegisterAWithHalfCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_SBC_AB);
	cpu.regs->A = 0x40;
	cpu.regs->B = 0x04;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 0;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x3C);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_TRUE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, SBCABCanSubtractRegisterBPlusCarryFromRegisterAWithHalfCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_SBC_AB);
	cpu.regs->A = 0x44;
	cpu.regs->B = 0x04;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 0;
	cpu.regs->carry = 1;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x3F);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_TRUE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, SBCABCanSubtractRegisterBFromRegisterAWithoutCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_SBC_AB);
	cpu.regs->A = 0x00;
	cpu.regs->B = 0x01;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 0;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0xFF);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_TRUE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, SBCAHLCanSubtractAddress_HL_FromRegisterAWithCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_SBC_AHL);
	cpu.regs->A = 0x01;
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x1);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	cpu.regs->negative = 0;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_TRUE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, SBCAHLCanSubtractAddress_HL_FromRegisterAWithHalfCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_SBC_AHL);
	cpu.regs->A = 0x40;
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x04);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 0;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x3C);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_TRUE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, SBCAHLCanSubtractAddress_HL_FromRegisterAWithoutCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_SBC_AHL);
	cpu.regs->A = 0x00;
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x01);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 0;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0xFF);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_TRUE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, SBCAIMCanSubtractImmediateValueFromRegisterAWithCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_SBC_AIM);
	cpu.regs->A = 0x01;
	cpu.mem->write_to_address(0x101, 0x1);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	cpu.regs->negative = 0;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_TRUE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, SBCAIMCanSubtractImmediateValueFromRegisterAWithHalfCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_SBC_AIM);
	cpu.regs->A = 0x40;
	cpu.mem->write_to_address(0x101, 0x04);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 0;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x3C);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_TRUE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, SBCAIMCanSubtractImmediateValueFromRegisterAWithoutCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_SBC_AIM);
	cpu.regs->A = 0x00;
	cpu.mem->write_to_address(0x101, 0x01);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 0;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0xFF);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_TRUE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// ################ AND #################
TEST_F(_8BitALUTests, ANDAACanAndRegisterAWithRegisterANonZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_AND_AA);
	cpu.regs->A = 0x01;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 1;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x01);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, ANDAACanAndRegisterAWithRegisterAZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_AND_AA);
	cpu.regs->A = 0x00;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	cpu.regs->negative = 1;
	cpu.regs->carry = 1;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, ANDABCanAndRegisterBWithRegisterANonZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_AND_AB);
	cpu.regs->A = 0x01;
	cpu.regs->B = 0x01;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 1;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x01);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, ANDABCanAndRegisterBWithRegisterAZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_AND_AB);
	cpu.regs->A = 0x01;
	cpu.regs->B = 0x10;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 1;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, ANDAHLCanAndRegisterHLWithRegisterANonZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_AND_AHL);
	cpu.regs->A = 0x01;
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x01);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 1;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x01);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, ANDAHLCanAndRegisterHLWithRegisterAZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_AND_AHL);
	cpu.regs->A = 0x01;
	cpu.regs->HL = 0x200;
	cpu.mem->write_to_address(0x200, 0x10);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 1;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, ANDAIMCanAndImmediateValueWithRegisterANonZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_AND_AIM);
	cpu.regs->A = 0x01;
	cpu.mem->write_to_address(0x101, 0x01);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 1;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x01);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, ANDAIMCanAndImmediateValueWithRegisterAZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_AND_AIM);
	cpu.regs->A = 0x01;
	cpu.mem->write_to_address(0x101, 0x10);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 1;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// ################ OR #####################
TEST_F(_8BitALUTests, ORAACanOrRegisterAWithRegisterANonZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_OR_AA);
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
	EXPECT_EQ(cpu.regs->A, 0x01);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, ORAACanOrRegisterAWithRegisterAZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_OR_AA);
	cpu.regs->A = 0x00;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	cpu.regs->negative = 1;
	cpu.regs->carry = 1;
	cpu.regs->half_carry = 1;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, ORABCanOrRegisterBWithRegisterANonZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_OR_AB);
	cpu.regs->A = 0x01;
	cpu.regs->B = 0x10;
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
	EXPECT_EQ(cpu.regs->A, 0x11);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, ORAHLCanOrRegisterHLWithRegisterANonZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_OR_AHL);
	cpu.regs->A = 0x01;
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x10);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 1;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x11);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, ORAIMCanOrImmediateValueWithRegisterANonZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_OR_AIM);
	cpu.regs->A = 0x01;
	cpu.mem->write_to_address(0x101, 0x10);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 1;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x11);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// ################ XOR #####################
TEST_F(_8BitALUTests, XORAACanXOrRegisterAWithRegisterAZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_XOR_AA);
	cpu.regs->A = 0x01;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	cpu.regs->negative = 1;
	cpu.regs->carry = 1;
	cpu.regs->half_carry = 1;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, XORABCanXOrRegisterBWithRegisterANonZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_XOR_AB);
	cpu.regs->A = 0x01;
	cpu.regs->B = 0x10;
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
	EXPECT_EQ(cpu.regs->A, 0x11);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, XORABCanXOrRegisterBWithRegisterAZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_XOR_AB);
	cpu.regs->A = 0x01;
	cpu.regs->B = 0x01;
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
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, XORAHLCanXOrRegisterHLWithRegisterANonZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_XOR_AHL);
	cpu.regs->A = 0x01;
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x10);
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
	EXPECT_EQ(cpu.regs->A, 0x11);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, XORAHLCanXOrRegisterHLWithRegisterAZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_XOR_AHL);
	cpu.regs->A = 0x01;
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x01);
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
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, XORAIMCanXOrImmediateValueWithRegisterANonZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_XOR_AIM);
	cpu.regs->A = 0x01;
	cpu.mem->write_to_address(0x101, 0x10);
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
	EXPECT_EQ(cpu.regs->A, 0x11);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, XORAIMCanXOrImmediateValueWithRegisterAZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_XOR_AIM);
	cpu.regs->A = 0x01;
	cpu.mem->write_to_address(0x101, 0x01);
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
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// ############### CP ##################
TEST_F(_8BitALUTests, CPAACanCompareRegisterAWithRegisterAWithCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_CP_AA);
	cpu.regs->A = 0x01;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	cpu.regs->negative = 0;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x01);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_TRUE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, CPABCanCompareRegisterBWithRegisterAWithCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_CP_AB);
	cpu.regs->A = 0x01;
	cpu.regs->B = 0x01;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	cpu.regs->negative = 0;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x01);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_TRUE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, CPABCanCompareRegisterBWithRegisterAWithHalfCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_CP_AB);
	cpu.regs->A = 0x40;
	cpu.regs->B = 0x04;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 0;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x40);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_TRUE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, CPABCanCompareRegisterBWithRegisterAWithoutCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_CP_AB);
	cpu.regs->A = 0x00;
	cpu.regs->B = 0x01;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 0;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_TRUE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, CPAHLCanCompareAddress_HL_WithRegisterAWithCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_CP_AHL);
	cpu.regs->A = 0x01;
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x1);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	cpu.regs->negative = 0;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x01);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_TRUE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, CPAHLCanCompareAddress_HL_WithRegisterAWithHalfCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_CP_AHL);
	cpu.regs->A = 0x40;
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x04);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 0;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x40);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_TRUE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, CPAHLCanCompareAddress_HL_WithRegisterAWithoutCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_CP_AHL);
	cpu.regs->A = 0x00;
	cpu.regs->HL = 0x0200;
	cpu.mem->write_to_address(0x200, 0x01);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 0;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_TRUE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, CPAIMCanCompareImmediateValueWithRegisterAWithCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_CP_AIM);
	cpu.regs->A = 0x01;
	cpu.mem->write_to_address(0x101, 0x1);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	cpu.regs->negative = 0;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x01);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_TRUE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, CPAIMCanCompareImmediateValueWithRegisterAWithHalfCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_CP_AIM);
	cpu.regs->A = 0x40;
	cpu.mem->write_to_address(0x101, 0x04);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 0;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x40);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_TRUE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_TRUE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, CPAIMCanCompareImmediateValueWithRegisterAWithoutCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_CP_AIM);
	cpu.regs->A = 0x00;
	cpu.mem->write_to_address(0x101, 0x01);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 0;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_TRUE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// ##################### INC ################
TEST_F(_8BitALUTests, INCRegisterCanIncreaseRegisterA)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_INC_A);
	cpu.regs->A = 0x00;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
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
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, INCRegisterCanIncreaseRegisterAZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_INC_A);
	cpu.regs->A = 0xFF;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, INCRegisterCanIncreaseRegisterAHalfCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_INC_A);
	cpu.regs->A = 0x0F;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x10);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, INCRegisterCanIncreaseAddress_HL_)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_INC_HL_);
	cpu.regs->HL = 0x200;
	cpu.mem->write_to_address(0x200, 0x00);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 1;
	Byte expected_machine_cycles = 3;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x01);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, INCRegisterCanIncreaseAddress_HL_Zero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_INC_HL_);
	cpu.regs->HL = 0x200;
	cpu.mem->write_to_address(0x200, 0xFF);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 3;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, INCRegisterCanIncreaseAddress_HL_HalfCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_INC_HL_);
	cpu.regs->HL = 0x200;
	cpu.mem->write_to_address(0x200, 0x0F);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 3;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x10);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_FALSE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// ##################### DEC ################
TEST_F(_8BitALUTests, DECRegisterCanDecreaseRegisterAHalfCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_DEC_A);
	cpu.regs->A = 0x02;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 0;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x01);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_TRUE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, DECRegisterCanDecreaseRegisterAZero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_DEC_A);
	cpu.regs->A = 0x01;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	cpu.regs->negative = 0;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_TRUE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, DECRegisterCanDecreaseRegisterA)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_DEC_A);
	cpu.regs->A = 0x00;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 0;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 1;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0xFF);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_TRUE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, DECRegisterCanDecreaseAddress_HL_HalfCarry)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_DEC_HL_);
	cpu.regs->HL = 0x200;
	cpu.mem->write_to_address(0x200, 0x02);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 0;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 3;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x01);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_TRUE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, DECRegisterCanDecreaseAddress_HL_Zero)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_DEC_HL_);
	cpu.regs->HL = 0x200;
	cpu.mem->write_to_address(0x200, 0x01);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	cpu.regs->negative = 1;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 0;
	Byte expected_machine_cycles = 3;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x00);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_TRUE(cpu.regs->half_carry);
	EXPECT_TRUE(cpu.regs->negative);
	EXPECT_TRUE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitALUTests, DECRegisterCanDecreaseAddress_HL_)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_DEC_HL_);
	cpu.regs->HL = 0x200;
	cpu.mem->write_to_address(0x200, 0x00);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	cpu.regs->negative = 0;
	cpu.regs->carry = 0;
	cpu.regs->half_carry = 1;
	Byte expected_machine_cycles = 3;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0xFF);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_FALSE(cpu.regs->carry);
	EXPECT_FALSE(cpu.regs->half_carry);
	EXPECT_TRUE(cpu.regs->negative);
	EXPECT_FALSE(cpu.regs->zero);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}
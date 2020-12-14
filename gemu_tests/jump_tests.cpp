#include "pch.h"
#include "../GameBoyEmu/GZ80.h"
#include "../GameBoyEmu/memory.h"
using namespace GZ80;
class JumpTests : public testing::Test
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

// ################## Jumps #####################
// Jump Immediate
TEST_F(JumpTests, JumpImmediateJumpsToSpecifiedPosition)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_JPIM);
	cpu.mem->write_to_address(0x101, 0x00);
	cpu.mem->write_to_address(0x102, 0x02);
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 3;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x200 + 1);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// Jump not Zero
TEST_F(JumpTests, JumpNotZeroJumpsToSpecifiedPositionIfZeroFlagIsReset)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_JPNZ);
	cpu.mem->write_to_address(0x101, 0x00);
	cpu.mem->write_to_address(0x102, 0x02);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	Byte expected_machine_cycles = 3;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x200 + 1);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(JumpTests, JumpNotZeroDoesntJumpToSpecifiedPositionIfZeroFlagIsSet)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_JPNZ);
	cpu.mem->write_to_address(0x101, 0x00);
	cpu.mem->write_to_address(0x102, 0x02);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	Byte expected_machine_cycles = 3;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x103 + 1);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// Jump Zero
TEST_F(JumpTests, JumpZeroJumpsToSpecifiedPositionIfZeroFlagIsSet)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_JPZ);
	cpu.mem->write_to_address(0x101, 0x00);
	cpu.mem->write_to_address(0x102, 0x02);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	Byte expected_machine_cycles = 3;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x200 + 1);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(JumpTests, JumpZeroDoesntJumpToSpecifiedPositionIfZeroFlagIsReset)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_JPZ);
	cpu.mem->write_to_address(0x101, 0x00);
	cpu.mem->write_to_address(0x102, 0x02);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	Byte expected_machine_cycles = 3;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x103 + 1);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// Jump not Carry
TEST_F(JumpTests, JumpNotCarryJumpsToSpecifiedPositionIfCarryFlagIsReset)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_JPNC);
	cpu.mem->write_to_address(0x101, 0x00);
	cpu.mem->write_to_address(0x102, 0x02);
	cpu.regs->pc = 0x100;
	cpu.regs->carry = 0;
	Byte expected_machine_cycles = 3;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x200 + 1);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(JumpTests, JumpNotCarryDoesntJumpToSpecifiedPositionIfCarryFlagIsSet)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_JPNC);
	cpu.mem->write_to_address(0x101, 0x00);
	cpu.mem->write_to_address(0x102, 0x02);
	cpu.regs->pc = 0x100;
	cpu.regs->carry = 1;
	Byte expected_machine_cycles = 3;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x103 + 1);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// Jump Carry
TEST_F(JumpTests, JumpCarryJumpsToSpecifiedPositionIfCarryFlagIsSet)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_JPC);
	cpu.mem->write_to_address(0x101, 0x00);
	cpu.mem->write_to_address(0x102, 0x02);
	cpu.regs->pc = 0x100;
	cpu.regs->carry = 1;
	Byte expected_machine_cycles = 3;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x200 + 1);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(JumpTests, JumpCarryDoesntJumpToSpecifiedPositionIfCarryFlagIsReset)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_JPC);
	cpu.mem->write_to_address(0x101, 0x00);
	cpu.mem->write_to_address(0x102, 0x02);
	cpu.regs->pc = 0x100;
	cpu.regs->carry = 0;
	Byte expected_machine_cycles = 3;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x103 + 1);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// Jump to HL
TEST_F(JumpTests, JumpToHLJumpsToHL)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_JPHL);
	cpu.regs->HL = 0x200;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x200 + 1);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// Jump relative
TEST_F(JumpTests, JumpRelativeJumpsForwards)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_JR);
	cpu.mem->write_to_address(0x101, 0x20);
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x121 + 1);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(JumpTests, JumpRelativeJumpsBackwards)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_JR);
	cpu.mem->write_to_address(0x101, 0xA0);
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x0A1 + 1);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// Jump relative Not Zero
TEST_F(JumpTests, JumpRelativeNotZeroJumpsForwardsIfZeroFlagIsReset)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_JRNZ);
	cpu.mem->write_to_address(0x101, 0x20);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x121 + 1);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(JumpTests, JumpRelativeNotZeroDoesntJumpForwardsIfZeroFlagIsSet)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_JRNZ);
	cpu.mem->write_to_address(0x101, 0x20);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x102 + 1);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(JumpTests, JumpRelativeNotZeroJumpsBackwardsIfZeroFlagIsReset)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_JRNZ);
	cpu.mem->write_to_address(0x101, 0xA0);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x0A1 + 1);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(JumpTests, JumpRelativeNotZeroDoesntJumpBackwardsIfZeroFlagIsSet)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_JRNZ);
	cpu.mem->write_to_address(0x101, 0xA0);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x102 + 1);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// Jump relative Zero
TEST_F(JumpTests, JumpRelativeZeroJumpsForwardsIfZeroFlagIsSet)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_JRZ);
	cpu.mem->write_to_address(0x101, 0x20);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x121 + 1);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(JumpTests, JumpRelativeZeroDoesntJumpForwardsIfZeroFlagIsReset)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_JRZ);
	cpu.mem->write_to_address(0x101, 0x20);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x102 + 1);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(JumpTests, JumpRelativeZeroJumpsBackwardsIfZeroFlagIsSet)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_JRZ);
	cpu.mem->write_to_address(0x101, 0xA0);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 1;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x0A1 + 1);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(JumpTests, JumpRelativeZeroDoesntJumpBackwardsIfZeroFlagIsReset)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_JRZ);
	cpu.mem->write_to_address(0x101, 0xA0);
	cpu.regs->pc = 0x100;
	cpu.regs->zero = 0;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x102 + 1);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// Jump relative Not Carry
TEST_F(JumpTests, JumpRelativeNotCarryJumpsForwardsIfCarryFlagIsReset)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_JRNC);
	cpu.mem->write_to_address(0x101, 0x20);
	cpu.regs->pc = 0x100;
	cpu.regs->carry = 0;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x121 + 1);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(JumpTests, JumpRelativeNotCarryDoesntJumpForwardsIfCarryFlagIsSet)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_JRNC);
	cpu.mem->write_to_address(0x101, 0x20);
	cpu.regs->pc = 0x100;
	cpu.regs->carry = 1;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x102 + 1);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(JumpTests, JumpRelativeNotCarryJumpsBackwardsIfCarryFlagIsReset)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_JRNC);
	cpu.mem->write_to_address(0x101, 0xA0);
	cpu.regs->pc = 0x100;
	cpu.regs->carry = 0;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x0A1 + 1);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(JumpTests, JumpRelativeNotCarryDoesntJumpBackwardsIfCarryFlagIsSet)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_JRNC);
	cpu.mem->write_to_address(0x101, 0xA0);
	cpu.regs->pc = 0x100;
	cpu.regs->carry = 1;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x102 + 1);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// Jump relative Carry
TEST_F(JumpTests, JumpRelativeCarryJumpsForwardsIfCarryFlagIsSet)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_JRC);
	cpu.mem->write_to_address(0x101, 0x20);
	cpu.regs->pc = 0x100;
	cpu.regs->carry = 1;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x121 + 1);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(JumpTests, JumpRelativeCarryDoesntJumpForwardsIfCarryFlagIsReset)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_JRC);
	cpu.mem->write_to_address(0x101, 0x20);
	cpu.regs->pc = 0x100;
	cpu.regs->carry = 0;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x102 + 1);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(JumpTests, JumpRelativeCarryJumpsBackwardsIfCarryFlagIsSet)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_JRC);
	cpu.mem->write_to_address(0x101, 0xA0);
	cpu.regs->pc = 0x100;
	cpu.regs->carry = 1;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x0A1 + 1);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(JumpTests, JumpRelativeCarryDoesntJumpBackwardsIfCarryFlagIsReset)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_JRC);
	cpu.mem->write_to_address(0x101, 0xA0);
	cpu.regs->pc = 0x100;
	cpu.regs->carry = 0;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x102 + 1);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}
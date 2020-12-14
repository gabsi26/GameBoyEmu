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

	void jump_tests(Byte instruction, bool relative, bool hl, bool use_zero, bool use_carry, bool zero, bool carry, bool zero_wanted, bool carry_wanted, Byte expected_cycles, bool backwards = false);
};

void JumpTests::jump_tests(Byte instruction, bool relative, bool hl, bool use_zero, bool use_carry, bool zero, bool carry, bool zero_wanted, bool carry_wanted, Byte expected_cycles, bool backwards)
{
	// given
	cpu.mem->write_to_address(0x100, instruction);
	if (!relative && !hl)
	{
		cpu.mem->write_to_address(0x101, 0x00);
		cpu.mem->write_to_address(0x102, 0x02);
	}
	else if (hl)
	{
		cpu.regs->HL = 0x200;
		
	}
	else if (!backwards)
	{
		cpu.mem->write_to_address(0x101, 0x20);
	}
	else
	{
		cpu.mem->write_to_address(0x101, 0xA0);
	}
	if (use_zero)
	{
		cpu.regs->zero = zero;
	}
	else if (use_carry)
	{
		cpu.regs->carry = carry;
	}
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = expected_cycles;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_cycles);
	// then
	if (((use_carry && cpu.regs->carry == carry_wanted) || (use_zero && cpu.regs->zero == zero_wanted) || (!use_carry && !use_zero)))
	{
		if (relative)
		{
			if (!backwards)
			{
				EXPECT_EQ(cpu.regs->pc, 0x121 + 1);
			}
			else
			{
				EXPECT_EQ(cpu.regs->pc, 0x0A1 + 1);
			}
		}
		else
		{
			EXPECT_EQ(cpu.regs->pc, 0x200 + 1);
		}
	}
	else if (relative && (use_carry || use_zero))
	{
		EXPECT_EQ(cpu.regs->pc, 0x102 + 1);
	}
	else
	{
		EXPECT_EQ(cpu.regs->pc, 0x103 + 1);
	}
	EXPECT_EQ(cpu.cycles->mc, expected_cycles);
}

// ################## Jumps #####################
// Jump Immediate
TEST_F(JumpTests, JumpImmediateJumpsToSpecifiedPosition)
{
	jump_tests(CPU::INS_JPIM, 0, 0, 0, 0, 0, 0, 0, 0, 4);
}

// Jump not Zero
TEST_F(JumpTests, JumpNotZeroJumpsToSpecifiedPositionIfZeroFlagIsReset)
{
	jump_tests(CPU::INS_JPNZ, 0, 0, 1, 0, 0, 0, 0, 0, 4);
}

TEST_F(JumpTests, JumpNotZeroDoesntJumpToSpecifiedPositionIfZeroFlagIsSet)
{
	jump_tests(CPU::INS_JPNZ, 0, 0, 1, 0, 1, 0, 0, 0, 3);
}

// Jump Zero
TEST_F(JumpTests, JumpZeroJumpsToSpecifiedPositionIfZeroFlagIsSet)
{
	jump_tests(CPU::INS_JPZ, 0, 0, 1, 0, 1, 0, 1, 0, 4);
}

TEST_F(JumpTests, JumpZeroDoesntJumpToSpecifiedPositionIfZeroFlagIsReset)
{
	jump_tests(CPU::INS_JPZ, 0, 0, 1, 0, 0, 0, 1, 0, 3);
}

// Jump not Carry
TEST_F(JumpTests, JumpNotCarryJumpsToSpecifiedPositionIfCarryFlagIsReset)
{
	jump_tests(CPU::INS_JPNC, 0, 0, 0, 1, 0, 0, 0, 0, 4);
}

TEST_F(JumpTests, JumpNotCarryDoesntJumpToSpecifiedPositionIfCarryFlagIsSet)
{
	jump_tests(CPU::INS_JPNC, 0, 0, 0, 1, 0, 1, 0, 0, 3);
}

// Jump Carry
TEST_F(JumpTests, JumpCarryJumpsToSpecifiedPositionIfCarryFlagIsSet)
{
	jump_tests(CPU::INS_JPC, 0, 0, 0, 1, 0, 1, 0, 1, 4);
}

TEST_F(JumpTests, JumpCarryDoesntJumpToSpecifiedPositionIfCarryFlagIsReset)
{
	jump_tests(CPU::INS_JPC, 0, 0, 0, 1, 0, 0, 0, 1, 3);
}

// Jump to HL
TEST_F(JumpTests, JumpToHLJumpsToHL)
{
	jump_tests(CPU::INS_JPHL, 0, 1, 0, 0, 0, 0, 0, 0, 1);
}

// Jump relative
TEST_F(JumpTests, JumpRelativeJumpsForwards)
{
	jump_tests(CPU::INS_JR, 1, 0, 0, 0, 0, 0, 0, 0, 3);
}

TEST_F(JumpTests, JumpRelativeJumpsBackwards)
{
	jump_tests(CPU::INS_JR, 1, 0, 0, 0, 0, 0, 0, 0, 3, 1);
}

// Jump relative Not Zero
TEST_F(JumpTests, JumpRelativeNotZeroJumpsForwardsIfZeroFlagIsReset)
{
	jump_tests(CPU::INS_JRNZ, 1, 0, 1, 0, 0, 0, 0, 0, 3);
}

TEST_F(JumpTests, JumpRelativeNotZeroDoesntJumpForwardsIfZeroFlagIsSet)
{
	jump_tests(CPU::INS_JRNZ, 1, 0, 1, 0, 1, 0, 0, 0, 2);
}

TEST_F(JumpTests, JumpRelativeNotZeroJumpsBackwardsIfZeroFlagIsReset)
{
	jump_tests(CPU::INS_JRNZ, 1, 0, 1, 0, 0, 0, 0, 0, 3, 1);
}

TEST_F(JumpTests, JumpRelativeNotZeroDoesntJumpBackwardsIfZeroFlagIsSet)
{
	jump_tests(CPU::INS_JRNZ, 1, 0, 1, 0, 1, 0, 0, 0, 2, 1);
}

// Jump relative Zero
TEST_F(JumpTests, JumpRelativeZeroJumpsForwardsIfZeroFlagIsSet)
{
	jump_tests(CPU::INS_JRZ, 1, 0, 1, 0, 1, 0, 1, 0, 3);
}

TEST_F(JumpTests, JumpRelativeZeroDoesntJumpForwardsIfZeroFlagIsReset)
{
	jump_tests(CPU::INS_JRZ, 1, 0, 1, 0, 0, 0, 1, 0, 2);
}

TEST_F(JumpTests, JumpRelativeZeroJumpsBackwardsIfZeroFlagIsSet)
{
	jump_tests(CPU::INS_JRZ, 1, 0, 1, 0, 1, 0, 1, 0, 3, 1);
}

TEST_F(JumpTests, JumpRelativeZeroDoesntJumpBackwardsIfZeroFlagIsReset)
{
	jump_tests(CPU::INS_JRZ, 1, 0, 1, 0, 0, 0, 1, 0, 2, 1);
}

// Jump relative Not Carry
TEST_F(JumpTests, JumpRelativeNotCarryJumpsForwardsIfCarryFlagIsReset)
{
	jump_tests(CPU::INS_JRNC, 1, 0, 0, 1, 0, 0, 0, 0, 3);
}

TEST_F(JumpTests, JumpRelativeNotCarryDoesntJumpForwardsIfCarryFlagIsSet)
{
	jump_tests(CPU::INS_JRNC, 1, 0, 0, 1, 0, 1, 0, 0, 2);
}

TEST_F(JumpTests, JumpRelativeNotCarryJumpsBackwardsIfCarryFlagIsReset)
{
	jump_tests(CPU::INS_JRNC, 1, 0, 0, 1, 0, 0, 0, 0, 3, 1);
}

TEST_F(JumpTests, JumpRelativeNotCarryDoesntJumpBackwardsIfCarryFlagIsSet)
{
	jump_tests(CPU::INS_JRNC, 1, 0, 0, 1, 0, 1, 0, 0, 2, 1);
}

// Jump relative Carry
TEST_F(JumpTests, JumpRelativeCarryJumpsForwardsIfCarryFlagIsSet)
{
	jump_tests(CPU::INS_JRC, 1, 0, 0, 1, 0, 1, 0, 1, 3);
}

TEST_F(JumpTests, JumpRelativeCarryDoesntJumpForwardsIfCarryFlagIsReset)
{
	jump_tests(CPU::INS_JRC, 1, 0, 0, 1, 0, 0, 0, 1, 2);
}

TEST_F(JumpTests, JumpRelativeCarryJumpsBackwardsIfCarryFlagIsSet)
{
	jump_tests(CPU::INS_JRC, 1, 0, 0, 1, 0, 1, 0, 1, 3, 1);
}

TEST_F(JumpTests, JumpRelativeCarryDoesntJumpBackwardsIfCarryFlagIsReset)
{
	jump_tests(CPU::INS_JRC, 1, 0, 0, 1, 0, 0, 0, 1, 2, 1);
}
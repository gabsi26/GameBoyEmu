#include "pch.h"
#include "../GameBoyEmu/GZ80.h"

class InitTests : public testing::Test
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

TEST_F(InitTests, RegistersSPAndPCGetInitalisedCorrectly)
{
	EXPECT_EQ(cpu.regs->AF, 0x0);
	EXPECT_EQ(cpu.regs->BC, 0x0);
	EXPECT_EQ(cpu.regs->DE, 0x0);
	EXPECT_EQ(cpu.regs->HL, 0x0);
	EXPECT_EQ(cpu.regs->sp, 0xFFFE);
	EXPECT_EQ(cpu.regs->pc, 0x0100);
}
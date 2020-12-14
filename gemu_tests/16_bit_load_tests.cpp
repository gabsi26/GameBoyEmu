#include "pch.h"
#include "../GameBoyEmu/GZ80.h"
#include "../GameBoyEmu/memory.h"
using namespace GZ80;
class _16BitLoadTests : public testing::Test
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

// ---------- immediate -------------
TEST_F(_16BitLoadTests, LDBCnnCanLoadAValueIntoRegisterBC)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_BCnn);
	cpu.mem->write_to_address(0x101, 0xEE);
	cpu.mem->write_to_address(0x102, 0xFF);
	cpu.regs->BC = 0x00;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 3;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->BC, 0xFFEE);
	EXPECT_EQ(cpu.regs->pc, 0x103);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_16BitLoadTests, LDDEnnCanLoadAValueIntoRegisterDE)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_DEnn);
	cpu.mem->write_to_address(0x101, 0xEE);
	cpu.mem->write_to_address(0x102, 0xFF);
	cpu.regs->DE = 0x00;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 3;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->DE, 0xFFEE);
	EXPECT_EQ(cpu.regs->pc, 0x103);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_16BitLoadTests, LDHLnnCanLoadAValueIntoRegisterHL)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_HLnn);
	cpu.mem->write_to_address(0x101, 0xEE);
	cpu.mem->write_to_address(0x102, 0xFF);
	cpu.regs->HL = 0x00;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 3;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->HL, 0xFFEE);
	EXPECT_EQ(cpu.regs->pc, 0x103);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_16BitLoadTests, LDSPnnCanLoadAValueIntoSP)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_SPnn);
	cpu.mem->write_to_address(0x101, 0xEE);
	cpu.mem->write_to_address(0x102, 0xFF);
	cpu.regs->sp = 0x00;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 3;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->sp, 0xFFEE);
	EXPECT_EQ(cpu.regs->pc, 0x103);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// stack load and store operations
TEST_F(_16BitLoadTests, LDSPHLCanPutHLIntoSP)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_SPHL);
	cpu.regs->HL = 0xFFEE;
	cpu.regs->sp = 0x00;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->sp, 0xFFEE);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_16BitLoadTests, LDHLSPnCanPutSPPlusnIntoHLWithoutSettingAnyFlag)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LDHL_SPn);
	cpu.mem->write_to_address(0x101, 0x02);
	cpu.regs->HL = 0x0000;
	cpu.regs->sp = 0xFFF8;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = cpu.regs->negative = 1;
	cpu.regs->half_carry = cpu.regs->carry = 0;
	Byte expected_machine_cycles = 3;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->HL, 0xFFFA);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
	EXPECT_EQ(cpu.regs->zero, 0);
	EXPECT_EQ(cpu.regs->negative, 0);
	EXPECT_EQ(cpu.regs->half_carry, 0);
	EXPECT_EQ(cpu.regs->carry, 0);
}

TEST_F(_16BitLoadTests, LDHLSPnCanPutSPPlusnIntoHLWhileSettingCarryAndHalfCarryFlags)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LDHL_SPn);
	cpu.mem->write_to_address(0x101, 0xFF);
	cpu.regs->HL = 0x0000;
	cpu.regs->sp = 0xFFFF;
	cpu.regs->pc = 0x100;
	cpu.regs->zero = cpu.regs->negative = 1;
	cpu.regs->half_carry = cpu.regs->carry = 0;
	Byte expected_machine_cycles = 3;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->HL, 0xFFFE);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
	EXPECT_EQ(cpu.regs->zero, 0);
	EXPECT_EQ(cpu.regs->negative, 0);
	EXPECT_EQ(cpu.regs->half_carry, 1);
	EXPECT_EQ(cpu.regs->carry, 1);
}

TEST_F(_16BitLoadTests, LDnnSPCanPutValueOfSPIntoAddressnn)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_nnSP);
	cpu.mem->write_to_address(0x101, 0x00);
	cpu.mem->write_to_address(0x102, 0x02);
	cpu.mem->write_to_address(0x200, 0x00);
	cpu.regs->sp = 0xFFEE;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 5;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0xFF);
	EXPECT_EQ(cpu.mem->read_from_address(0x201), 0xEE);
	EXPECT_EQ(cpu.regs->pc, 0x103);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_16BitLoadTests, PUSHAFCanPushValueInAFOntoStack)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_PUSH_AF);
	cpu.regs->A = 0x11;
	cpu.regs->F = 0x22;
	cpu.regs->sp = 0xFFFE;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0xFFFE), 0x22);
	EXPECT_EQ(cpu.mem->read_from_address(0xFFFD), 0x11);
	EXPECT_EQ(cpu.regs->sp, 0xFFFC);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_16BitLoadTests, PUSHBCCanPushValueInBCOntoStack)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_PUSH_BC);
	cpu.regs->B = 0x11;
	cpu.regs->C = 0x22;
	cpu.regs->sp = 0xFFFE;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0xFFFE), 0x22);
	EXPECT_EQ(cpu.mem->read_from_address(0xFFFD), 0x11);
	EXPECT_EQ(cpu.regs->sp, 0xFFFC);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_16BitLoadTests, PUSHDECanPushValueInDEOntoStack)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_PUSH_DE);
	cpu.regs->D = 0x11;
	cpu.regs->E = 0x22;
	cpu.regs->sp = 0xFFFE;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0xFFFE), 0x22);
	EXPECT_EQ(cpu.mem->read_from_address(0xFFFD), 0x11);
	EXPECT_EQ(cpu.regs->sp, 0xFFFC);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_16BitLoadTests, PUSHHLCanPushValueInHLOntoStack)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_PUSH_HL);
	cpu.regs->H = 0x11;
	cpu.regs->L = 0x22;
	cpu.regs->sp = 0xFFFE;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0xFFFE), 0x22);
	EXPECT_EQ(cpu.mem->read_from_address(0xFFFD), 0x11);
	EXPECT_EQ(cpu.regs->sp, 0xFFFC);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_16BitLoadTests, POPAFCanPopValueFromStackIntoAF)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_POP_AF);
	cpu.mem->write_to_address(0xFFFE, 0x22);
	cpu.mem->write_to_address(0xFFFD, 0x11);
	cpu.regs->sp = 0xFFFC;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 3;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x11);
	EXPECT_EQ(cpu.regs->F, 0x22);
	EXPECT_EQ(cpu.regs->sp, 0xFFFE);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_16BitLoadTests, POPBCCanPopValueFromStackIntoBC)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_POP_BC);
	cpu.mem->write_to_address(0xFFFE, 0x22);
	cpu.mem->write_to_address(0xFFFD, 0x11);
	cpu.regs->sp = 0xFFFC;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 3;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->B, 0x11);
	EXPECT_EQ(cpu.regs->C, 0x22);
	EXPECT_EQ(cpu.regs->sp, 0xFFFE);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_16BitLoadTests, POPDECanPopValueFromStackIntoDE)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_POP_DE);
	cpu.mem->write_to_address(0xFFFE, 0x22);
	cpu.mem->write_to_address(0xFFFD, 0x11);
	cpu.regs->sp = 0xFFFC;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 3;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->D, 0x11);
	EXPECT_EQ(cpu.regs->E, 0x22);
	EXPECT_EQ(cpu.regs->sp, 0xFFFE);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_16BitLoadTests, POPHLCanPopValueFromStackIntoHL)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_POP_HL);
	cpu.mem->write_to_address(0xFFFE, 0x22);
	cpu.mem->write_to_address(0xFFFD, 0x11);
	cpu.regs->sp = 0xFFFC;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 3;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->H, 0x11);
	EXPECT_EQ(cpu.regs->L, 0x22);
	EXPECT_EQ(cpu.regs->sp, 0xFFFE);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}
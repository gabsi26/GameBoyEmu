#include "pch.h"
#include "../GameBoyEmu/GZ80.h"
#include "../GameBoyEmu/memory.h"
using namespace GZ80;
class _8BitLoadTests : public testing::Test
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
TEST_F(_8BitLoadTests, LDBnCanLoadAValueIntoRegisterB)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_Bn);
	cpu.mem->write_to_address(0x101, 0x42);
	cpu.regs->B = 0x00;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->B, 0x42);
	EXPECT_EQ(cpu.regs->pc, 0x102); 
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDCnCanLoadAValueIntoRegisterC)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_Cn);
	cpu.mem->write_to_address(0x101, 0x42);
	cpu.regs->C = 0x00;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->C, 0x42);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDDnCanLoadAValueIntoRegisterD)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_Dn);
	cpu.mem->write_to_address(0x101, 0x42);
	cpu.regs->D = 0x00;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->D, 0x42);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDEnCanLoadAValueIntoRegisterE)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_En);
	cpu.mem->write_to_address(0x101, 0x42);
	cpu.regs->E = 0x00;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->E, 0x42);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDHnCanLoadAValueIntoRegisterH)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_Hn);
	cpu.mem->write_to_address(0x101, 0x42);
	cpu.regs->H = 0x00;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->H, 0x42);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDLnCanLoadAValueIntoRegisterL)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_Ln);
	cpu.mem->write_to_address(0x101, 0x42);
	cpu.regs->L = 0x00;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->L, 0x42);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDHLnCanLoadAValueImmediateIntoAddressHL)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_HLn);
	cpu.mem->write_to_address(0x101, 0xAA);
	cpu.regs->HL = 0x0200;
	cpu.regs->pc = 0x100;
	cpu.mem->write_to_address(0x200, 0x00);
	Byte expected_machine_cycles = 3;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDAnCanLoadAValueIntoRegisterA)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_An);
	cpu.mem->write_to_address(0x101, 0x42);
	cpu.regs->A = 0x00;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0x42);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// ------------------ store in A ----------------------
TEST_F(_8BitLoadTests, LDAACanLoadAValueFromRegisterAIntoRegisterA)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_AA);
	cpu.regs->A = 0x10;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDABCanLoadAValueFromRegisterBIntoRegisterA)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_AB);
	cpu.regs->A = 0x00;
	cpu.regs->B = 0xAA;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDACCanLoadAValueFromRegisterCIntoRegisterA)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_AC);
	cpu.regs->A = 0x10;
	cpu.regs->C = 0xAA;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDADCanLoadAValueFromRegisterDIntoRegisterA)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_AD);
	cpu.regs->A = 0x10;
	cpu.regs->D = 0xAA;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDAECanLoadAValueFromRegisterEIntoRegisterA)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_AE);
	cpu.regs->A = 0x10;
	cpu.regs->E = 0xAA;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDAHCanLoadAValueFromRegisterHIntoRegisterA)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_AH);
	cpu.regs->A = 0x10;
	cpu.regs->H = 0xAA;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDALCanLoadAValueFromRegisterLIntoRegisterA)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_AL);
	cpu.regs->A = 0x10;
	cpu.regs->L = 0xAA;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDAHLCanLoadAValueFromAddress_HL_IntoRegisterA)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_AHL);
	cpu.regs->A = 0x10;
	cpu.regs->HL = 0x0200;
	cpu.regs->pc = 0x100;
	cpu.mem->write_to_address(0x200, 0xAA);
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDABCCanLoadAValueFromAddress_BC_IntoRegisterA)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_ABC);
	cpu.regs->A = 0x10;
	cpu.regs->BC = 0x0200;
	cpu.regs->pc = 0x100;
	cpu.mem->write_to_address(0x200, 0xAA);
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDADECanLoadAValueFromAddress_DE_IntoRegisterA)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_ADE);
	cpu.regs->A = 0x10;
	cpu.regs->DE = 0x0200;
	cpu.regs->pc = 0x100;
	cpu.mem->write_to_address(0x200, 0xAA);
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDAnnCanLoadAValueFromAddress_nn_IntoRegisterA)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_Ann);
	cpu.regs->A = 0x10;
	cpu.mem->write_to_address(0x101, 0x00);
	cpu.mem->write_to_address(0x102, 0x02);
	cpu.regs->pc = 0x100;
	cpu.mem->write_to_address(0x200, 0xAA);
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x103);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDA_C_CanLoadAValueFromAddress_0xFF00_C_IntoRegisterA)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_A_C_);
	cpu.regs->A = 0x00;
	cpu.regs->C = 0xA0;
	cpu.regs->pc = 0x100;
	cpu.mem->write_to_address(0xFFA0, 0xAA);
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// ------------------------ load from A ---------------------
TEST_F(_8BitLoadTests, LDBACanLoadAValueFromRegisterAIntoRegisterB)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_BA);
	cpu.regs->B = 0x00;
	cpu.regs->A = 0xAA;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->B, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDCACanLoadAValueFromRegisterAIntoRegisterC)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_CA);
	cpu.regs->C = 0x10;
	cpu.regs->A = 0xAA;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->C, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDDACanLoadAValueFromRegisterAIntoRegisterD)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_DA);
	cpu.regs->D = 0x10;
	cpu.regs->A = 0xAA;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->D, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDEACanLoadAValueFromRegisterAIntoRegisterE)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_EA);
	cpu.regs->E = 0x10;
	cpu.regs->A = 0xAA;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->E, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDHACanLoadAValueFromRegisterAIntoRegisterH)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_HA);
	cpu.regs->H = 0x10;
	cpu.regs->A = 0xAA;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->H, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDLACanLoadAValueFromRegisterAIntoRegisterL)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_LA);
	cpu.regs->L = 0x10;
	cpu.regs->A = 0xAA;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->L, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDBCACanLoadAValueFromRegisterAIntoAddress_BC_)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_BCA);
	cpu.regs->A = 0xAA;
	cpu.regs->BC = 0x0200;
	cpu.regs->pc = 0x100;
	cpu.mem->write_to_address(0x200, 0x00);
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x0200), 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDDEACanLoadAValueFromRegisterAIntoAddress_DE_)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_DEA);
	cpu.regs->A = 0xAA;
	cpu.regs->DE = 0x0200;
	cpu.regs->pc = 0x100;
	cpu.mem->write_to_address(0x200, 0x00);
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x0200), 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDHLACanLoadAValueFromRegisterAIntoAddress_HL_)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_HLA);
	cpu.regs->A = 0xAA;
	cpu.regs->HL = 0x0200;
	cpu.regs->pc = 0x100;
	cpu.mem->write_to_address(0x200, 0x00);
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x0200), 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDnnACanLoadAValueFromRegisterAIntoAddress_nn_)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_nnA);
	cpu.regs->A = 0xAA;
	cpu.mem->write_to_address(0x101, 0x00);
	cpu.mem->write_to_address(0x102, 0x02);
	cpu.regs->pc = 0x100;
	cpu.mem->write_to_address(0x200, 0x00);
	Byte expected_machine_cycles = 4;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x103);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LD_C_ACanLoadAValueFromRegisterAIntoAddress_0xFF00_C)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_C_A);
	cpu.regs->A = 0xAA;
	cpu.regs->C = 0x00A0;
	cpu.regs->pc = 0x100;
	cpu.mem->write_to_address(0xFFA0, 0x00);
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0xFFA0), 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// ------------------------ store in B ------------------------
TEST_F(_8BitLoadTests, LDBBCanLoadAValueFromRegisterBIntoRegisterB)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_BB);
	cpu.regs->B = 0xAA;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->B, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDBCCanLoadAValueFromRegisterCIntoRegisterB)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_BC);
	cpu.regs->B = 0x00;
	cpu.regs->C = 0xAA;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->B, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDBDCanLoadAValueFromRegisterDIntoRegisterB)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_BD);
	cpu.regs->B = 0x00;
	cpu.regs->D = 0xAA;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->B, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDBECanLoadAValueFromRegisterEIntoRegisterB)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_BE);
	cpu.regs->B = 0x00;
	cpu.regs->E = 0xAA;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->B, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDBHCanLoadAValueFromRegisterHIntoRegisterB)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_BH);
	cpu.regs->B = 0x00;
	cpu.regs->H = 0xAA;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->B, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDBLCanLoadAValueFromRegisterLIntoRegisterB)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_BL);
	cpu.regs->B = 0x00;
	cpu.regs->L = 0xAA;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->B, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDBHLCanLoadAValueFromAddress_HL_IntoRegisterB)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_BHL);
	cpu.regs->B = 0x00;
	cpu.regs->HL = 0x0200;
	cpu.regs->pc = 0x100;
	cpu.mem->write_to_address(0x200, 0xAA);
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->B, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// ------------ store in C ---------------------
TEST_F(_8BitLoadTests, LDCBCanLoadAValueFromRegisterBIntoRegisterC)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_CB);
	cpu.regs->B = 0xAA;
	cpu.regs->C = 0x00;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->C, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDCCCanLoadAValueFromRegisterCIntoRegisterC)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_CC);
	cpu.regs->C = 0xAA;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->C, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDCDCanLoadAValueFromRegisterDIntoRegisterC)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_CD);
	cpu.regs->C = 0x00;
	cpu.regs->D = 0xAA;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->C, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDCECanLoadAValueFromRegisterEIntoRegisterC)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_CE);
	cpu.regs->C = 0x00;
	cpu.regs->E = 0xAA;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->C, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDCHCanLoadAValueFromRegisterHIntoRegisterC)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_CH);
	cpu.regs->C = 0x00;
	cpu.regs->H = 0xAA;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->C, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDCLCanLoadAValueFromRegisterLIntoRegisterC)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_CL);
	cpu.regs->C = 0x00;
	cpu.regs->L = 0xAA;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->C, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDCHLCanLoadAValueFromAddress_HL_IntoRegisterC)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_CHL);
	cpu.regs->C = 0x00;
	cpu.regs->HL = 0x0200;
	cpu.regs->pc = 0x100;
	cpu.mem->write_to_address(0x200, 0xAA);
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->C, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// -------------------- store in D -------------------------
TEST_F(_8BitLoadTests, LDDBCanLoadAValueFromRegisterBIntoRegisterD)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_DB);
	cpu.regs->B = 0xAA;
	cpu.regs->D = 0x00;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->D, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDDCCanLoadAValueFromRegisterCIntoRegisterD)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_DC);
	cpu.regs->C = 0xAA;
	cpu.regs->D = 0x00;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->D, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDDDCanLoadAValueFromRegisterDIntoRegisterD)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_DD);
	cpu.regs->D = 0xAA;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->D, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDDECanLoadAValueFromRegisterEIntoRegisterD)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_DE);
	cpu.regs->D = 0x00;
	cpu.regs->E = 0xAA;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->D, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDDHCanLoadAValueFromRegisterHIntoRegisterD)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_DH);
	cpu.regs->D = 0x00;
	cpu.regs->H = 0xAA;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->D, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDDLCanLoadAValueFromRegisterLIntoRegisterD)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_DL);
	cpu.regs->D = 0x00;
	cpu.regs->L = 0xAA;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->D, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDDHLCanLoadAValueFromAddress_HL_IntoRegisterD)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_DHL);
	cpu.regs->D = 0x00;
	cpu.regs->HL = 0x0200;
	cpu.regs->pc = 0x100;
	cpu.mem->write_to_address(0x200, 0xAA);
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->D, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// ------------------- store in E ----------------
TEST_F(_8BitLoadTests, LDEBCanLoadAValueFromRegisterBIntoRegisterE)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_EB);
	cpu.regs->B = 0xAA;
	cpu.regs->E = 0x00;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->E, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDECCanLoadAValueFromRegisterCIntoRegisterE)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_EC);
	cpu.regs->C = 0xAA;
	cpu.regs->E = 0x00;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->E, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDEDCanLoadAValueFromRegisterDIntoRegisterE)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_ED);
	cpu.regs->D = 0xAA;
	cpu.regs->E = 0x00;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->E, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDEECanLoadAValueFromRegisterEIntoRegisterE)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_EE);
	cpu.regs->E = 0xAA;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->E, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDEHCanLoadAValueFromRegisterHIntoRegisterE)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_EH);
	cpu.regs->E = 0x00;
	cpu.regs->H = 0xAA;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->E, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDELCanLoadAValueFromRegisterLIntoRegisterE)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_EL);
	cpu.regs->E = 0x00;
	cpu.regs->L = 0xAA;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->E, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDEHLCanLoadAValueFromAddress_HL_IntoRegisterE)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_EHL);
	cpu.regs->E = 0x00;
	cpu.regs->HL = 0x0200;
	cpu.regs->pc = 0x100;
	cpu.mem->write_to_address(0x200, 0xAA);
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->E, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// ----------------- store in H ----------------
TEST_F(_8BitLoadTests, LDHBCanLoadAValueFromRegisterBIntoRegisterH)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_HB);
	cpu.regs->B = 0xAA;
	cpu.regs->H = 0x00;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->H, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDHCCanLoadAValueFromRegisterCIntoRegisterH)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_HC);
	cpu.regs->C = 0xAA;
	cpu.regs->H = 0x00;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->H, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDHDCanLoadAValueFromRegisterDIntoRegisterH)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_HD);
	cpu.regs->D = 0xAA;
	cpu.regs->H = 0x00;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->H, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDHECanLoadAValueFromRegisterEIntoRegisterH)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_HE);
	cpu.regs->E = 0xAA;
	cpu.regs->H = 0x00;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->H, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDHHCanLoadAValueFromRegisterHIntoRegisterH)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_HH);
	cpu.regs->H = 0xAA;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->H, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDHLCanLoadAValueFromRegisterLIntoRegisterH)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_HL);
	cpu.regs->H = 0x00;
	cpu.regs->L = 0xAA;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->H, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDHHLCanLoadAValueFromAddress_HL_IntoRegisterH)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_HHL);
	cpu.regs->H = 0x00;
	cpu.regs->HL = 0x0200;
	cpu.regs->pc = 0x100;
	cpu.mem->write_to_address(0x200, 0xAA);
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->H, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// ----------------- store in L ----------------
TEST_F(_8BitLoadTests, LDLBCanLoadAValueFromRegisterBIntoRegisterL)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_LB);
	cpu.regs->B = 0xAA;
	cpu.regs->L = 0x00;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->L, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDLCCanLoadAValueFromRegisterCIntoRegisterL)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_LC);
	cpu.regs->C = 0xAA;
	cpu.regs->L = 0x00;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->L, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDLDCanLoadAValueFromRegisterDIntoRegisterL)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_LD);
	cpu.regs->D = 0xAA;
	cpu.regs->L = 0x00;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->L, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDLECanLoadAValueFromRegisterEIntoRegisterL)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_LE);
	cpu.regs->E = 0xAA;
	cpu.regs->L = 0x00;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->L, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDLHCanLoadAValueFromRegisterHIntoRegisterL)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_LH);
	cpu.regs->H = 0xAA;
	cpu.regs->L = 0x00;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->L, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDLLCanLoadAValueFromRegisterLIntoRegisterL)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_LL);
	cpu.regs->L = 0xAA;
	cpu.regs->pc = 0x100;
	Byte expected_machine_cycles = 1;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->L, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDLHLCanLoadAValueFromAddress_HL_IntoRegisterL)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_LHL);
	cpu.regs->L = 0x00;
	cpu.regs->HL = 0x0200;
	cpu.regs->pc = 0x100;
	cpu.mem->write_to_address(0x200, 0xAA);
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->L, 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// ----------------- store at _HL_ ----------------
TEST_F(_8BitLoadTests, LDHLBCanLoadAValueFromRegisterBIntoAddressHL)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_HLB);
	cpu.regs->B = 0xAA;
	cpu.regs->HL = 0x0200;
	cpu.regs->pc = 0x100;
	cpu.mem->write_to_address(0x200, 0x00);
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDHLCCanLoadAValueFromRegisterCIntoAddressHL)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_HLC);
	cpu.regs->C = 0xAA;
	cpu.regs->HL = 0x0200;
	cpu.regs->pc = 0x100;
	cpu.mem->write_to_address(0x200, 0x00);
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDHLDCanLoadAValueFromRegisterDIntoAddressHL)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_HLD);
	cpu.regs->D = 0xAA;
	cpu.regs->HL = 0x0200;
	cpu.regs->pc = 0x100;
	cpu.mem->write_to_address(0x200, 0x00);
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDHLECanLoadAValueFromRegisterEIntoAddressHL)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_HLE);
	cpu.regs->E = 0xAA;
	cpu.regs->HL = 0x0200;
	cpu.regs->pc = 0x100;
	cpu.mem->write_to_address(0x200, 0x00);
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0xAA);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDHLHCanLoadAValueFromRegisterHIntoAddressHL)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_HLH);
	cpu.regs->HL = 0x0200;
	cpu.regs->pc = 0x100;
	cpu.mem->write_to_address(0x200, 0x00);
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x200), 0x02);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDHLLCanLoadAValueFromRegisterLIntoAddressHL)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LD_HLL);
	cpu.regs->HL = 0x0202;
	cpu.regs->pc = 0x100;
	cpu.mem->write_to_address(0x202, 0x00);
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x202), 0x02);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// --------------- store and decrement/increment --------------
TEST_F(_8BitLoadTests, LDD_A_HL_CanLoadAValueFromAddress_HL_IntoRegisterAAndDecrementHL)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LDD_A_HL_);
	cpu.regs->HL = 0x0201;
	cpu.regs->A = 0x00;
	cpu.regs->pc = 0x100;
	cpu.mem->write_to_address(0x201, 0xEE);
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0xEE);
	EXPECT_EQ(cpu.regs->HL, 0x200);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDD_HL_ACanLoadAValueFromRegisterAIntoAddress_HL_AndDecrementHL)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LDD_HL_A);
	cpu.regs->HL = 0x0201;
	cpu.regs->A = 0xEE;
	cpu.regs->pc = 0x100;
	cpu.mem->write_to_address(0x201, 0x00);
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x201), 0xEE);
	EXPECT_EQ(cpu.regs->HL, 0x200);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDI_A_HL_CanLoadAValueFromAddress_HL_IntoRegisterAAndIncrementHL)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LDI_A_HL_);
	cpu.regs->HL = 0x0201;
	cpu.regs->A = 0x00;
	cpu.regs->pc = 0x100;
	cpu.mem->write_to_address(0x201, 0xEE);
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0xEE);
	EXPECT_EQ(cpu.regs->HL, 0x202);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDI_HL_ACanLoadAValueFromRegisterAIntoAddress_HL_AndIncrementHL)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LDI_HL_A);
	cpu.regs->HL = 0x0201;
	cpu.regs->A = 0xEE;
	cpu.regs->pc = 0x100;
	cpu.mem->write_to_address(0x201, 0x00);
	Byte expected_machine_cycles = 2;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0x201), 0xEE);
	EXPECT_EQ(cpu.regs->HL, 0x202);
	EXPECT_EQ(cpu.regs->pc, 0x101);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

// --------------- store and load at 0xFF00 + n
TEST_F(_8BitLoadTests, LDH_nACanLoadAValueFromRegisterAIntoAddress_0xFF00_n)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LDH_nA);
	cpu.mem->write_to_address(0x101, 0xA0);
	cpu.regs->A = 0xEE;
	cpu.regs->pc = 0x100;
	cpu.mem->write_to_address(0xFFA0, 0x00);
	Byte expected_machine_cycles = 3;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.mem->read_from_address(0xFFA0), 0xEE);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}

TEST_F(_8BitLoadTests, LDH_AnCanLoadAValueFromAddress_0xFF00_nIntoRegisterA)
{
	// given
	cpu.mem->write_to_address(0x100, CPU::INS_LDH_An);
	cpu.mem->write_to_address(0x101, 0xA0);
	cpu.regs->A = 0x00;
	cpu.regs->pc = 0x100;
	cpu.mem->write_to_address(0xFFA0, 0xEE);
	Byte expected_machine_cycles = 3;
	// when
	Byte opcode = cpu.fetch_byte(false);
	cpu.execute(opcode, expected_machine_cycles);
	// then
	EXPECT_EQ(cpu.regs->A, 0xEE);
	EXPECT_EQ(cpu.regs->pc, 0x102);
	EXPECT_EQ(cpu.cycles->mc, expected_machine_cycles);
}
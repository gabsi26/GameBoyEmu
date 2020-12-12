#include "pch.h"
#include "../GameBoyEmu/GZ80.h"
#include "../GameBoyEmu/memory.h"
using namespace GZ80;
class HelperFunctionTests : public testing::Test
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

TEST_F(HelperFunctionTests, BitAddCanAdd1And0WithoutCarry)
{
	bool carry = 0;
	Bit result = cpu.bit_add(0b1, 0b0, carry);
	EXPECT_EQ(result, 0b1);
	EXPECT_EQ(carry, 0b0);
}

TEST_F(HelperFunctionTests, BitAddCanAdd1And0WithCarry)
{
	bool carry = 1;
	Bit result = cpu.bit_add(0b1, 0b0, carry);
	EXPECT_EQ(result, 0b0);
	EXPECT_EQ(carry, 0b1);
}

TEST_F(HelperFunctionTests, BitAddCanAdd1And1WithoutCarry)
{
	bool carry = 0;
	Bit result = cpu.bit_add(0b1, 0b1, carry);
	EXPECT_EQ(result, 0b0);
	EXPECT_EQ(carry, 0b1);
}

TEST_F(HelperFunctionTests, BitAddCanAdd1And1WithCarry)
{
	bool carry = 1;
	Bit result = cpu.bit_add(0b1, 0b1, carry);
	EXPECT_EQ(result, 0b1);
	EXPECT_EQ(carry, 0b1);
}

TEST_F(HelperFunctionTests, FourBitAddCanAdd1And1WithoutCarry)
{
	bool carry = 0;
	Byte result = cpu.four_bit_add(0b1, 0b1, carry);
	EXPECT_EQ(result, 0b10);
	EXPECT_EQ(carry, 0b0);
}

TEST_F(HelperFunctionTests, FourBitAddCanAdd1And1WithCarry)
{
	bool carry = 1;
	Byte result = cpu.four_bit_add(0b1, 0b1, carry);
	EXPECT_EQ(result, 0b11);
	EXPECT_EQ(carry, 0b0);
}

TEST_F(HelperFunctionTests, FourBitAddCanAdd15And1WithoutCarry)
{
	bool carry = 0;
	Byte result = cpu.four_bit_add(0xF, 0b1, carry);
	EXPECT_EQ(result, 0b0);
	EXPECT_EQ(carry, 0b1);
}

TEST_F(HelperFunctionTests, FourBitAddCanAdd15And1WithCarry)
{
	bool carry = 1;
	Byte result = cpu.four_bit_add(0xF, 0b1, carry);
	EXPECT_EQ(result, 0b1);
	EXPECT_EQ(carry, 0b1);
}

TEST_F(HelperFunctionTests, FourBitAddCanAdd15AndNegative1WithoutCarry)
{
	bool carry = 0;
	Byte result = cpu.four_bit_add(0xF, -1, carry);
	EXPECT_EQ(result, 0xE);
	EXPECT_EQ(carry, 0b1);
}

TEST_F(HelperFunctionTests, FourBitAddCanAdd15AndNegative1WithCarry)
{
	bool carry = 1;
	Byte result = cpu.four_bit_add(0xF, -1, carry);
	EXPECT_EQ(result, 0xF);
	EXPECT_EQ(carry, 0b1);
}

TEST_F(HelperFunctionTests, ByteAddCanAddFFAnd1WithoutCarry)
{
	bool carry = 0;
	bool half_carry = carry;
	Byte result = cpu.byte_add(0xFF, 1, carry, half_carry);
	EXPECT_EQ(result, 0x00);
	EXPECT_EQ(carry, 0b1);
	EXPECT_EQ(half_carry, 0b1);
}

TEST_F(HelperFunctionTests, ByteAddCanAdd0FAnd1WithoutCarry)
{
	bool carry = 0;
	bool half_carry = carry;
	Byte result = cpu.byte_add(0b00001111, 0b00000001, carry, half_carry);
	EXPECT_EQ(result, 0x10);
	EXPECT_EQ(carry, 0b0);
	EXPECT_EQ(half_carry, 0b1);
}

TEST_F(HelperFunctionTests, WordAddLowerFlagsCanAddFFFFAndFFWithoutCarry)
{
	bool carry = 0;
	bool half_carry = carry;
	Word result = cpu.word_add_lower_flags(0xFFFF, 0xFF, carry, half_carry);
	EXPECT_EQ(result, 0xFFFE);
	EXPECT_EQ(carry, 0b1);
	EXPECT_EQ(half_carry, 0b1);
}

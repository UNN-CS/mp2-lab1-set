#include "tbitfield.h"

#include <gtest/gtest.h>
TEST(TBitField, check_the_length)
{
	TBitField  sf();
	ASSERT_NO_THROW(TBitField sf(1));
}
TEST(TBitField,negative_length)
{
	TBitField  sf();
	ASSERT_ANY_THROW(TBitField sf(-1));
}
TEST(TBitField, bit_with_negative_index)
{
	TBitField sf(1);

	ASSERT_ANY_THROW(sf.ClrBit(-1));
}
TEST(TBitField, clear_bit_with_too_large_index)
{
	TBitField sf(1);

	ASSERT_ANY_THROW(sf.ClrBit(2));
}
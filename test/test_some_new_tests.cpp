#include "tset.h"

#include <gtest.h>

TEST(MyTest, is_after_double_delete_bit_stay_zero)
{
	TBitField bField(10);
	bField.ClrBit(9);
	bField.ClrBit(9);
	EXPECT_EQ(bField.GetBit(9), 0);
}

TEST(MyTest, is_after_muliple_OR_return_correct_velue)
{
	TBitField b1(10);
	TBitField b2(9);
	TBitField b3(8);
	TBitField bCorrect(10);
	b1.SetBit(0);
	b2.SetBit(1);
	b3.SetBit(2);

	bCorrect.SetBit(0);
	bCorrect.SetBit(1);
	bCorrect.SetBit(2);

	EXPECT_EQ(b1 | b2 | b3, bCorrect);

}

TEST(MyTest, is_after_muliple_PLUS_return_correct_velue)
{
	
	TSet s1(10);
	TSet s2(9);
	TSet s3(8);
	TSet sCorrect(10);

	s1.InsElem(0);
	s2.InsElem(1);
	s3.InsElem(3);

	sCorrect.InsElem(0);
	sCorrect.InsElem(1);
	sCorrect.InsElem(3);

	EXPECT_EQ(s1 + s2 + s3, sCorrect);
}



#include "tset.h"
#include <gtest.h>

TEST(TBitField, MY_TEST_double_clear_bit)
{
	TBitField bf(1);

	bf.SetBit(0);

	bf.ClrBit(0);
	bf.ClrBit(0);

	EXPECT_EQ(0, bf.GetBit(0));
}

TEST(TBitField, MY_TEST_or_operator_applied_to_three_bitfields_of_equal_size)
{
	const int size = 3;
	TBitField bf1(size), bf2(size), bf3(size), expBf(size);
	//bf1 = 001
	bf1.SetBit(0);
	//bf2 = 010
	bf2.SetBit(1);
	//bf3 = 100
	bf3.SetBit(2);
	//expBf = 111
	expBf.SetBit(0);
	expBf.SetBit(1);
	expBf.SetBit(2);

	EXPECT_EQ(expBf, bf1 | bf2 | bf3);
}

TEST(TBitField, MY_TEST_or_operator_applied_to_three_bitfields_of_non_equal_size)
{
	TBitField bf1(1), bf2(2), bf3(3), expBf(3);
	//bf1 = 1
	bf1.SetBit(0);
	//bf2 = 10
	bf2.SetBit(1);
	//bf3 = 100
	bf3.SetBit(2);
	//expBf = 111
	expBf.SetBit(0);
	expBf.SetBit(1);
	expBf.SetBit(2);

	EXPECT_EQ(expBf, bf1 | bf2 | bf3);
}

TEST(TSet, MY_TEST_can_intersect_three_sets_of_equal_size)
{
	const int size = 3;
	TSet set1(size), set2(size), set3(size), expSet(size);
	//set1 = 001
	set1.InsElem(0);
	//set2 = 010
	set2.InsElem(1);
	//setf3 = 100
	set3.InsElem(2);
	//expSet = 000
	expSet.DelElem(0);
	expSet.DelElem(1);
	expSet.DelElem(2);

	EXPECT_EQ(expSet, set1 * set2 * set3);
}

TEST(TSet, MY_TEST_can_intersect_three_sets_of_non_equal_size)
{
	TSet set1(1), set2(2), set3(3), expSet(3);
	//bf1 = 1
	set1.InsElem(0);
	//bf2 = 10
	set2.InsElem(1);
	//bf3 = 100
	set3.InsElem(2);
	//expBf = 000
	expSet.DelElem(0);
	expSet.DelElem(1);
	expSet.DelElem(2);

	EXPECT_EQ(expSet, set1 * set2 * set3);
}
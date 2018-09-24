#include "tbitfield.h"
#include "tset.h"
#include <gtest.h>

TEST(TBitField, or_operators_applied_to_three_bitfields_of_non_equal_size_MY_TEST)
{
	const int size1 = 5, size2 = 6, size3 = 7, size4 = 7;
	TBitField bf1(size1), bf2(size2), bf3(size3), expBf(size4);
	//bf1 = 10010
	bf1.SetBit(0);
	bf1.SetBit(3);
	//bf2 = 110001
	bf2.SetBit(0);
	bf2.SetBit(1);
	bf2.SetBit(5);
	//bf3 = 0000100
	bf3.SetBit(4);
	//expBf = 1101110
	expBf.SetBit(0);
	expBf.SetBit(1);
	expBf.SetBit(3);
	expBf.SetBit(4);
	expBf.SetBit(5);
	EXPECT_EQ(expBf, bf1 | bf2 | bf3);
}

TEST(TBitField, and_operators_applied_to_three_bitfields_of_non_equal_size_MY_TEST)
{
	const int size1 = 5, size2 = 6, size3 = 7, size4 = 7;
	TBitField bf1(size1), bf2(size2), bf3(size3), expBf(size4);
	//bf1 = 10010
	bf1.SetBit(0);
	bf1.SetBit(3);
	//bf2 = 110001
	bf2.SetBit(0);
	bf2.SetBit(1);
	bf2.SetBit(5);
	//bf3 = 1010100
	bf3.SetBit(0);
	bf3.SetBit(2);
	bf3.SetBit(4);
	//expBf = 1000000
	expBf.SetBit(0);
	EXPECT_EQ(expBf, bf1 & bf2 & bf3);
}

TEST(TSet, can_combine_three_sets_with_non_equal_size_MY_TEST)
{
	const int size1 = 5, size2 = 7, size3 = 8, size4 = 8;
	TSet set1(size1), set2(size2), set3(size3), expSet(size4);
	//set1 = {1, 2, 3}
	set1.InsElem(1);
	set1.InsElem(3);
	set1.InsElem(3);
	//set2 = {1, 6}
	set2.InsElem(1);
	set2.InsElem(6);
	//set3 = {2, 3, 6, 7}
	set3.InsElem(2);
	set3.InsElem(3);
	set3.InsElem(6);
	set3.InsElem(7);
	//expSet = {1, 2, 3, 6, 7}
	expSet.InsElem(1);
	expSet.InsElem(2);
	expSet.InsElem(3);
	expSet.InsElem(6);
	expSet.InsElem(7);
	EXPECT_EQ(expSet, set1 + set2 + set3);
}

TEST(TSet, throws_when_insert_non_existing_element_out_of_range_MY_TEST)
{
	const int size = 5;
	TSet Set(size);
	EXPECT_ANY_THROW(Set.InsElem(5));
}
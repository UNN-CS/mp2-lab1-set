#include <gtest.h>
#include <stdio.h>

#include "tbitfield.h"
#include "tset.h"

#include <gtest.h>

TEST(TSet, can_get_max_power_set)
{
	const int size = 5;
	TSet set(size);

	EXPECT_EQ(size, set.GetMaxPower());
}

TEST(TSet, can_insert_non_existing_element)
{
	const int size = 5, k = 3;
	TSet set(size);
	set.InsElem(k);

	EXPECT_NE(set.IsMember(k), 0);
}

TEST(TSet, can_insert_existing_element)
{
	const int size = 5;
	const int k = 3;
	TSet set(size);
	set.InsElem(k);
	set.InsElem(k);

	EXPECT_NE(set.IsMember(k), 0);
}

TEST(TSet, can_delete_non_existing_element)
{
	const int size = 5, k = 3;
	TSet set(size);
	set.DelElem(k);

	EXPECT_EQ(set.IsMember(k), 0);
}

TEST(TSet, can_delete_existing_element)
{
	const int size = 5, k = 3;
	TSet set(size);

	set.InsElem(k);
	EXPECT_GT(set.IsMember(k), 0);

	set.DelElem(k);
	EXPECT_EQ(set.IsMember(k), 0);
}

TEST(TSet, compare_two_sets_of_non_equal_sizes)
{
	const int size1 = 4, size2 = 6;
	TSet set1(size1), set2(size2);

	EXPECT_EQ(1, set1 != set2);
}

TEST(TSet, compare_two_equal_sets)
{
	const int size = 4;
	TSet set1(size), set2(size);
	// set1 = set2 = {1, 3}
	set1.InsElem(1);
	set1.InsElem(3);
	set2.InsElem(1);
	set2.InsElem(3);

	EXPECT_EQ(set1, set2);
}

TEST(TSet, compare_two_non_equal_sets)
{
	const int size = 4;
	TSet set1(size), set2(size);
	// set1 = {1, 3}
	set1.InsElem(1);
	set1.InsElem(3);
	// set2 = {1, 2}
	set2.InsElem(1);
	set2.InsElem(2);

	EXPECT_EQ(1, set1 != set2);
}

TEST(TSet, can_assign_set_of_equal_size)
{
	const int size = 4;
	TSet set1(size), set2(size);
	// set1 = {1, 3}
	set1.InsElem(1);
	set1.InsElem(3);
	set2 = set1;

	EXPECT_EQ(set1, set2);
}

TEST(TSet, can_assign_set_of_greater_size)
{
	const int size1 = 4, size2 = 6;
	TSet set1(size1), set2(size2);
	// set1 = {1, 3}
	set1.InsElem(1);
	set1.InsElem(3);
	set2 = set1;

	EXPECT_EQ(set1, set2);
}

TEST(TSet, can_assign_set_of_less_size)
{
	const int size1 = 6, size2 = 4;
	TSet set1(size1), set2(size2);
	// set1 = {1, 3, 5}
	set1.InsElem(1);
	set1.InsElem(3);
	set1.InsElem(5);
	set2 = set1;

	EXPECT_EQ(set1, set2);
}

TEST(TSet, can_insert_non_existing_element_using_plus_operator)
{
	const int size = 4;
	const int k = 3;
	TSet set(size), updatedSet(size);
	set.InsElem(0);
	set.InsElem(2);
	updatedSet = set + k;

	EXPECT_NE(0, updatedSet.IsMember(k));
}

TEST(TSet, throws_when_insert_non_existing_element_out_of_range_using_plus_operator)
{
	const int size = 4;
	const int k = 6;
	TSet set(size), updatedSet(size);
	set.InsElem(0);
	set.InsElem(2);

	ASSERT_ANY_THROW(updatedSet = set + k);
}

TEST(TSet, can_insert_existing_element_using_plus_operator)
{
	const int size = 4;
	const int k = 3;
	TSet set(size), updatedSet(size);
	set.InsElem(0);
	set.InsElem(k);
	updatedSet = set + k;

	EXPECT_NE(0, set.IsMember(k));
}

TEST(TSet, check_size_of_the_combination_of_two_sets_of_equal_size)
{
	const int size = 5;
	TSet set1(size), set2(size), set3(size);
	// set1 = {1, 2, 4}
	set1.InsElem(1);
	set1.InsElem(2);
	set1.InsElem(4);
	// set2 = {0, 1, 2}
	set2.InsElem(0);
	set2.InsElem(1);
	set2.InsElem(2);
	set3 = set1 + set2;

	EXPECT_EQ(size, set3.GetMaxPower());
}

TEST(TSet, can_combine_two_sets_of_equal_size)
{
	const int size = 5;
	TSet set1(size), set2(size), set3(size), expSet(size);
	// set1 = {1, 2, 4}
	set1.InsElem(1);
	set1.InsElem(2);
	set1.InsElem(4);
	// set2 = {0, 1, 2}
	set2.InsElem(0);
	set2.InsElem(1);
	set2.InsElem(2);
	set3 = set1 + set2;
	// expSet = {0, 1, 2, 4}
	expSet.InsElem(0);
	expSet.InsElem(1);
	expSet.InsElem(2);
	expSet.InsElem(4);

	EXPECT_EQ(expSet, set3);
}

TEST(TSet, check_size_changes_of_the_combination_of_two_sets_of_non_equal_size)
{
	const int size1 = 5, size2 = 7;
	TSet set1(size1), set2(size2), set3(size1);
	// set1 = {1, 2, 4}
	set1.InsElem(1);
	set1.InsElem(2);
	set1.InsElem(4);
	// set2 = {0, 1, 2}
	set2.InsElem(0);
	set2.InsElem(1);
	set2.InsElem(2);
	set3 = set1 + set2;

	EXPECT_EQ(size2, set3.GetMaxPower());
}

TEST(TSet, can_combine_two_sets_of_non_equal_size)
{
	const int size1 = 5, size2 = 7;
	TSet set1(size1), set2(size2), set3(size1), expSet(size2);
	// set1 = {1, 2, 4}
	set1.InsElem(1);
	set1.InsElem(2);
	set1.InsElem(4);
	// set2 = {0, 1, 2, 6}
	set2.InsElem(0);
	set2.InsElem(1);
	set2.InsElem(2);
	set2.InsElem(6);
	set3 = set1 + set2;
	// expSet = {0, 1, 2, 4, 6}
	expSet.InsElem(0);
	expSet.InsElem(1);
	expSet.InsElem(2);
	expSet.InsElem(4);
	expSet.InsElem(6);

	EXPECT_EQ(expSet, set3);
}

TEST(TSet, can_intersect_two_sets_of_equal_size)
{
	const int size = 5;
	TSet set1(size), set2(size), set3(size), expSet(size);
	// set1 = {1, 2, 4}
	set1.InsElem(1);
	set1.InsElem(2);
	set1.InsElem(4);
	// set2 = {0, 1, 2}
	set2.InsElem(0);
	set2.InsElem(1);
	set2.InsElem(2);
	set3 = set1 * set2;
	// expSet = {1, 2}
	expSet.InsElem(1);
	expSet.InsElem(2);

	EXPECT_EQ(expSet, set3);
}

TEST(TSet, can_intersect_two_sets_of_non_equal_size)
{
	const int size1 = 5, size2 = 7;
	TSet set1(size1), set2(size2), set3(size1), expSet(size2);
	// set1 = {1, 2, 4}
	set1.InsElem(1);
	set1.InsElem(2);
	set1.InsElem(4);
	// set2 = {0, 1, 2, 4, 6}
	set2.InsElem(0);
	set2.InsElem(1);
	set2.InsElem(2);
	set2.InsElem(4);
	set2.InsElem(6);
	set3 = set1 * set2;
	// expSet = {1, 2, 4}
	expSet.InsElem(1);
	expSet.InsElem(2);
	expSet.InsElem(4);

	EXPECT_EQ(expSet, set3);
}

TEST(TSet, check_negation_operator)
{
	const int size = 4;
	TSet set(size), set1(size), expSet(size);
	// set1 = {1, 3}
	set.InsElem(1);
	set.InsElem(3);
	set1 = ~set;
	// expSet = {0, 2}
	expSet.InsElem(0);
	expSet.InsElem(2);

	EXPECT_EQ(expSet, set1);
}


TEST(TBitField, can_create_bitfield_with_positive_length)
{
	ASSERT_NO_THROW(TBitField bf(3));
}

TEST(TBitField, can_get_length)
{
	TBitField bf(3);

	EXPECT_EQ(3, bf.GetLength());
}

TEST(TBitField, new_bitfield_is_set_to_zero)
{
	TBitField bf(100);

	int sum = 0;
	for (int i = 0; i < bf.GetLength(); i++)
	{
		sum += bf.GetBit(i);
	}

	EXPECT_EQ(0, sum);
}

TEST(TBitField, can_set_bit)
{
	TBitField bf(10);

	EXPECT_EQ(0, bf.GetBit(3));

	bf.SetBit(3);
	EXPECT_NE(0, bf.GetBit(3));
}

TEST(TBitField, can_clear_bit)
{
	TBitField bf(10);

	int bitIdx = 3;

	bf.SetBit(bitIdx);
	EXPECT_NE(0, bf.GetBit(bitIdx));

	bf.ClrBit(bitIdx);
	EXPECT_EQ(0, bf.GetBit(bitIdx));
}

TEST(TBitField, throws_when_create_bitfield_with_negative_length)
{
	ASSERT_ANY_THROW(TBitField bf(-3));
}

TEST(TBitField, throws_when_set_bit_with_negative_index)
{
	TBitField bf(10);

	ASSERT_ANY_THROW(bf.SetBit(-3));
}

TEST(TBitField, throws_when_set_bit_with_too_large_index)
{
	TBitField bf(10);

	ASSERT_ANY_THROW(bf.SetBit(11));
}

TEST(TBitField, throws_when_get_bit_with_negative_index)
{
	TBitField bf(10);

	ASSERT_ANY_THROW(bf.GetBit(-3));
}

TEST(TBitField, throws_when_get_bit_with_too_large_index)
{
	TBitField bf(10);

	ASSERT_ANY_THROW(bf.GetBit(11));
}

TEST(TBitField, throws_when_clear_bit_with_negative_index)
{
	TBitField bf(10);

	ASSERT_ANY_THROW(bf.ClrBit(-3));
}

TEST(TBitField, throws_when_clear_bit_with_too_large_index)
{
	TBitField bf(10);

	ASSERT_ANY_THROW(bf.ClrBit(11));
}

TEST(TBitField, can_assign_bitfields_of_equal_size)
{
	const int size = 2;
	TBitField bf1(size), bf2(size);
	for (int i = 0; i < size; i++)
	{
		bf1.SetBit(i);
	}
	bf2 = bf1;

	EXPECT_NE(0, bf2.GetBit(0));
	EXPECT_NE(0, bf2.GetBit(1));
}

TEST(TBitField, assign_operator_changes_bitfield_size)
{
	const int size1 = 2, size2 = 5;
	TBitField bf1(size1), bf2(size2);
	for (int i = 0; i < size1; i++)
	{
		bf1.SetBit(i);
	}
	bf2 = bf1;

	EXPECT_EQ(2, bf2.GetLength());
}

TEST(TBitField, can_assign_bitfields_of_non_equal_size)
{
	const int size1 = 2, size2 = 5;
	TBitField bf1(size1), bf2(size2);
	for (int i = 0; i < size1; i++)
	{
		bf1.SetBit(i);
	}
	bf2 = bf1;

	EXPECT_NE(0, bf2.GetBit(0));
	EXPECT_NE(0, bf2.GetBit(1));
}

TEST(TBitField, compare_equal_bitfields_of_equal_size)
{
	const int size = 2;
	TBitField bf1(size), bf2(size);
	for (int i = 0; i < size; i++)
	{
		bf1.SetBit(i);
	}
	bf2 = bf1;

	EXPECT_EQ(bf1, bf2);
}

TEST(TBitField, or_operator_applied_to_bitfields_of_equal_size)
{
	const int size = 4;
	TBitField bf1(size), bf2(size), expBf(size);
	// bf1 = 0011
	bf1.SetBit(2);
	bf1.SetBit(3);
	// bf2 = 0101
	bf2.SetBit(1);
	bf2.SetBit(3);

	// expBf = 0111
	expBf.SetBit(1);
	expBf.SetBit(2);
	expBf.SetBit(3);

	EXPECT_EQ(expBf, bf1 | bf2);
}

TEST(TBitField, or_operator_applied_to_bitfields_of_non_equal_size)
{
	const int size1 = 4, size2 = 5;
	TBitField bf1(size1), bf2(size2), expBf(size2);
	// bf1 = 0011
	bf1.SetBit(2);
	bf1.SetBit(3);
	// bf2 = 01010
	bf2.SetBit(1);
	bf2.SetBit(3);

	// expBf = 01110
	expBf.SetBit(1);
	expBf.SetBit(2);
	expBf.SetBit(3);

	EXPECT_EQ(expBf, bf1 | bf2);
}

TEST(TBitField, and_operator_applied_to_bitfields_of_equal_size)
{
	const int size = 4;
	TBitField bf1(size), bf2(size), expBf(size);
	// bf1 = 0011
	bf1.SetBit(2);
	bf1.SetBit(3);
	// bf2 = 0101
	bf2.SetBit(1);
	bf2.SetBit(3);

	// expBf = 0001
	expBf.SetBit(3);

	EXPECT_EQ(expBf, bf1 & bf2);
}

TEST(TBitField, and_operator_applied_to_bitfields_of_non_equal_size)
{
	const int size1 = 4, size2 = 5;
	TBitField bf1(size1), bf2(size2), expBf(size2);
	// bf1 = 0011
	bf1.SetBit(2);
	bf1.SetBit(3);
	// bf2 = 01010
	bf2.SetBit(1);
	bf2.SetBit(3);

	// expBf = 00010
	expBf.SetBit(3);

	EXPECT_EQ(expBf, bf1 & bf2);
}

TEST(TBitField, can_invert_bitfield)
{
	const int size = 2;
	TBitField bf(size), negBf(size), expNegBf(size);
	// bf = 01
	bf.SetBit(1);
	negBf = ~bf;

	// expNegBf = 10
	expNegBf.SetBit(0);

	EXPECT_EQ(expNegBf, negBf);
}

TEST(TBitField, can_invert_large_bitfield)
{
	const int size = 38;
	TBitField bf(size), negBf(size), expNegBf(size);
	bf.SetBit(35);
	negBf = ~bf;

	for (int i = 0; i < size; i++)
		expNegBf.SetBit(i);
	expNegBf.ClrBit(35);

	EXPECT_EQ(expNegBf, negBf);
}

TEST(TBitField, invert_plus_and_operator_on_different_size_bitfield)
{
	const int firstSze = 4, secondSize = 8;
	TBitField firstBf(firstSze), negFirstBf(firstSze), secondBf(secondSize), testBf(secondSize);
	// firstBf = 0001
	firstBf.SetBit(0);
	negFirstBf = ~firstBf;
	// negFirstBf = 1110

	// secondBf = 00011000
	secondBf.SetBit(3);
	secondBf.SetBit(4);

	// testBf = 00001000
	testBf.SetBit(3);

	EXPECT_EQ(secondBf & negFirstBf, testBf);
}

TEST(TBitField, can_invert_many_random_bits_bitfield)
{
	const int size = 38;
	TBitField bf(size), negBf(size), expNegBf(size);

	std::vector<int> bits;
	bits.push_back(0);
	bits.push_back(1);
	bits.push_back(14);
	bits.push_back(16);
	bits.push_back(33);
	bits.push_back(37);

	for (unsigned int i = 0; i < bits.size(); i++)
		bf.SetBit(bits[i]);

	negBf = ~bf;

	for (int i = 0; i < size; i++)
		expNegBf.SetBit(i);
	for (unsigned int i = 0; i < bits.size(); i++)
		expNegBf.ClrBit(bits[i]);

	EXPECT_EQ(expNegBf, negBf);
}

TEST(TBitField, bitfields_with_different_bits_are_not_equal)
{
	const int size = 4;
	TBitField bf1(size), bf2(size);

	bf1.SetBit(1);
	bf1.SetBit(3);

	bf2.SetBit(1);
	bf2.SetBit(2);

	EXPECT_NE(bf1, bf2);
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
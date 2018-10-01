#include <tset.h>
#include <tbitfield.h>
#include <gtest/gtest.h>

TEST(TBitField, inverted_different_size_bitfields_not_equal)
{
  TBitField firstBF(4), secondBF(3), negFirstBF(4);

  firstBF.SetBit(0);
  firstBF.SetBit(1);          //First BF: 0011

  secondBF.SetBit(0);
  secondBF.SetBit(1);         //Second BF: 011

  EXPECT_EQ(firstBF, secondBF);

  negFirstBF = ~firstBF;

  EXPECT_NE(negFirstBF, secondBF);
}

TEST(TSet, operator_diff_on_two_not_equal_sets_dont_makes_equal)
{
  TSet firstSet(6), secondSet(5);

  firstSet.InsElem(3);
  firstSet.InsElem(4);
  firstSet.InsElem(5);
  firstSet.InsElem(6);

  secondSet.InsElem(3);
  secondSet.InsElem(4);
  secondSet.InsElem(5);

  firstSet = firstSet - 6;

  EXPECT_NE(firstSet, secondSet);
}

TEST(TSet, fun_test)
{
  TSet funSet(20), negFunSet(20);

  for (int i = 1; i <= 20; i++)
    funSet.InsElem(i);

  negFunSet = ~funSet;

  EXPECT_NE(negFunSet, funSet);
}
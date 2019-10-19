#include "tbitfield.h"
#include "tset.h"

#include <gtest.h>
#include <cmath>

TEST(Additional, check_arithmetic) {
    EXPECT_EQ(1+3+5+7+9+11, pow(6,2));
}

TEST(Additional, double_clear_sets_to_zero) {
    TBitField bitField(1);
    
    bitField.SetBit(0);
    bitField.ClrBit(0);
    bitField.ClrBit(0);

    EXPECT_EQ(0, bitField.GetBit(0));
}

TEST(Additional, bitfield_double_disjunction) {
    TBitField bf1(4);
    TBitField bf2(4);
    TBitField bf3(4);
    TBitField expBf(4);

    bf1.SetBit(0);
    bf1.SetBit(1);
    
    bf2.SetBit(1);
    bf2.SetBit(2);

    bf3.SetBit(2);
    bf3.SetBit(3);

    expBf = ~expBf;

    EXPECT_EQ(expBf, bf1 | bf2 | bf3);
}

TEST(Additional, set_double_disjunction) {
    TSet s1(4);
    TSet s2(4);
    TSet s3(4);
    TSet expSet(4);

    s1.InsElem(0);
    s1.InsElem(1);

    s2.InsElem(1);
    s2.InsElem(2);

    s3.InsElem(2);
    s3.InsElem(3);

    expSet = ~expSet;

    EXPECT_EQ(expSet, s1 + s2 + s3);
}

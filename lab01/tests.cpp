#include "gtest/gtest.h"
#include "Tritset.h"

using testing::Eq;



TEST(TritSetTest, CapacityTest)
{
    int n = 1000;
    Tritset set(n);
    size_t allocLength = set.capacity();

    // n*2 - min bits count
    // n*2 / 8 - min bytes count
    // n*2 / 8 / sizeof(uint) - min uint[] size
    ASSERT_GE(allocLength, (n*2 / 8 / sizeof(uint)));
}

TEST(TritSetTest, NoAllocTest)
{
    int n = 1000;
    Tritset set(n);
    unsigned int allocLength = set.capacity();
    set[1000000] = trit::tUnknown;
    ASSERT_EQ(allocLength, set.capacity());
//    ASSERT_EQ(set[1000000], trit::tUnknown);
//    if (set[1000000] == trit::tUnknown) {
//        exit(1);
//    }
    EXPECT_TRUE(set[1000000] == trit::tUnknown);
}

TEST(TritSetTest, AllocTest)
{
    int n = 1000;
    Tritset set(n);
    size_t allocLength = set.capacity();
    set[1000000000] = trit::tTrue;
    ASSERT_LT(allocLength, set.capacity());
    EXPECT_TRUE(set[1000000000] == trit::tTrue);
}

TEST(TritSetTest, ShrinkTest)
{
    int n = 1000;
    Tritset set(n);
    set[1000000000] = trit::tTrue;
    size_t allocLength = set.capacity();
    set.shrink();
    EXPECT_TRUE(allocLength == set.capacity());
}

TEST(TritSetTest, ANDTest)
{
    Tritset setA(1000);
    Tritset setB(2000);
    Tritset setC = setA & setB;
    ASSERT_EQ(setC.capacity(), setB.capacity());
}

TEST(TritSetTest, TrueCardinalityTest)
{
    Tritset set(1000);
    set[2] = trit::tTrue;
    ASSERT_EQ(set.cardinality(trit::tTrue), 1);
}

TEST(TritSetTest, TrueCardinalityTest2)
{
    Tritset set(1000);
    set[1] = trit::tFalse;
    set[2] = trit::tFalse;
    set[3] = trit::tTrue;
    ASSERT_EQ(set.cardinality(trit::tTrue), 1);
}

TEST(TritSetTest, UnknownCardinalityTest)
{
    Tritset set(1000);
    set[2] = trit::tTrue;
    ASSERT_EQ(set.cardinality(trit::tUnknown), 2);
}

TEST(TritSetTest, TrimTest)
{
    Tritset set(1000);
    set[1] = trit::tFalse;
    set[2] = trit::tFalse;
    set[3] = trit::tTrue;
    set.trim(2);
    EXPECT_TRUE(set[2] == trit::tFalse);
    EXPECT_TRUE(set[3] == trit::tUnknown);
}

TEST(TritSetTest, LengthTest)
{
    Tritset set(1000);
    set[1] = trit::tFalse;
    set[2] = trit::tFalse;
    set[3] = trit::tTrue;
    ASSERT_EQ(set.length(), 4);
}

#include "gtest/gtest.h"
#include "../Tritset.h"

using testing::Eq;


TEST(FirstTest, part0) {
    //резерв памяти для хранения 1000 тритов
    Tritset set(1000);
    // length of internal array
    size_t allocLength = set.capacity();
    EXPECT_TRUE(allocLength >= 1000 * 2 / 8 / sizeof(uint));
    // 1000*2 - min bits count
    // 1000*2 / 8 - min bytes count
    // 1000*2 / 8 / sizeof(uint) - min uint[] size

    //не выделяет никакой памяти
    set[1000000000] = trit::tUnknown;
    EXPECT_TRUE(allocLength == set.capacity());

    // false, but no exception or memory allocation
    if (set[2000000000] == trit::tTrue) {}
    EXPECT_TRUE(allocLength == set.capacity());

    //выделение памяти
    set[1000000000] = trit::tTrue;
    EXPECT_TRUE(allocLength < set.capacity());

    //no memory operations
    allocLength = set.capacity();
    set[1000000000] = trit::tUnknown;
    set[1000000] = trit::tFalse;
    EXPECT_TRUE(allocLength == set.capacity());

    //освобождение памяти до начального значения или
    //до значения необходимого для хранения последнего установленного трита
    //в данном случае для трита 1000’000
    set.shrink();
    EXPECT_TRUE(allocLength > set.capacity());

    Tritset setA(1000);
    Tritset setB(2000);
    Tritset setC = setA & setB;
    EXPECT_TRUE(setC.capacity() == setB.capacity());
}

TEST(Trim, part0) {
    Tritset set(1000);
    set[1] = trit::tFalse;
    set[2] = trit::tFalse;
    set[3] = trit::tTrue;
    set.trim(2);
    EXPECT_TRUE(set[1] == trit::tFalse);
    EXPECT_TRUE(set[2] == trit::tUnknown);
    EXPECT_TRUE(set[3] == trit::tUnknown);
}

TEST(Trim, part1) {
    Tritset set;

    for (uint i = 0; i < 100; i++) {
        set[i] = trit::tTrue;
    }
    for (uint i = 60; i < 80; i++) {
        set[i] = trit::tUnknown;
    }
    set.trim(80);
    for (uint i = 0; i < 60; i++) {
        EXPECT_TRUE(set[i] == trit::tTrue);
    }
    for (uint i = 60; i < 100; i++) {
        EXPECT_TRUE(set[i] == trit::tUnknown);
    }
    EXPECT_TRUE(set.length() < 101);
}

TEST(Trim, part2) {
    Tritset set;

    for (uint i = 0; i < 80; i++) {
        set[i] = trit::tTrue;
    }

    set.trim(90);
    for (uint i = 0; i < 80; i++) {
        EXPECT_TRUE(set[i] == trit::tTrue);
    }
    EXPECT_TRUE(set.length() == 80);
}

TEST(Shrink, part0) {
    int n = 10;
    Tritset set(n);
    set[1000000] = trit::tTrue;
    size_t allocLength = set.capacity();
    set.shrink();
    EXPECT_TRUE(allocLength == set.capacity());
}

TEST(Shrink, part1) {
    Tritset set(100);

    for (uint i = 0; i < 70; i++) {
        set[i] = trit::tTrue;
    }
    set.shrink();

    for (uint i = 0; i < 70; i++) {
        EXPECT_TRUE(set[i] == trit::tTrue);
    }
    uint tritAmount = set.length();
    EXPECT_TRUE(tritAmount == 70);
}

TEST(Shrink, part2) {
    Tritset set(100);

    for (uint i = 0; i < 70; i++) {
        set[i] = trit::tTrue;
    }
    uint n = set.length();
    for (uint i = 50; i < 70; i++) {
        set[i] = trit::tUnknown;
    }
    uint m = set.length();
    set.shrink();

    for (uint i = 0; i < 50; i++) {
        EXPECT_TRUE(set[i] == trit::tTrue);
    }
    for (uint i = 50; i < 70; i++) {
        EXPECT_TRUE(set[i] == trit::tUnknown);
    }
    EXPECT_TRUE(n == 70);
    EXPECT_TRUE(n - 20 == m);
    EXPECT_TRUE(m == set.length());
}

TEST(Cardinality, part0) {
    Tritset set;
    set[22] = trit::tFalse;
    set[19] = trit::tTrue;
    set[18] = trit::tTrue;
    set[16] = trit::tFalse;
    set[14] = trit::tTrue;
    set[13] = trit::tTrue;
    set[12] = trit::tTrue;
    set[9] = trit::tFalse;
    set[8] = trit::tFalse;
    set[7] = trit::tFalse;
    set[5] = trit::tTrue;
    set[4] = trit::tTrue;
    set[3] = trit::tFalse;
    set[2] = trit::tFalse;
    set[0] = trit::tTrue;

    EXPECT_TRUE(set[22] == trit::tFalse);
    EXPECT_TRUE(set[16] == trit::tFalse);
    EXPECT_TRUE(set[9] == trit::tFalse);
    EXPECT_TRUE(set[8] == trit::tFalse);
    EXPECT_TRUE(set[7] == trit::tFalse);
    EXPECT_TRUE(set[3] == trit::tFalse);
    EXPECT_TRUE(set[2] == trit::tFalse);

    EXPECT_TRUE(set[19] == trit::tTrue);
    EXPECT_TRUE(set[18] == trit::tTrue);
    EXPECT_TRUE(set[14] == trit::tTrue);
    EXPECT_TRUE(set[13] == trit::tTrue);
    EXPECT_TRUE(set[12] == trit::tTrue);
    EXPECT_TRUE(set[4] == trit::tTrue);
    EXPECT_TRUE(set[5] == trit::tTrue);
    EXPECT_TRUE(set[0] == trit::tTrue);

    EXPECT_TRUE(set[1] == trit::tUnknown);
    EXPECT_TRUE(set[6] == trit::tUnknown);
    EXPECT_TRUE(set[10] == trit::tUnknown);
    EXPECT_TRUE(set[11] == trit::tUnknown);
    EXPECT_TRUE(set[15] == trit::tUnknown);
    EXPECT_TRUE(set[17] == trit::tUnknown);
    EXPECT_TRUE(set[20] == trit::tUnknown);
    EXPECT_TRUE(set[21] == trit::tUnknown);

    EXPECT_TRUE(set.cardinality(trit::tFalse) == 7);
    EXPECT_TRUE(set.cardinality(trit::tUnknown) == 8);
    EXPECT_TRUE(set.cardinality(trit::tTrue) == 8);
}

TEST(MapCardinality, part0) {
    Tritset set;
    set[0] = trit::tTrue;
    set[2] = trit::tFalse;
    set[3] = trit::tFalse;
    set[4] = trit::tTrue;
    set[5] = trit::tTrue;
    set[7] = trit::tFalse;
    set[8] = trit::tFalse;
    set[9] = trit::tFalse;
    set[12] = trit::tTrue;
    set[13] = trit::tTrue;
    set[14] = trit::tTrue;
    set[16] = trit::tFalse;
    set[18] = trit::tTrue;
    set[19] = trit::tTrue;
    set[22] = trit::tFalse;

    std::unordered_map<trit, int> count = set.cardinality();

    EXPECT_TRUE(count[trit::tFalse] == 7);
    EXPECT_TRUE(count[trit::tUnknown] == 8);
    EXPECT_TRUE(count[trit::tTrue] == 8);

}

TEST(Constructor, Constructor) {
    Tritset set(1000);

    for (uint i = 0; i < 30; i++) {
        set[i] = static_cast<trit>(i % 3);
    }
    for (uint i = 600; i < 800; i++) {
        set[i] = trit::tFalse;
    }
    for (uint i = 800; i < 1000; i++) {
        set[i] = trit::tTrue;
    }

    for (uint i = 0; i < 30; i++) {
        EXPECT_TRUE(set[i] == static_cast<trit>(i % 3));
    }
    for (uint i = 30; i < 600; i++) {
        EXPECT_TRUE(set[i] == trit::tUnknown);
    }
    for (uint i = 600; i < 800; i++) {
        EXPECT_TRUE(set[i] == trit::tFalse);
    }
    for (uint i = 800; i < 1000; i++) {
        EXPECT_TRUE(set[i] == trit::tTrue);
    }
}

TEST(CopyConstructor, part0) {
    Tritset setA(100);
    setA[70] = trit::tTrue;
    setA[50] = trit::tUnknown;
    setA[24] = trit::tFalse;
    Tritset setB = setA;
    setB[70] = trit::tFalse;
    setB[50] = trit::tFalse;
    setB[24] = trit::tFalse;
    setB.trim(60);

    EXPECT_TRUE(setA[70] == trit::tTrue);
    EXPECT_TRUE(setA[50] == trit::tUnknown);
    EXPECT_TRUE(setA[24] == trit::tFalse);
    EXPECT_TRUE(setB[70] == trit::tUnknown);
    EXPECT_TRUE(setB[50] == trit::tFalse);
    EXPECT_TRUE(setB[24] == trit::tFalse);
    EXPECT_TRUE(setB.length() < setA.length());
    EXPECT_TRUE(setA.capacity() == setB.capacity());
}

TEST(CopyConstructor, part1) {
    Tritset set(100);
    set[88] = trit::tTrue;
    set[70] = trit::tTrue;
    set[50] = trit::tUnknown;
    set[24] = trit::tFalse;

    unsigned int n = set.capacity();
    unsigned int m = set.length();

    Tritset set1 = set;

    EXPECT_TRUE(set1[70] == trit::tTrue);
    EXPECT_TRUE(set1[50] == trit::tUnknown);
    EXPECT_TRUE(set1[24] == trit::tFalse);
    EXPECT_TRUE(set1[88] == trit::tTrue);
    EXPECT_TRUE(set1.capacity() == n);
    EXPECT_TRUE(set1.length() == m);
}

TEST(CopyConstructor, part2) {
    Tritset set(100);
    for (int i = 0; i < 100; i++) {
        set[i] = static_cast<trit>(i % 3);
    }

    Tritset set1 = set;
    for (int i = 0; i < 100; i++) {
        EXPECT_TRUE(set1[i] == static_cast<trit>(i % 3));
    }
}

TEST(MemoryReallocation, part0) { // NoReallocation
    Tritset set(30);
    uint cap = set.capacity();
    for (uint i = 0; i < 30; i++) {
        set[i] = static_cast<trit>(i % 3);
    }
    EXPECT_TRUE(cap == set.capacity());
    set[31] = trit::tUnknown;
    set[40] = trit::tUnknown;
    set[100] = trit::tUnknown;
    set[10000] = trit::tUnknown;
    EXPECT_TRUE(cap == set.capacity());
}

TEST(MemoryReallocation, part1) { // Reallocation
    Tritset set;

    for (uint i = 0; i < 30; i++) {
        set[i] = static_cast<trit>(i % 3);
    }
    set[70] = trit::tTrue;
    set[70] = trit::tUnknown;

    for (uint i = 0; i < 30; i++) {
        EXPECT_TRUE(set[i] == static_cast<trit>(i % 3));
    }
    for (uint i = 30; i < 100; i++) {
        EXPECT_TRUE(set[i] == trit::tUnknown);
    }
}

TEST(LengthTest, part0) {
    Tritset set(1000);
    set[1] = trit::tFalse;
    set[2] = trit::tFalse;
    set[3] = trit::tTrue;
    EXPECT_TRUE(set.length() == 4);
}

TEST (LengthTest, part1) {
    Tritset set(1000);
    set[1] = trit::tFalse;
    set[2] = trit::tFalse;
    set[333] = trit::tTrue;
    set[555] = trit::tFalse;

    EXPECT_TRUE(set.length() == 556);

    set[565] = trit::tFalse;
    EXPECT_TRUE(set.length() == 566);

    set[565] = trit::tUnknown;
    set[555] = trit::tUnknown;
    EXPECT_TRUE(set.length() == 334);

    set[787] = trit::tTrue;
    set[789] = trit::tUnknown;
    set[700] = trit::tFalse;
    EXPECT_TRUE(set.length() == 788);

    set[787] = trit::tUnknown;
    EXPECT_TRUE(set.length() == 701);
}

TEST(trit_operator, AND) {
    trit F = trit::tFalse, U = trit::tUnknown, T = trit::tTrue;

    EXPECT_TRUE((F & F) == trit::tFalse);
    EXPECT_TRUE((F & U) == trit::tFalse);
    EXPECT_TRUE((F & T) == trit::tFalse);
    EXPECT_TRUE((U & U) == trit::tUnknown);
    EXPECT_TRUE((U & T) == trit::tUnknown);
    EXPECT_TRUE((T & T) == trit::tTrue);
}

TEST(trit_operator, OR) {
    trit F = trit::tFalse, U = trit::tUnknown, T = trit::tTrue;

    EXPECT_TRUE((T | T) == trit::tTrue);
    EXPECT_TRUE((T | U) == trit::tTrue);
    EXPECT_TRUE((T | F) == trit::tTrue);
    EXPECT_TRUE((U | U) == trit::tUnknown);
    EXPECT_TRUE((U | F) == trit::tUnknown);
    EXPECT_TRUE((F | F) == trit::tFalse);
}

TEST(trit_operator, NOT) {
    trit F = trit::tFalse, U = trit::tUnknown, T = trit::tTrue;
    EXPECT_TRUE(!F == trit::tTrue);
    EXPECT_TRUE(!U == trit::tUnknown);
    EXPECT_TRUE(!T == trit::tFalse);
}

TEST(TritsetOperator, AND) {
    Tritset setA, setB, setC;
    setA[1] = trit::tFalse;
    setA[3] = trit::tFalse;
    setA[5] = trit::tTrue;

    setB[0] = trit::tTrue;
    setB[2] = trit::tFalse;
    setB[3] = trit::tFalse;
    setB[4] = trit::tTrue;
    setB[5] = trit::tTrue;
    setB[7] = trit::tFalse;
    setB[8] = trit::tFalse;
    setB[9] = trit::tFalse;
    uint capA = setA.capacity(), capB = setB.capacity();
    setC = setA & setB;

    EXPECT_TRUE(setA[0] == trit::tUnknown);
    EXPECT_TRUE(setA[1] == trit::tFalse);
    EXPECT_TRUE(setA[2] == trit::tUnknown);
    EXPECT_TRUE(setA[3] == trit::tFalse);
    EXPECT_TRUE(setA[4] == trit::tUnknown);
    EXPECT_TRUE(setA[5] == trit::tTrue);

    EXPECT_TRUE(setB[0] == trit::tTrue);
    EXPECT_TRUE(setB[1] == trit::tUnknown);
    EXPECT_TRUE(setB[2] == trit::tFalse);
    EXPECT_TRUE(setB[3] == trit::tFalse);
    EXPECT_TRUE(setB[4] == trit::tTrue);
    EXPECT_TRUE(setB[5] == trit::tTrue);
    EXPECT_TRUE(setB[6] == trit::tUnknown);
    EXPECT_TRUE(setB[7] == trit::tFalse);
    EXPECT_TRUE(setB[8] == trit::tFalse);
    EXPECT_TRUE(setB[9] == trit::tFalse);

    EXPECT_TRUE(setC[0] == trit::tUnknown);
    EXPECT_TRUE(setC[1] == trit::tFalse);
    EXPECT_TRUE(setC[2] == trit::tFalse);
    EXPECT_TRUE(setC[3] == trit::tFalse);
    EXPECT_TRUE(setC[4] == trit::tUnknown);
    EXPECT_TRUE(setC[5] == trit::tTrue);
    EXPECT_TRUE(setC[6] == trit::tUnknown);
    EXPECT_TRUE(setC[7] == trit::tFalse);
    EXPECT_TRUE(setC[8] == trit::tFalse);
    EXPECT_TRUE(setC[9] == trit::tFalse);

    EXPECT_TRUE(setA.capacity() == capA);
    EXPECT_TRUE(setB.capacity() == capB);
    EXPECT_TRUE(setC.capacity() == capB);
}

TEST(TritsetOperator, OR) {
    Tritset setA, setB, setC;
    setA[5] = trit::tTrue;
    setA[3] = trit::tFalse;
    setA[1] = trit::tFalse;

    setB[9] = trit::tFalse;
    setB[8] = trit::tFalse;
    setB[7] = trit::tFalse;
    setB[0] = trit::tTrue;
    setB[3] = trit::tFalse;
    setB[5] = trit::tTrue;
    setB[4] = trit::tTrue;
    setB[2] = trit::tFalse;
    uint capA = setA.capacity(), capB = setB.capacity();
    setC = setA | setB;

    EXPECT_TRUE(setA[0] == trit::tUnknown);
    EXPECT_TRUE(setA[1] == trit::tFalse);
    EXPECT_TRUE(setA[2] == trit::tUnknown);
    EXPECT_TRUE(setA[3] == trit::tFalse);
    EXPECT_TRUE(setA[4] == trit::tUnknown);
    EXPECT_TRUE(setA[5] == trit::tTrue);

    EXPECT_TRUE(setB[0] == trit::tTrue);
    EXPECT_TRUE(setB[1] == trit::tUnknown);
    EXPECT_TRUE(setB[2] == trit::tFalse);
    EXPECT_TRUE(setB[3] == trit::tFalse);
    EXPECT_TRUE(setB[4] == trit::tTrue);
    EXPECT_TRUE(setB[5] == trit::tTrue);
    EXPECT_TRUE(setB[6] == trit::tUnknown);
    EXPECT_TRUE(setB[7] == trit::tFalse);
    EXPECT_TRUE(setB[8] == trit::tFalse);
    EXPECT_TRUE(setB[9] == trit::tFalse);

    EXPECT_TRUE(setC[0] == trit::tTrue);
    EXPECT_TRUE(setC[1] == trit::tUnknown);
    EXPECT_TRUE(setC[2] == trit::tUnknown);
    EXPECT_TRUE(setC[3] == trit::tFalse);
    EXPECT_TRUE(setC[4] == trit::tTrue);
    EXPECT_TRUE(setC[5] == trit::tTrue);
    EXPECT_TRUE(setC[6] == trit::tUnknown);
    EXPECT_TRUE(setC[7] == trit::tUnknown);
    EXPECT_TRUE(setC[8] == trit::tUnknown);
    EXPECT_TRUE(setC[9] == trit::tUnknown);

    EXPECT_TRUE(setA.capacity() == capA);
    EXPECT_TRUE(setB.capacity() == capB);
    EXPECT_TRUE(setC.capacity() == capB);
}

TEST(TritsetOperator, NOT) {
    Tritset setA(100);
    setA[0] = trit::tTrue;
    setA[1] = trit::tFalse;
    setA[2] = trit::tTrue;
    setA[5] = trit::tFalse;
    Tritset setB = !setA;

    EXPECT_TRUE(setA.length() == 6);
    EXPECT_TRUE(setA.length() == setB.length());

    EXPECT_TRUE(setA[0] == trit::tTrue);
    EXPECT_TRUE(setA[1] == trit::tFalse);
    EXPECT_TRUE(setA[2] == trit::tTrue);
    EXPECT_TRUE(setA[3] == trit::tUnknown);
    EXPECT_TRUE(setA[4] == trit::tUnknown);
    EXPECT_TRUE(setA[5] == trit::tFalse);

    EXPECT_TRUE(setB[0] == trit::tFalse);
    EXPECT_TRUE(setB[1] == trit::tTrue);
    EXPECT_TRUE(setB[2] == trit::tFalse);
    EXPECT_TRUE(setB[3] == trit::tUnknown);
    EXPECT_TRUE(setB[4] == trit::tUnknown);
    EXPECT_TRUE(setB[5] == trit::tTrue);
}

TEST(SingleTritAssignment, part0) {
    Tritset setA(100);
    setA[0] = trit::tTrue;
    setA[1] = trit::tFalse;
    setA[2] = trit::tTrue;
    setA[5] = trit::tFalse;
    Tritset setB(100);

    setB[0] = setA[0];
    setB[1] = setA[1];
    setB[2] = setA[2];
    setB[5] = setA[5];

    EXPECT_TRUE(setB[0] == trit::tTrue);
    EXPECT_TRUE(setB[1] == trit::tFalse);
    EXPECT_TRUE(setB[2] == trit::tTrue);
    EXPECT_TRUE(setB[3] == trit::tUnknown);
    EXPECT_TRUE(setB[4] == trit::tUnknown);
    EXPECT_TRUE(setB[5] == trit::tFalse);
}

TEST(SingleTritAssignment, part1) {
    Tritset setA(1000);
    Tritset setB(1000);
    setA[232] = trit::tFalse;
    setA[578] = trit::tTrue;
    setA[333] = trit::tFalse;
    setA[881] = trit::tTrue;

    setB[678] = setA[232];
    EXPECT_TRUE(setB[678] == trit::tFalse);

    setB[45] = setA[881];
    EXPECT_TRUE(setB[45] == trit::tTrue);

    setB[665] = setA[333];
    EXPECT_TRUE(setB[665] == trit::tFalse);

    setB[999] = setA[578];
    EXPECT_TRUE(setB[999] == trit::tTrue);
}

TEST(SingleTritAssignment, part2) {
    Tritset setA(1000);
    Tritset setB(1000);
    for (int i = 0; i < 1000; i++) {
        setA[i] = static_cast<trit>(i % 3);
    }

    for (int i = 0; i < 999; i++) {
        setB[i] = setA[i+1];
    }

    for (int i = 0; i < 999; i++) {
        EXPECT_TRUE(setB[i] == static_cast<trit>((i + 1) % 3));
    }
}



#ifndef OOOP_NSU_TRITSET_H
#define OOOP_NSU_TRITSET_H
#include "trit.h"
#include <cstring>
#include <cstdlib>
#include <unordered_map>
#include <iostream>


typedef unsigned int u__int;


class TritsetSupport;

class Tritset {
    friend TritsetSupport;
private:
    static const u__int tritsInUnsignedInt = sizeof(unsigned int) * 4;
    u__int *arr;
    int arrLength; // Current length in u__int
    int arrSize; // Array max size in u__int
    int lastIndexInTrits; // Last array index in trits
    void expandArray(u__int newSizeInUiBytes);
    void resetLastIndexInTrits();
    void resetLastIndexInTrits(u__int index);
    trit getTritByIndex(u__int index) const;
    static u__int getMaxIndexInTrits(const Tritset &a, const Tritset &b);
    static u__int getArrMaxSize(const Tritset &a, const Tritset &b);
public:
    Tritset();
    explicit Tritset(int n);
    Tritset(const Tritset &set);
    ~Tritset();
    Tritset operator&(const Tritset &secondOperand) const;
    Tritset operator|(const Tritset &secondOperand) const ;
    Tritset operator!() const;
    trit operator[](u__int idx) const;
    TritsetSupport operator[](u__int idx);
    Tritset &operator=(const Tritset &secondOperand);
    u__int capacity();
    std::unordered_map<trit, int> cardinality() const;
    u__int cardinality(trit value) const;
    u__int length() const;
    void trim(u__int lastIdx);
    void shrink();
};

class TritsetSupport {
    friend Tritset;
private:
    u__int arrIndex;
    u__int tritIndexInByte;
    Tritset* ptr;
    TritsetSupport(int arrIdx, int tritIdx, Tritset *p);
public:
    TritsetSupport &operator=(trit operand);
    bool operator==(trit secondOperand);
    bool operator!=(trit secondOperand);
    TritsetSupport &operator=(const TritsetSupport &t);
};


#endif //OOOP_NSU_TRITSET_H
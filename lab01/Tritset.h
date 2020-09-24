#ifndef OOOP_NSU_TRITSET_H
#define OOOP_NSU_TRITSET_H
#include <cstring>
#include <cstdlib>
#include <unordered_map>


typedef unsigned int u__int;
enum class trit {tFalse = 2, tUnknown = 0, tTrue = 1};


class TritsetSupport;

class Tritset {
    friend TritsetSupport;
private:
    u__int *arr;
    int arrLength; // Current length in u__int
    int arrSize; // Array max size in u__int
    int lastIndexInTrits; // Last array index in trits
    void expandArray(u__int newSizeInUiBytes);
    void resetLastIndexInTrits();
public:
    Tritset();
    explicit Tritset(int n);
    Tritset(const Tritset &set);
    ~Tritset();
    Tritset operator&(const Tritset &secondOperand);
    Tritset operator|(const Tritset &secondOperand);
    Tritset operator!();
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
};


trit operator!(const trit &operand);
trit operator|(const trit &firstOperand, const trit &secondOperand);
trit operator&(const trit &firstOperand, const trit &secondOperand);


#endif //OOOP_NSU_TRITSET_H
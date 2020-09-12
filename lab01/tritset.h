#ifndef OOOP_NSU_TRITSET_H
#define OOOP_NSU_TRITSET_H
#include <cstring>
#include <cstdlib>


typedef unsigned int u__int;
enum class trit {tritFalse = 2, tritUnknown = 0, tritTrue = 1};


class tritsetSupport;

class tritset {
    friend tritsetSupport;
private:
    u__int *arr;
    int arrLength; // Current length in u__int
    int arrSize; // Array max size in u__int
public:
    tritset();
    tritset(int m, int n);
    ~tritset();
    tritset operator&(const tritset secondOperand);
    tritset operator|(const tritset secondOperand);
    tritset operator!();
    trit operator[](u__int idx) const;
    tritsetSupport operator[](u__int idx);
    tritset &operator=(const tritset &secondOperand);
};

class tritsetSupport {
    friend tritset;
private:
    u__int arrIndex;
    u__int tritIndexInByte;
    tritset* ptr;
    tritsetSupport(int arrIdx, int tritIdx, tritset *p);
public:
    tritsetSupport &operator=(trit operand);
    bool operator==(trit secondOperand);
    bool operator!=(trit secondOperand);
};


trit operator!(const trit &operand);
trit operator|(const trit &firstOperand, const trit &secondOperand);
trit operator&(const trit &firstOperand, const trit &secondOperand);


#endif //OOOP_NSU_TRITSET_H

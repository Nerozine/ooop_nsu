//
// Created by alexandr on 09.09.2020.
//

#ifndef OOOP_NSU_TRITSET_H
#define OOOP_NSU_TRITSET_H


#include <cstring>


typedef unsigned int u__int;
enum trit {tritFalse, tritUnknown, tritTrue};


class tritset {
private:
private:
    u__int *arr;
    int arrLength; // Current length in u__int
    int arrSize; // Array max size in u__int
public:
    tritset();
    ~tritset();
    tritset operator& (const tritset secondOperand);
    tritset operator| (const tritset secondOperand);
    tritset operator! ();
    tritset operator[] (u__int idx);
    tritset& operator= (const tritset &secondOperand);

};


#endif //OOOP_NSU_TRITSET_H

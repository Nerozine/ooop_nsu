#include "Tritset.h"


Tritset &Tritset::operator=(const Tritset &secondOperand) {
    if (this == &secondOperand) {
        return *this;
    }

    auto *tempArr = new u__int[secondOperand.arrSize]();
    memset(tempArr, 0,secondOperand.arrSize * sizeof(u__int));
    delete[] this->arr;
    this->arr = tempArr;
    this->arrSize = secondOperand.arrSize;

    this->arrLength = secondOperand.arrLength;
    this->lastIndexInTrits = secondOperand.lastIndexInTrits;
    memcpy(this->arr, secondOperand.arr, arrSize * sizeof(u__int));

    return *this;
}


Tritset::Tritset(): arr(new u__int[10]()), arrSize(10), arrLength(0), lastIndexInTrits(0) {
    memset(arr, 0, sizeof(u__int) * 10);
}


Tritset::~Tritset() {
    delete[] arr;
}


Tritset Tritset::operator&(const Tritset &secondOperand) {
    Tritset result;
    Tritset t;

    if (this->arrLength > secondOperand.arrLength) {
        result = *this;
        t = secondOperand;
        expandArray(&t, result.arrSize);
    }
    else {
        result = secondOperand;
        t = *this;
        expandArray(&t, result.arrSize);
    }

    for (u__int i = 0; i <= result.arrLength; i++) {
        for (u__int j = 0; j < sizeof(u__int) * 4; j++) {
            u__int tmpIdx = i * 4 * sizeof(u__int) + j;

            if (tmpIdx > result.lastIndexInTrits) {
                break;
            }

            if ((t[tmpIdx] == trit::tFalse) || (result[tmpIdx]) == trit::tFalse) {
                result[tmpIdx] = trit::tFalse;
            }
            else {
                if ((result[tmpIdx] == trit::tTrue) && (t[tmpIdx] == trit::tTrue)) {
                    result[tmpIdx] = trit::tTrue;
                }
                else {
                    result[tmpIdx] = trit::tUnknown;
                }
            }
        }
    }

    return result;
}


Tritset Tritset::operator|(const Tritset &secondOperand) {
    Tritset result;
    Tritset t;

    if (this->arrLength > secondOperand.arrLength) {
        result = *this;
        t = secondOperand;
        expandArray(&t, result.arrSize);
    }
    else {
        result = secondOperand;
        t = *this;
        expandArray(&t, result.arrSize);
    }

    for (u__int i = 0; i <= result.arrLength; i++) {
        for (u__int j = 0; j < sizeof(u__int) * 4; j++) {
            u__int tmpIdx = i * 4 * sizeof(u__int) + j;

            if (tmpIdx > result.lastIndexInTrits) {
                break;
            }

            if ((t[tmpIdx] == trit::tTrue) || (result[tmpIdx] == trit::tTrue)) {
                result[tmpIdx] = trit::tTrue;
            }
            else {
                if ((t[tmpIdx] == trit::tFalse) && (result[tmpIdx] == trit::tFalse)) {
                    result[tmpIdx] = trit::tFalse;
                }
                else {
                    result[tmpIdx] = trit::tUnknown;
                }
            }
        }
    }

    return result;
}


Tritset Tritset::operator!() {
    Tritset result = *this;

    for (u__int i = 0; i <= result.arrLength; i++) {
        for (u__int j = 0; j < sizeof(u__int) * 4; j++) {
            u__int tmpIdx = i * 4 * sizeof(u__int) + j;

            if (tmpIdx > result.lastIndexInTrits) {
                break;
            }

            if (result[tmpIdx] == trit::tFalse) {
                result[tmpIdx] = trit::tTrue;
            }
            else {
                if (result[tmpIdx] == trit::tTrue) {
                    result[tmpIdx] = trit::tFalse;
                }
            }
        }
    }

    return result;
}


trit Tritset::operator[](u__int idx) const {
    u__int tritsInUiByte = sizeof(u__int) * 4;
    u__int arrIndex = idx / tritsInUiByte;
    u__int tritIndexInByte = idx % tritsInUiByte;
    if (idx > lastIndexInTrits) {
        return trit::tUnknown;
    }

    u__int requiredTrit = arr[arrIndex] >> (2 * tritIndexInByte);
    requiredTrit &= 3u;

    switch(requiredTrit) {
        case 2: { // tritFalse
            return trit::tFalse;
        }
        case 1: { // tritTrue
            return trit::tTrue;
        }
        case 0: { // tritUnknown
            return trit::tUnknown;
        }
        default: std::exit(10);
    }
}


Tritset::Tritset(int n): arr(new u__int[n / sizeof(u__int) / 4 + 1]()), arrSize(n / sizeof(u__int) / 4 + 1),
                        lastIndexInTrits(0), arrLength(0) {
    memset(arr, 0, (n / sizeof(u__int) / 4 + 1) * sizeof(u__int));
}

Tritset::Tritset(const Tritset &set): arr(new u__int[set.arrSize]()),
                        arrSize(set.arrSize), lastIndexInTrits(set.lastIndexInTrits), arrLength(set.arrLength) {
    memset(arr, 0, arrSize * sizeof(u__int));
    memcpy(arr, set.arr, (set.arrLength + 1) * sizeof(u__int));
}


TritsetSupport Tritset::operator[](u__int idx) {
//    if (idx > lastIndexInTrits && idx < arrSize * sizeof(u__int) * 4) {
//        lastIndexInTrits = idx;
//    }

    u__int arrIdx = idx / sizeof(u__int) / 4;
    u__int tritIdxInByte = idx % (sizeof(u__int) * 4);

    return TritsetSupport(arrIdx, tritIdxInByte, this);
}


u__int Tritset::capacity() {
     return arrSize * 4 * sizeof(u__int);
}


std::unordered_map<trit, int> Tritset::cardinality() const {
    u__int numberOfUnknown = 0;
    u__int numberOfTrue = 0;
    u__int numberOfFalse = 0;

    for (u__int i = 0; i <= lastIndexInTrits; i++) {
        switch ((*this)[i]) {
            case trit::tUnknown: {
                numberOfUnknown++;
                break;
            }
            case trit::tTrue: {
                numberOfTrue++;
                break;
            }
            case trit::tFalse: {
                numberOfFalse++;
                break;
            }
        }
    }

    std::unordered_map<trit, int> resultMap;
    resultMap[trit::tUnknown] = numberOfUnknown;
    resultMap[trit::tTrue] = numberOfTrue;
    resultMap[trit::tFalse] = numberOfFalse;

    return resultMap;
}


u__int Tritset::cardinality(trit value) const {
    // returns number of trits that is equal to value
    u__int cnt = 0;

    for (u__int i = 0; i <= lastIndexInTrits; i++) {
        if ((*this)[i] == value) {
            cnt++;
        }
    }

    return cnt;
}



u__int Tritset::length() const {
    // returns index of last trit + 1
    return lastIndexInTrits + 1;
}


void Tritset::trim(u__int lastIdx) {
    // forget all trits form lastIdx including lastidx
    for (u__int i = lastIdx; i <= lastIndexInTrits; i++) {
        (*this)[i] = trit::tUnknown;
    }
    if (lastIndexInTrits > lastIdx) {
        if (lastIdx > 1) {
            lastIndexInTrits = lastIdx - 1;
        } else {
            lastIndexInTrits = 0;
        }
    }
    arrLength = lastIdx / 4 / sizeof(u__int) + 1;
}


void Tritset::shrink() {
    // memory free from the last seted trit
    auto newArr = new u__int[arrLength]();
    memset(newArr, 0, arrLength * sizeof(u__int));
    memcpy(newArr, this->arr, (arrLength + 1) * sizeof(u__int));
    delete [] this->arr;
    this->arr = newArr;
    this->arrSize = arrLength + 1;
}


void Tritset::expandArray(Tritset *t, u__int newSizeInUiBytes) {
    auto newArr = new u__int[newSizeInUiBytes]();
    memset(newArr, 0, newSizeInUiBytes * sizeof(u__int));
    memcpy(newArr, t->arr, (t->arrLength + 1) * sizeof(u__int));
    delete [] t->arr;
    t->arr = newArr;
    t->arrSize = newSizeInUiBytes;
}


trit operator!(const trit &operand) {
    switch (operand) {
        case trit::tFalse: {
            return trit::tTrue;
        }
        case trit::tTrue: {
            return trit::tFalse;
        }
        case trit::tUnknown: {
            return trit::tUnknown;
        }
        default: {
            std::exit(11);
        }
    }
}


trit operator|(const trit &firstOperand, const trit &secondOperand) {
    if ((firstOperand == trit::tTrue) || (secondOperand == trit::tTrue)) {
        return trit::tTrue;
    }
    else {
        if ((firstOperand == trit::tUnknown) || (secondOperand == trit::tUnknown)) {
            return trit::tUnknown;
        }
        return trit::tFalse;
    }
}


trit operator&(const trit &firstOperand, const trit &secondOperand) {
    if ((firstOperand == trit::tFalse) || (secondOperand == trit::tFalse)) {
        return trit::tFalse;
    }
    else {
        if ((firstOperand == trit::tTrue) && (secondOperand == trit::tTrue)) {
            return trit::tTrue;
        }
        return trit::tUnknown;
    }
}


TritsetSupport &TritsetSupport::operator=(trit operand) {
    // expands arr if not enough size and operand!=tritUnknown
    if (operand == trit::tUnknown && arrIndex > ptr->arrSize) {
        return *this;
    }

    if (operand != trit::tUnknown && arrIndex >= ptr->arrSize) {
        auto newArr = new u__int[arrIndex + 1]();
        memset(newArr, 0, (arrIndex + 1) * sizeof(u__int));
        memcpy(newArr, ptr->arr, (ptr->arrLength + 1) * sizeof(u__int));
        delete [] ptr->arr;
        ptr->arr = newArr;
        ptr->arrSize = arrIndex + 1;
        ptr->arrLength = arrIndex;
    }

    if (ptr->arrLength < arrIndex) {
        ptr->arrLength = arrIndex;
    }

    if (ptr->lastIndexInTrits < arrIndex * sizeof(u__int) * 4 + tritIndexInByte) {
        ptr->lastIndexInTrits = arrIndex * sizeof(u__int) * 4 + tritIndexInByte;
    }

    u__int mask = 0;
    u__int tmp = 0;
    u__int arrByteTmp = ptr->arr[arrIndex];

    mask |= (3u << (tritIndexInByte * 2));
    mask = ~mask;
    arrByteTmp &= mask;

    switch (operand) {
        case trit::tTrue: {
            tmp = 1u << (tritIndexInByte * 2);
            break;
        }
        case trit::tFalse: {
            tmp = 1u << (tritIndexInByte * 2 + 1);
            break;
        }
        case trit::tUnknown: {
            tmp = 0;
            break;
        }
        default: {
            exit(12);
        }
    }

    ptr->arr[arrIndex] = arrByteTmp | tmp;

    if (operand == trit::tUnknown && arrIndex * sizeof(u__int) * 4 + tritIndexInByte == ptr->lastIndexInTrits
            && ptr->lastIndexInTrits != 0) {
        u__int i;
        for (i = ptr->lastIndexInTrits - 1;; i--) {
            if ((*ptr)[i] != trit::tUnknown || i == 0) {
                ptr->lastIndexInTrits = i;
                ptr->arrLength = i / (sizeof(u__int) * 4);
                break;
            }
        }
    }

    return *this;
}


TritsetSupport::TritsetSupport(int arrIdx, int tritIdx, Tritset *p):
    arrIndex(arrIdx), tritIndexInByte(tritIdx), ptr(p) {}


bool TritsetSupport::operator==(const trit secondOperand) {
    u__int tmp = 0;

    if (arrIndex > ptr->arrLength) {
        tmp = 0;
    }
    else {
        tmp = ptr->arr[arrIndex];
        tmp >>= tritIndexInByte * 2;
        u__int mask = 3u;
        tmp &= mask;
    }

    switch (tmp) {
        case 0: {
            return secondOperand == trit::tUnknown;
        }
        case 1: {
            return secondOperand == trit::tTrue;
        }
        case 2: {
            return secondOperand == trit::tFalse;
        }
        default: {
            std::exit(13);
        }
    }
}


bool TritsetSupport::operator!=(const trit secondOperand) {
    u__int tmp = 0;

    if (arrIndex > ptr->arrLength) {
        tmp = 0;
    }
    else {
        tmp = ptr->arr[arrIndex];
        tmp >>= tritIndexInByte * 2;
        u__int mask = 3u;
        tmp &= mask;
    }

    switch (tmp) {
        case 0: {
            return !(secondOperand == trit::tUnknown);
        }
        case 1: {
            return !(secondOperand == trit::tTrue);
        }
        case 2: {
            return !(secondOperand == trit::tFalse);
        }
        default: {
            std::exit(14);
        }
    }
}
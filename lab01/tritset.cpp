#include "tritset.h"


tritset &tritset::operator=(const tritset &secondOperand) {
    if (this == &secondOperand) {
        return *this;
    }

    if (arrSize != secondOperand.arrSize) {
        auto *tempArr = new u__int[secondOperand.arrSize];
        if (!this->arr) {
            delete[] this->arr;
        }
        this->arr = tempArr;
        this->arrSize = secondOperand.arrSize;
    }
    this->arrLength = secondOperand.arrLength;
    this->lastIndexInTrits = secondOperand.lastIndexInTrits;
    memcpy(this->arr, secondOperand.arr, arrLength * sizeof(u__int));

    return *this;
}


tritset::tritset(): arr(new u__int[500 / sizeof(u__int)]),
    arrSize(500 / sizeof(u__int)), arrLength(0), lastIndexInTrits(0) { }


tritset::~tritset() {
    delete[] arr;
}


tritset tritset::operator&(const tritset &secondOperand) {
    tritset result;
    tritset t;

    if (this->arrLength > secondOperand.arrLength) {
        result = *this;
        t = secondOperand;
    }
    else {
        result = secondOperand;
        t = *this;
    }

    for (u__int i = 0; i < result.arrLength; i++) {
        for (u__int j = 0; j < sizeof(u__int) * 4; j++) {
            u__int tmpIdx = i * 4 + j;
            if ((t[tmpIdx] == trit::tritFalse) || (result[tmpIdx]) == trit::tritFalse) {
                result[tmpIdx] = trit::tritFalse;
            }
            else {
                if ((t[tmpIdx] == trit::tritTrue) && (result[tmpIdx]) == trit::tritTrue) {
                    result[tmpIdx] = trit::tritTrue;
                }
                else {
                    result[tmpIdx] = trit::tritUnknown;
                }
            }
        }
    }

    return result;
}


tritset tritset::operator|(const tritset &secondOperand) {
    tritset result;
    tritset t;

    if (this->arrLength > secondOperand.arrLength) {
        result = *this;
        t = secondOperand;
    }
    else {
        result = secondOperand;
        t = *this;
    }

    for (u__int i = 0; i < result.arrLength; i++) {
        for (u__int j = 0; j < sizeof(u__int) * 4; j++) {
            u__int tmpIdx = i * 4 + j;
            if ((t[tmpIdx] == trit::tritTrue) || (result[tmpIdx] == trit::tritTrue)) {
                result[tmpIdx] = trit::tritTrue;
            }
            else {
                if ((t[tmpIdx] == trit::tritFalse) && (result[tmpIdx] == trit::tritFalse)) {
                    result[tmpIdx] = trit::tritFalse;
                }
                else {
                    result[tmpIdx] = trit::tritUnknown;
                }
            }
        }
    }

    return result;
}


tritset tritset::operator!() {
    tritset result = *this;

    for (u__int i = 0; i < result.arrLength; i++) {
        for (u__int j = 0; j < sizeof(u__int) * 4; j++) {
            u__int tmpIdx = i * 4 + j;
            if (result[tmpIdx] == trit::tritFalse) {
                result[tmpIdx] = trit::tritTrue;
            }
            else {
                if (result[tmpIdx] == trit::tritTrue) {
                    result[tmpIdx] = trit::tritFalse;
                }
            }
        }
    }

    return result;
}


trit tritset::operator[](u__int idx) const {
    u__int tritsInByte = sizeof(u__int) * 4;
    u__int arrIndex = idx / tritsInByte;
    u__int tritIndexInByte = idx % tritsInByte;
    if (idx > lastIndexInTrits) {
        return trit::tritUnknown;
    }

    u__int requiredTrit = arr[arrIndex] << (tritsInByte - 1 - tritIndexInByte);
    requiredTrit >>= (tritsInByte - 1);

    switch(requiredTrit) {
        case 2: { // tritFalse
            return trit::tritFalse;
        }
        case 1: { // tritTrue
            return trit::tritTrue;
        }
        case 0: { // tritUnknown
            return trit::tritUnknown;
        }
        default: std::exit(10);
    }
}


tritset::tritset(int n): arr(new u__int[n / sizeof(u__int)]), arrSize(n / sizeof(u__int)),
    lastIndexInTrits(0), arrLength(0) { }


tritsetSupport tritset::operator[](u__int idx) {
    if (idx > lastIndexInTrits && idx < arrSize * sizeof(u__int) / 2) {
        lastIndexInTrits = idx;
    }

    u__int tritsInByte = sizeof(u__int) * 4;
    u__int arrIdx = idx / tritsInByte;
    u__int tritIdxInByte = idx % tritsInByte;

    return tritsetSupport(arrIdx,tritIdxInByte, this);
}


u__int tritset::capacity() {
     return arrSize * 4;
}


std::unordered_map<trit, int> tritset::cardinality() const {
    u__int numberOfUnknown = 0;
    u__int numberOfTrue = 0;
    u__int numberOfFalse = 0;

    for (u__int i = 0; i <= lastIndexInTrits; i++) {
        switch ((*this)[i]) {
            case trit::tritUnknown: {
                numberOfUnknown++;
                break;
            }
            case trit::tritTrue: {
                numberOfTrue++;
                break;
            }
            case trit::tritFalse: {
                numberOfFalse++;
                break;
            }
        }
    }

    std::unordered_map<trit, int> resultMap;
    resultMap[trit::tritUnknown] = numberOfUnknown;
    resultMap[trit::tritTrue] = numberOfTrue;
    resultMap[trit::tritFalse] = numberOfFalse;

    return resultMap;
}


u__int tritset::cardinality(trit value) const {
    // returns number of trits that is equal to value
    u__int cnt = 0;

    for (u__int i = 0; i <= lastIndexInTrits + 1; i++) {
        if ((*this)[i] == value) {
            cnt++;
        }
    }

    return cnt;
}



u__int tritset::length() const {
    // returns index of last trit + 1
    return lastIndexInTrits + 1;
}


void tritset::trim(u__int lastIdx) {
    // remember lastIdx, but lastIdx+1 don't
    for (int i = lastIdx + 1; i <= lastIndexInTrits; i++) {
        (*this)[i] = trit::tritUnknown;
    }
    lastIndexInTrits = lastIdx;
    arrLength = lastIdx / 4 / sizeof(u__int);
}


void tritset::shrink() {
    // memory free from the last seted trit
    auto newArr = new u__int[arrLength];
    memcpy(newArr, this->arr, arrLength);
    delete [] this->arr;
    this->arr = newArr;
}


trit operator!(const trit &operand) {
    switch (operand) {
        case trit::tritFalse: {
            return trit::tritTrue;
        }
        case trit::tritTrue: {
            return trit::tritFalse;
        }
        case trit::tritUnknown: {
            return trit::tritUnknown;
        }
        default: {
            std::exit(11);
        }
    }
}


trit operator|(const trit &firstOperand, const trit &secondOperand) {
    if ((firstOperand == trit::tritTrue) || (secondOperand == trit::tritTrue)) {
        if ((firstOperand == trit::tritUnknown) || (secondOperand == trit::tritUnknown)) {
            return trit::tritTrue;
        }
        return trit::tritUnknown;
    }
    else {
        if ((firstOperand == trit::tritUnknown) || (secondOperand == trit::tritUnknown)) {
            return trit::tritUnknown;
        }
        return trit::tritFalse;
    }
}


trit operator&(const trit &firstOperand, const trit &secondOperand) {
    if ((firstOperand == trit::tritFalse) || (secondOperand == trit::tritFalse)) {
        return trit::tritFalse;
    }
    else {
        if ((firstOperand == trit::tritTrue) && (secondOperand == trit::tritTrue)) {
            return trit::tritTrue;
        }
        return trit::tritUnknown;
    }
}


tritsetSupport &tritsetSupport::operator=(trit operand) {
    // expands arr if not enough size and operand!=tritUnknown

    if (operand == trit::tritUnknown && arrIndex > ptr->arrSize) {
        return *this;
    }

    if (operand != trit::tritUnknown && arrIndex > ptr->arrSize) {
        auto newArr = new u__int[arrIndex];
        memcpy(newArr, ptr->arr, ptr->arrLength);
        delete [] ptr->arr;
        ptr->arr = newArr;
        ptr->arrSize = arrIndex * 4;
    }

    u__int mask = 0;
    u__int tmp = 0;
    u__int arrByteTmp = ptr->arr[arrIndex];

    mask |= (3u << (tritIndexInByte * 2));
    mask = ~mask;
    arrByteTmp &= mask;

    switch (operand) {
        case trit::tritTrue: {
            tmp = 1u << (tritIndexInByte * 2);
            break;
        }
        case trit::tritFalse: {
            tmp = 1u << (tritIndexInByte * 2 + 1);
            break;
        }
        case trit::tritUnknown: {
            tmp = 0;
            break;
        }
        default: {
            exit(12);
        }
    }
    arrByteTmp |= tmp;
    ptr->arr[arrIndex] = arrByteTmp;
    return *this;
}


tritsetSupport::tritsetSupport(int arrIdx, int tritIdx, tritset *p):
    arrIndex(arrIdx), tritIndexInByte(tritIdx), ptr(p) {}


bool tritsetSupport::operator==(trit secondOperand) {
    u__int tmp = ptr->arr[arrIndex];
    tmp >>= tritIndexInByte * 2;
    u__int mask = 3u;
    tmp &= mask;
    switch (tmp) {
        case 0: {
            return secondOperand == trit::tritUnknown;
        }
        case 1: {
            return secondOperand == trit::tritTrue;
        }
        case 2: {
            return secondOperand == trit::tritFalse;
        }
        default: {
            std::exit(13);
        }
    }
}


bool tritsetSupport::operator!=(trit secondOperand) {
    u__int tmp = ptr->arr[arrIndex];
    tmp >>= tritIndexInByte * 2;
    u__int mask = 3u;
    tmp &= mask;
    switch (tmp) {
        case 0: {
            return !(secondOperand == trit::tritUnknown);
        }
        case 1: {
            return !(secondOperand == trit::tritTrue);
        }
        case 2: {
            return !(secondOperand == trit::tritFalse);
        }
        default: {
            std::exit(14);
        }
    }
}
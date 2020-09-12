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
    memcpy(this->arr, secondOperand.arr, arrSize * sizeof(u__int));

    return *this;
}

tritset::tritset(): arr(nullptr), arrSize(0), arrLength(0) { }

tritset::~tritset() {
    delete[] arr;
}

tritset tritset::operator&(const tritset secondOperand) {
    return tritset();
}

tritset tritset::operator|(const tritset secondOperand) {
    return tritset();
}

tritset tritset::operator!() {
    return tritset();
}

trit tritset::operator[](u__int idx) const {
    u__int tritsInByte = sizeof(u__int) * 4;
    u__int arrIndex = idx / tritsInByte;
    u__int tritIndexInByte = idx % tritsInByte;
    if (idx > arrLength * tritsInByte) {
        return trit::tritUnknown;
    }

    u__int requiredTrit = arr[arrIndex] << (tritsInByte - 1 - tritIndexInByte);
    requiredTrit >>= (tritsInByte - 1);
//    requiredTrit &= 3u;

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

tritset::tritset(int m, int n) {
    arr = new u__int[m];
    arrSize = n;
    arrLength = 0;
}

tritsetSupport tritset::operator[](u__int idx) {
    u__int tritsInByte = sizeof(u__int) * 4;
    u__int arrIdx = idx / tritsInByte;
    u__int tritIdxInByte = idx % tritsInByte;
    return tritsetSupport(arrIdx, tritIdxInByte, this);
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
    // возможны ошибки связанные с доступом по несуществующему индексу
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

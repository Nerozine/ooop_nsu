#include "Tritset.h"


Tritset &Tritset::operator=(const Tritset &secondOperand) {
    if (this == &secondOperand) {
        return *this;
    }

    auto *tempArr = new u__int[secondOperand.arrSize]();
    delete[] this->arr;

    this->arr = tempArr;
    this->arrSize = secondOperand.arrSize;
    this->arrLength = secondOperand.arrLength;
    this->lastIndexInTrits = secondOperand.lastIndexInTrits;

    memcpy(this->arr, secondOperand.arr, arrSize * sizeof(u__int));

    return *this;
}


Tritset::Tritset():
    arr(nullptr),
    arrSize(0),
    arrLength(0),
    lastIndexInTrits(0) {}


Tritset::~Tritset() {
    delete[] arr;
}


trit Tritset::getTritByIndex(u__int index) const {
    //returns trit:tUnknown if index > lastIndexInTrits
    if (lastIndexInTrits < index || (*this)[index] == trit::tUnknown) {
        return trit::tUnknown;
    }
    if ((*this)[index] == trit::tFalse) {
        return trit::tFalse;
    }
    return trit::tTrue;
}


u__int Tritset::getMaxIndexInTrits(const Tritset &a, const Tritset &b) {
    if (a.lastIndexInTrits > b.lastIndexInTrits) {
        return a.lastIndexInTrits;
    }
    return b.lastIndexInTrits;
}


u__int  Tritset::getArrMaxSize(const Tritset &a, const Tritset &b) {
    if (a.arrSize > b.arrSize) {
        return a.arrSize;
    }
    return b.arrSize;
}


Tritset Tritset::operator&(const Tritset &secondOperand) const {
    Tritset result(tritsInUnsignedInt * getArrMaxSize(*this, secondOperand));
    u__int maxLastIndexInTrits = getMaxIndexInTrits(*this, secondOperand);

    for (u__int i = 0; i <= maxLastIndexInTrits; i++) {
        result[i] =  this->getTritByIndex(i) & secondOperand.getTritByIndex(i);
    }

    return result;
}


Tritset Tritset::operator|(const Tritset &secondOperand) const {
    Tritset result(tritsInUnsignedInt * getArrMaxSize(*this, secondOperand));
    u__int maxLastIndexInTrits = getMaxIndexInTrits(*this, secondOperand);

    for (u__int i = 0; i <= maxLastIndexInTrits; i++) {
        result[i] =  this->getTritByIndex(i) | secondOperand.getTritByIndex(i);
    }

    return result;
}


Tritset Tritset::operator!() const {
    Tritset result(tritsInUnsignedInt * this->arrLength);

    for (u__int i = 0; i <= this->lastIndexInTrits; i++) {
        result[i] = !this->getTritByIndex(i);
    }

    return result;
}


trit Tritset::operator[](u__int idx) const {
    if (idx > lastIndexInTrits) {
        return trit::tUnknown;
    }

    u__int arrIndex = idx / tritsInUnsignedInt;
    u__int tritIndexInByte = idx % tritsInUnsignedInt;

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


Tritset::Tritset(int n):
    arr(new u__int[n / sizeof(u__int) / 4 + 1]()),
    arrSize(n / sizeof(u__int) / 4 + 1),
    lastIndexInTrits(0),
    arrLength(0) {}


Tritset::Tritset(const Tritset &set):
    arr(new u__int[set.arrSize]()),
    arrSize(set.arrSize),
    lastIndexInTrits(set.lastIndexInTrits),
    arrLength(set.arrLength) {
    memcpy(arr, set.arr, (set.arrLength + 1) * sizeof(u__int));
}


TritsetSupport Tritset::operator[](u__int idx) {
    u__int arrIdx = idx / tritsInUnsignedInt;
    u__int tritIdxInByte = idx % tritsInUnsignedInt;
    return TritsetSupport(arrIdx, tritIdxInByte, this);
}


u__int Tritset::capacity() {
    return arrSize * tritsInUnsignedInt;
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


void Tritset::resetLastIndexInTrits(u__int index) {
    if (index > 1) {
        lastIndexInTrits = index - 1;
    }
    else {
        lastIndexInTrits = 0;
    }
}


void Tritset::trim(u__int lastIdx) {
    // forgets all trits from lastIdx including lastidx

    if (lastIdx > lastIndexInTrits) {
        return;
    }

    // lastIdx and lastIndexInTrits is not from the same u__int
    if (lastIndexInTrits - lastIdx >= tritsInUnsignedInt) {
        u__int loopBorder =  lastIndexInTrits / tritsInUnsignedInt + 1;
        for (u__int i = lastIdx / tritsInUnsignedInt + 1; i < loopBorder; i++) {
            arr[i] = 0;
        }
    }

    // now we need to forget trits only form the same unsigned int
    for (u__int i = lastIdx; i <= lastIndexInTrits; i++) {
        (*this)[i] = trit::tUnknown;
    }

    this->resetLastIndexInTrits(lastIdx);
    arrLength = lastIdx / tritsInUnsignedInt + 1;
}


void Tritset::shrink() {
    // memory free from the last seted trit
    auto newArr = new u__int[arrLength + 1]();
    memcpy(newArr, this->arr, (arrLength + 1) * sizeof(u__int));
    delete [] this->arr;
    this->arr = newArr;
    this->arrSize = arrLength + 1;
}


void Tritset::expandArray(u__int newSizeInUiBytes) {
    auto newArr = new u__int[newSizeInUiBytes]();
    if (this->arr != nullptr) {
        memcpy(newArr, this->arr, (this->arrLength + 1) * sizeof(u__int));
        delete [] this->arr;
    }
    this->arr = newArr;
    this->arrSize = newSizeInUiBytes;
}


TritsetSupport &TritsetSupport::operator=(trit operand) {
    if (operand == trit::tUnknown && (arrIndex > ptr->arrSize || ptr->arrSize == 0)) {
        return *this;
    }

    // expand arr if not enough size and operand != tUnknown
    if (operand != trit::tUnknown && arrIndex >= ptr->arrSize) {
        ptr->expandArray(arrIndex + 1);
        ptr->arrLength = arrIndex;
    }

    if (ptr->arrLength < arrIndex) {
        // seting new arrLength
        ptr->arrLength = arrIndex;
    }

    u__int tritsInUnsignedInt = sizeof(u__int) * 4;
    if (ptr->lastIndexInTrits < arrIndex * tritsInUnsignedInt + tritIndexInByte) {
        // seting new lastIndexInTrits
        ptr->lastIndexInTrits = arrIndex * tritsInUnsignedInt + tritIndexInByte;
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

    if (arrIndex * tritsInUnsignedInt + tritIndexInByte == ptr->lastIndexInTrits && operand == trit::tUnknown
        && ptr->lastIndexInTrits != 0) {
        ptr->resetLastIndexInTrits();
    }

    return *this;
}


void Tritset::resetLastIndexInTrits() {
    u__int j = this->lastIndexInTrits / tritsInUnsignedInt;
    while (this->arr[j] == 0) {
        if (j == 0) {
            this->lastIndexInTrits = 0;
            this->arrLength = 0;
            return;
        }
        j--;
    }

    for (u__int i = (j * tritsInUnsignedInt) + tritsInUnsignedInt - 1;; i--) {
        if ((*this)[i] != trit::tUnknown || i == 0) {
            this->lastIndexInTrits = i;
            this->arrLength = i / tritsInUnsignedInt;
            break;
        }
    }
}


TritsetSupport::TritsetSupport(int arrIdx, int tritIdx, Tritset *p):
    arrIndex(arrIdx),
    tritIndexInByte(tritIdx),
    ptr(p) {}


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
    return !(*this == secondOperand);
}


TritsetSupport &TritsetSupport::operator=(const TritsetSupport &t) {
    if (this == &t) {
        return *this;
    }

    u_int tmp = 0;
    tmp |= (3u << (2 * t.tritIndexInByte));

    tmp &= (t.ptr->arr[t.arrIndex]);
    tmp >>= (2 * t.tritIndexInByte);

    switch (tmp) {
        case 0: {
            (*(this->ptr))[arrIndex * sizeof(u__int) * 4 + tritIndexInByte] = trit::tUnknown;
            break;
        }
        case 1: {
            (*(this->ptr))[arrIndex * sizeof(u__int) * 4 + tritIndexInByte] = trit::tTrue;
            break;
        }
        case 2: {
            (*(this->ptr))[arrIndex * sizeof(u__int) * 4 + tritIndexInByte] = trit::tFalse;
            break;
        }
        default: {
            exit(14);
        }
    }

    return *this;
}

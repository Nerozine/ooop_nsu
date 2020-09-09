//
// Created by alexandr on 09.09.2020.
//

#include "tritset.h"

/*
triset () : arr(new u__int[10]) , arrSize(10 * sizeof(u__int)) , arrLength(0) { }
explicit triset (int size) : arr(new u__int[size / 16]) , arrSize(size * sizeof(u__int)), arrLength(0) { }
~triset () {
    delete[] arr;
}
 нужно подумать про конструкторы */


tritset &tritset::operator=(const tritset &secondOperand) {
    if (this == &secondOperand) {
        return *this;
    }

    if (arrSize != secondOperand.arrSize) {
        u__int *tempArr = new u__int[secondOperand.arrSize];
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

tritset tritset::operator[](u__int idx) {
    return tritset();
}


/*
triset () : arr(new u__int[10]) , arrSize(10 * sizeof(u__int)) , arrLength(0) { }
explicit triset (int size) : arr(new u__int[size / 16]) , arrSize(size * sizeof(u__int)), arrLength(0) { }
~triset () {
    delete[] arr;
}
 нужно подумать про конструкторы */

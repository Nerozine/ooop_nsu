#include "trit.h"


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
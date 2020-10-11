#ifndef OOOP_NSU_TRIT_H
#define OOOP_NSU_TRIT_H
#include <cstdlib>

enum trit {tFalse = 2, tUnknown = 0, tTrue = 1};


trit operator!(const trit &operand);
trit operator|(const trit &firstOperand, const trit &secondOperand);
trit operator&(const trit &firstOperand, const trit &secondOperand);


#endif //OOOP_NSU_TRIT_H

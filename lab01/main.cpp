#include <iostream>
#include "tritset.h"
#include <algorithm>

#include <string>
using namespace std;

int main() {
    tritset test(10,10);
    test[0] = trit::tritFalse;
    if (test[3321] == trit::tritFalse) {
        cout << "It's working!" << endl;
    }
    else {
        cout << "It's not working!" << endl;
    }


    return 0;
}
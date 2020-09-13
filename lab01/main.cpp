#include <iostream>
#include "tritset.h"


using namespace std;


int main() {
    tritset set(1000);
    cout << "current arr length: " << set.capacity() << endl;
    set[1000000000] = trit::tritTrue;
    cout << "current arr length: " << set.capacity() << endl;
    if (set[1000000000] == trit::tritTrue) {
        cout << "It's working!" << endl;
    }
    else {
        cout << "It's not working!" << endl;
    }

    return 0;
}
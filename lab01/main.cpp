#include <iostream>
#include "tritset.h"

using namespace std;

int main() {
    cout << sizeof(u__int) * 8 << endl; // 4 * 8 = 32
    cout << 32 / 2 << endl; // 16
    int *test  = new int[10];
    for (int i = 0; i < 10; i++) {
        cout << test[i] << " ";
    }
    return 0;
}
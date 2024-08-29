#include <iostream>
#include "MPointer.h"

using namespace std;

int main() {
    MPointer<int> myPtr = MPointer<int>::New();
    *myPtr = 42;
    cout <<"El valor de myPtr es:" << *myPtr << endl;

    return 0;

}

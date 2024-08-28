#include <iostream>
#include "MPointer.h"

using namespace std;

int main()
{
    MPointer<int> p(new int(87));
    cout <<"Valor: " << *p << endl;

}
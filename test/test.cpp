#include <iostream>
#include "MPointer.h"

using namespace std;

int main() {
    // Crear instancias de MPointer
    MPointer<int> myPtr1 = MPointer<int>::New();
    MPointer<int> myPtr2 = MPointer<int>::New();

    // Asignar valor a myPtr1
    *myPtr1 = 10;
    cout << "Valor en myPtr1: " << *myPtr1 << endl; // Debería mostrar 10

    // Asignar myPtr1 a myPtr2
    myPtr2 = myPtr1;
    cout << "Valor en myPtr2: " << *myPtr2 << endl; // Debería mostrar 10 (el mismo valor que myPtr1)

    // Asignar valor directamente a myPtr2
    myPtr2 = 20;
    cout << "Nuevo valor en myPtr1: " << *myPtr1 << endl; // Debería mostrar 20
    cout << "Nuevo valor en myPtr2: " << *myPtr2 << endl; // Debería mostrar 20

    return 0;
}

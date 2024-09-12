#include <iostream>
#include "../library/MPointer.h"

using namespace std;

// Definir algunas estructuras y tipos para las pruebas
struct MiStruct {
    int a;
    double b;
};

// Función para imprimir los valores de MiStruct
void imprimirMiStruct(const MiStruct& s) {
    cout << "MiStruct: a = " << s.a << ", b = " << s.b << endl;
}

int main() {
    // Prueba 1: Trabajando con enteros
    cout << "Prueba 1: Trabajando con enteros" << endl;
    MPointer<int> intPtr1 = MPointer<int>::New();
    MPointer<int> intPtr2 = MPointer<int>::New();

    *intPtr1 = 10;
    cout << "Valor en intPtr1: " << *intPtr1 << endl; // Debería mostrar 10

    // Asignar intPtr1 a intPtr2 (shallow copy)
    intPtr2 = intPtr1;
    cout << "Valor en intPtr2 despues de asignar intPtr1: " << *intPtr2 << endl; // Debería mostrar 10

    // Asignar un nuevo valor a intPtr2
    *intPtr2 = 20;
    cout << "Nuevo valor en intPtr1: " << *intPtr1 << endl; // Debería mostrar 20
    cout << "Nuevo valor en intPtr2: " << *intPtr2 << endl; // Debería mostrar 20

    // Prueba 2: Trabajando con estructuras
    cout << "\nPrueba 2: Trabajando con estructuras" << endl;
    MPointer<MiStruct> structPtr1 = MPointer<MiStruct>::New();
    MPointer<MiStruct> structPtr2 = MPointer<MiStruct>::New();

    // Asignar valores a la estructura
    (*structPtr1).a = 10;
    (*structPtr1).b = 99.99;

    // Imprimir valores de structPtr1
    imprimirMiStruct(*structPtr1);

    // Asignar structPtr1 a structPtr2 (shallow copy)
    structPtr2 = structPtr1;
    cout << "Valores en structPtr2 despues de asignar structPtr1:" << endl;
    imprimirMiStruct(*structPtr2); // Debería mostrar 10 y 99.99

    // Cambiar valores en structPtr2
    (*structPtr2).a = 20;
    (*structPtr2).b = 55.55;

    // Imprimir valores después de modificar structPtr2
    cout << "Valores en structPtr1 despues de modificar structPtr2:" << endl;
    imprimirMiStruct(*structPtr1); // Debería mostrar 20 y 55.55
    cout << "Valores en structPtr2 despues de modificacion:" << endl;
    imprimirMiStruct(*structPtr2); // Debería mostrar 20 y 55.55

    // Prueba 3: Probando el movimiento de punteros
    cout << "\nPrueba 3: Probando el movimiento de punteros" << endl;
    MPointer<int> intPtr3 = MPointer<int>::New();
    *intPtr3 = 50;
    cout << "Valor en intPtr3 antes de mover: " << *intPtr3 << endl;

    // Mover intPtr3 a intPtr4
    MPointer<int> intPtr4 = std::move(intPtr3);
    cout << "Valor en intPtr4 despues de mover: " << *intPtr4 << endl;

    // Comprobar que intPtr3 ya no es válido
    if (intPtr3 == nullptr) {
        cout << "intPtr3 se ha movido correctamente y ahora es nulo." << endl;
    }

    // Prueba 4: Validar recolección automática de basura
    cout << "\nPrueba 4: Validar recoleccion automatica de basura" << endl;
    {
        MPointer<int> tempPtr = MPointer<int>::New();
        *tempPtr = 100;
        cout << "Valor en tempPtr: " << *tempPtr << endl;
        // tempPtr se eliminará al salir de este bloque
    }

    return 0;
}

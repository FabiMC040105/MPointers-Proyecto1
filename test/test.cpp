#include <iostream>
#include "doublylinkedlist.h"

using namespace std;

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
    cout << "Valor en intPtr1: " << *intPtr1 << endl;

    // Asignar intPtr1 a intPtr2 (shallow copy)
    intPtr2 = intPtr1;
    cout << "Valor en intPtr2 despues de asignar intPtr1: " << *intPtr2 << endl;

    // Asignar un nuevo valor a intPtr2
    *intPtr2 = 20;
    cout << "Nuevo valor en intPtr1: " << *intPtr1 << endl;
    cout << "Nuevo valor en intPtr2: " << *intPtr2 << endl;


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
    imprimirMiStruct(*structPtr2);

    // Cambiar valores en structPtr2
    (*structPtr2).a = 20;
    (*structPtr2).b = 55.55;

    // Imprimir valores después de modificar structPtr2
    cout << "Valores en structPtr1 despues de modificar structPtr2:" << endl;
    imprimirMiStruct(*structPtr1);
    cout << "Valores en structPtr2 despues de modificacion:" << endl;
    imprimirMiStruct(*structPtr2);


    // Prueba 3: Movimiento de punteros
    cout << "\nPrueba 3: Probando el movimiento de punteros" << endl;
    MPointer<int> intPtr3 = MPointer<int>::New();
    *intPtr3 = 50;
    cout << "Valor en intPtr3 antes de mover: " << *intPtr3 << endl;

    // Mover intPtr3 a intPtr4
    MPointer<int> intPtr4 = move(intPtr3);
    cout << "Valor en intPtr4 despues de mover: " << *intPtr4 << endl;

    // Comprobar que intPtr3 ya no es válido
    if (intPtr3 == nullptr) {
        cout << "intPtr3 se ha movido correctamente y ahora es nulo." << endl;
    }

    // Prueba 4: Recolección automática de basura
    cout << "\nPrueba 4: Validar recoleccion automatica de basura" << endl;
    {
        MPointer<int> tempPtr = MPointer<int>::New();
        *tempPtr = 100;
        cout << "Valor en tempPtr: " << *tempPtr << endl;

    }



    DoublyLinkedList<int> list;

    // Agregar elementos a la lista
    list.append(3);
    list.append(1);
    list.append(4);
    list.append(5);
    list.append(9);
    list.append(2);

    // Prueba BubbleSort
    cout << "Prueba BubbleSort:" << endl;
    list.bubbleSort(list);
    list.haciadelante();

    // Reiniciar lista
    list.clear();
    list.append(1);
    list.append(3);
    list.append(4);
    list.append(5);
    list.append(9);
    list.append(7);
    list.append(2);

    // Prueba InsertionSort
    cout << "Prueba InsertionSort:" << endl;
    list.insertionSort(list);
    list.haciadelante();  // Verificar si está ordenada de menor a mayor

    // Reiniciar lista
    list.clear();
    list.append(3);
    list.append(1);
    list.append(4);
    list.append(1);
    list.append(5);
    list.append(9);
    list.append(2);

    // Prueba QuickSort
    cout << "Prueba QuickSort:" << endl;
    int hi = list.getLength();
    list.quickSort(list, 0, hi - 1);
    list.haciadelante();  // Verificar si está ordenada de menor a mayor

    return 0;
}

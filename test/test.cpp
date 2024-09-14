#include <iostream>
#include "doublylinkedlist.h"

using namespace std;

int main() {
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

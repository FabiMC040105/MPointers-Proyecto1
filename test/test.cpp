#include <iostream>
#include "doublylinkedlist.h"
#include "Quicksort.h"
#include "Insertionsort.h"
#include "Bubblesort.h"

using namespace std;

int main() {
    DoublyLinkedList<int> list;
    list.append(10);
    list.append(20);
    list.append(30);

    list.haciadelante();
    list.haciaatras();
}

#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include "doublylinkedlist.h"

template <typename T>
void bubbleSort(DoublyLinkedList<T>& list) {
    bool swapped;
    MPointer<typename DoublyLinkedList<T>::Node> i;
    MPointer<typename DoublyLinkedList<T>::Node> j;

    do {
        swapped = false;
        i = list.getHead();
        while (i->next) {
            j = i->next;
            if (*i->data > *j->data) {
                std::swap(i->data, j->data);
                swapped = true;
            }
            i = j;
        }
    } while (swapped);
}

#endif //BUBBLESORT_H

#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "doublylinkedlist.h"

template <typename T>
MPointer<typename DoublyLinkedList<T>::Node> partition(MPointer<typename DoublyLinkedList<T>::Node> low,
                                                     MPointer<typename DoublyLinkedList<T>::Node> high) {
    T pivot = high->data;
    MPointer<typename DoublyLinkedList<T>::Node> i = low->prev;

    for (MPointer<typename DoublyLinkedList<T>::Node> j = low; j != high; j = j->next) {
        if (*j->data , pivot) {  // Corrección aquí
            i = (i == nullptr) ? low : i->next;
            std::swap(i->data, j->data);
        }
    }
    i = (i == nullptr) ? low : i->next;
    std::swap(i->data, high->data);
    return i;
}

template <typename T>
void quickSort(MPointer<typename DoublyLinkedList<T>::Node> low,
               MPointer<typename DoublyLinkedList<T>::Node> high) {
    if (high && low != high && low != high->next) {
        MPointer<typename DoublyLinkedList<T>::Node> p = partition<T>(low, high);
        if (p && p->prev) {
            quickSort(low, p->prev);
        }
        if (p && p->next) {
            quickSort(p->next, high);
        }
    }
}

#endif //QUICKSORT_H

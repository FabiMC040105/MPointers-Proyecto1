#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

#include "doublylinkedlist.h"

template <typename T>
void insertionSort(DoublyLinkedList<T>& list) {
    MPointer<typename DoublyLinkedList<T>::Node> sorted = nullptr;
    MPointer<typename DoublyLinkedList<T>::Node> current = list.getHead();

    while (current) {
        MPointer<typename DoublyLinkedList<T>::Node> next = current->next;
        if (!sorted || *current->data <= *sorted->data) {
            current->next = sorted;
            if (sorted) sorted->prev = current;
            sorted = current;
            sorted->prev = nullptr;
        } else {
            MPointer<typename DoublyLinkedList<T>::Node> s = sorted;
            while (s->next && *current->data > *s->next->data) {
                s = s->next;
            }
            current->next = s->next;
            if (s->next) s->next->prev = current;
            s->next = current;
            current->prev = s;
        }
        current = next;
    }
    list.getHead() = sorted;
    if (sorted) {
        MPointer<typename DoublyLinkedList<T>::Node> temp = sorted;
        while (temp->next) temp = temp->next;
        list.getTail() = temp;
    }
}

#endif //INSERTIONSORT_H

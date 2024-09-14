#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include "../library/MPointer.h"
#include <iostream>

template <typename T>
class DoublyLinkedList {
public:
    struct Node {
    public:
        MPointer<T> data = MPointer<T>::New();
        MPointer<Node> prev = nullptr;
        MPointer<Node> next = nullptr;

        Node() = default;
    };

    int length = 0;

    MPointer<Node> head;
    MPointer<Node> tail;

    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    ~DoublyLinkedList() {
        clear();
    }

    void append(const T& value) {
        MPointer<Node> newNode = MPointer<Node>::New();
        newNode->data = value;
        if (tail) {
            tail->next = newNode;
            newNode->prev = tail;
        } else {
            head = newNode;
        }
        tail = newNode;
        length++;
    }

    void clear() {
        MPointer<Node> current = head;
        while (current) {
            MPointer<Node> next = current->next;
            current->prev = nullptr;
            current->next = nullptr;
            current = next;
        }
        head = tail = nullptr;
        length = 0;
    }

    int getLength(){ return length; }

    void haciadelante() const {
        MPointer<Node> current = head;
        while (current != nullptr) {
            std::cout << "Nodo en impresion hacia adelante: " << *current->data << endl;
            current = current->next;
        }
        std::cout << std::endl;
    }

    void haciaatras() const {
        MPointer<Node> current = tail;
        while (current != nullptr) {
            std::cout << "Nodo en impresion hacia atras: " << *current->data << endl;
            current = current->prev;
        }
        std::cout << std::endl;
    }

    void bubbleSort(DoublyLinkedList<T>& list) {
        bool swapped;
        MPointer<Node> ptr1 = nullptr;
        MPointer<Node> lptr = nullptr;

        if (list.getHead() == nullptr)
            return;

        do {
            swapped = false;
            ptr1 = list.getHead();

            while (ptr1->next != nullptr) {
                if (*ptr1->data > *ptr1->next->data) {
                    std::swap(ptr1->data, ptr1->next->data);
                    swapped = true;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1;
        } while (swapped);
    }

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

    MPointer<Node> getNodeAt(int index) const {
        if (index < 0 || index >= length) {
            throw out_of_range("Fuera de rango");
        }
        MPointer<Node> current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current;
    }

    int get(int index) const {
        return *getNodeAt(index)->data;
    }

    void set(int index, int val) {
        MPointer<Node> node = getNodeAt(index);
        node->data = val;
    }

    int partition(DoublyLinkedList& arr, int low, int high) {
        int pivot = arr.get(high);
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (arr.get(j) < pivot) {
                i++;
                int temp1 = arr.get(i);
                int temp2 = arr.get(j);
                arr.set(i, temp2);
                arr.set(j, temp1);
            }
        }

        int temp1 = arr.get(i + 1);
        int temp2 = arr.get(high);
        arr.set(i + 1, temp2);
        arr.set(high, temp1);

        return i + 1;
    }


    void quickSort(DoublyLinkedList& arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }

    MPointer<Node> getHead() const { return head; }
    void setHead(MPointer<Node> newHead) const { *head = *newHead; }
    MPointer<Node> getTail() const { return tail; }
};


#endif // DOUBLYLINKEDLIST_H

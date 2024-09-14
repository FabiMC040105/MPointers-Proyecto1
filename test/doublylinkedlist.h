#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include "../library/MPointer.h"
#include <iostream>

template <typename T>
class DoublyLinkedList {
private:
    struct Node {
    public:
        MPointer<T> data = MPointer<T>::New();
        MPointer<Node> prev = nullptr;
        MPointer<Node> next = nullptr;

        Node() = default;
    };

    MPointer<Node> head;
    MPointer<Node> tail;

public:
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
    }

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

    MPointer<Node> getHead() const { return head; }
    MPointer<Node> getTail() const { return tail; }
};


#endif // DOUBLYLINKEDLIST_H

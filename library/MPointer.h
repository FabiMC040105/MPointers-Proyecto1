#ifndef POINTERWRAPPER_H
#define POINTERWRAPPER_H

#include <iostream>
#include "MPointerGC.h"

using namespace std;

template <typename T>
class MPointer {
private:
    T* ptr;      // Puntero real a la memoria
    int id;      // ID asignado por el Garbage Collector

    // Constructor privado utilizado por New()
    MPointer() : ptr(new T()), id(MPointerGC::getInstance().registerMemory(ptr)) {
        // cout << "MPointer created with ID: " << id << endl;
    }

public:
    // Constructor de copia
    MPointer(const MPointer& other) : ptr(other.ptr), id(other.id) {
        MPointerGC::getInstance().addReference(id);
        // cout << "MPointer copied with ID: " << id << endl;
    }

    // Constructor de movimiento
    MPointer(MPointer&& other) noexcept : ptr(other.ptr), id(other.id) {
        other.ptr = nullptr;
        other.id = -1;
        // cout << "MPointer moved with ID: " << id << endl;
    }

    // Constructor de asignación desde nullptr
    MPointer(nullptr_t) : ptr(nullptr), id(-1) {
        // cout << "MPointer created from nullptr" << endl;
    }

    // Destructor
    ~MPointer() {
        if (ptr) {
            MPointerGC::getInstance().removeReference(id);
            // cout << "MPointer destroyed with ID: " << id << endl;
        }
    }

    // Operador de acceso a miembros
    T* operator->() const {
        return ptr;
    }

    // Operador de desreferencia
    T& operator*() const {
        return *ptr;
    }

    // Sobrecarga del operador de asignación para copiar
    MPointer<T>& operator=(const MPointer<T>& other) {
        if (this != &other) {
            if (ptr) {
                MPointerGC::getInstance().removeReference(id);
            }

            ptr = other.ptr;
            id = other.id;

            MPointerGC::getInstance().addReference(id);
            // cout << "MPointer assigned (copy) with ID: " << id << endl;
        }
        return *this;
    }

    // Sobrecarga del operador de asignación para mover
    MPointer& operator=(MPointer&& other) noexcept {
        if (this != &other) {
            if (ptr) {
                MPointerGC::getInstance().removeReference(id);
            }

            ptr = other.ptr;
            id = other.id;

            other.ptr = nullptr;
            other.id = -1;
            // cout << "MPointer assigned (move) with ID: " << id << endl;
        }
        return *this;
    }

    // Sobrecarga del operador de asignación para asignar un valor
    MPointer<T>& operator=(const T& value) {
        if (ptr) {
            *ptr = value;
            // cout << "MPointer value assigned with ID: " << id << endl;
        } else {
            throw runtime_error("Intento de asignar valor a un puntero nulo");
        }
        return *this;
    }

    static MPointer<T> New() {
        MPointerGC::getInstance().initialize(5);
        return MPointer<T>();
    }

    bool operator==(nullptr_t) const {
        return ptr == nullptr;
    }

    bool operator!=(nullptr_t) const {
        return ptr != nullptr;
    }

    // para poder usar en sort
    bool operator<(const MPointer<T>& other) const {
        return *ptr < *other.ptr;
    }

    explicit operator bool() const {
        return ptr != nullptr;
    }
};

#endif // POINTERWRAPPER_H

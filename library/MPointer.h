#ifndef POINTERWRAPPER_H
#define POINTERWRAPPER_H

#include <iostream>
#include "MPointerGC.h"

using namespace std;

template <typename T>
class MPointer {
private:
    T* ptr;
    int id;

    // Constructor privado para la creación a través de New()
    MPointer() : ptr(new T()), id(MPointerGC::getInstance().registerPointer<T>(ptr)) {}

public:
    // Constructor de copia
    MPointer(const MPointer& other) : ptr(other.ptr), id(other.id) {
        MPointerGC::getInstance().addReference(id);
    }

    // Constructor de movimiento
    MPointer(MPointer&& other) noexcept : ptr(other.ptr), id(other.id) {
        other.ptr = nullptr;
        other.id = -1; //
    }

    // Destructor
    ~MPointer() {
        if (ptr) {
            MPointerGC::getInstance().removeReference<T>(id);
        }
    }

    // Operador de desreferencia
    T& operator*() const {
        return *ptr;
    }

    // Operador & para obtener el puntero interno
    T* operator&() const {
        return ptr;
    }

    // Sobrecarga del operador de asignación para copiar punteros y actualizar el GC
    MPointer<T>& operator=(const MPointer<T>& other) {
        if (this != &other) {
            if (ptr) {
                MPointerGC::getInstance().removeReference<T>(id);
            }

            ptr = other.ptr;
            id = other.id;

            MPointerGC::getInstance().addReference(id);
        }
        return *this;
    }

    // Permite la movida
    MPointer& operator=(MPointer&& other) noexcept {
        if (this != &other) {
            if (ptr) {
                MPointerGC::getInstance().removeReference<T>(id);
            }

            ptr = other.ptr;
            id = other.id;

            other.ptr = nullptr;
            other.id = -1;
        }
        return *this;
    }

    // Sobrecarga del operador de asignación para tipos diferentes
    MPointer& operator=(const T& value) {
        if (ptr) {
            *ptr = value;
        }
        return *this;
    }

    // Función para crear un nuevo MPointer
    static MPointer<T> New() {
        return MPointer<T>();
    }
};

#endif // POINTERWRAPPER_H

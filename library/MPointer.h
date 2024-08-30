#ifndef POINTERWRAPPER_H
#define POINTERWRAPPER_H

#include <iostream>

using namespace std;

template <typename T>
class MPointer {

private:
    T* ptr;
    // Constructor para la creación a través de New()
    MPointer() {
        this->ptr = new T();
    }

public:

    // Destructor
    ~MPointer() {
        delete ptr;
    }
    // Operador de desreferencia
    T& operator*() const {
        return *ptr;
    }

    // Sobrecarga del operador &
    T& operator&() const {  // Devolver el valor almacenado en lugar del puntero
        return *ptr;
    }

    void reset(T* p = nullptr) {
        delete ptr; // Libera la memoria antes de reasignar
        ptr = p; // Reasigna el puntero
    }
    // Prohibe la copia para evitar problemas de doble liberación de memoria
    MPointer(const MPointer&) = delete;
    MPointer& operator=(const MPointer&) = delete;

    // Permite la movida
    MPointer(MPointer&& other) : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    MPointer& operator=(MPointer&& other) {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    // Función para crear un nuevo MPointer
    static MPointer<T> New() {
        return MPointer<T>(new T());
    }
};

#endif // POINTERWRAPPER_H

#ifndef POINTERWRAPPER_H
#define POINTERWRAPPER_H

#include <iostream>

using namespace std;

template <typename T>
class MPointer {

private:
    T* ptr;

public:
    //Este es mi constructor
    MPointer(T* p = nullptr) : ptr(p) {}
    //Destructor
    ~MPointer() {
        delete ptr;
    }
    //Operador de desreferencia (podemos acceder al valor al que apunta ptr y al devolver T& podemos modificar el valor apuntado directamente)
    T& operator*() const {
        return *ptr;
    }
    //Operador de acceso (permite acceder a miembros del objeto apuntado)
    T* operator->() const {
        return ptr;
    }
    // Sobrecarga del operador &
    T* operator&() const {
        return ptr;
    }
    //Metodo para obtener el puntero subyacente (es util si necesitamos trabajar con el puntero directamente sin modificarlo)
    T* get() const {
        return ptr;
    }
    //Metodo para liberar la memoria ocupada por el puntero actual y asignarle un nuevo puntero
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
};


#endif //POINTERWRAPPER_H

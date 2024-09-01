#ifndef MPOINTERGC_H
#define MPOINTERGC_H

#include <unordered_map>
#include <iostream>

using namespace std;

class MPointerGC {
private:
    unordered_map<int, int> refCountMap; // Mapa para llevar el conteo de referencias
    unordered_map<int, void*> pointerMap; // Mapa para almacenar los punteros
    int currentId;

    // Constructor privado para el patrón Singleton
    MPointerGC() : currentId(0) {}

public:
    // Prohibir la copia y la asignación
    MPointerGC(const MPointerGC&) = delete;
    MPointerGC& operator=(const MPointerGC&) = delete;

    // Metodo para obtener la unica instancia del MPointerGC
    static MPointerGC& getInstance() {
        static MPointerGC instance;
        return instance;
    }

    // Metodo para registrar un puntero y devolver un ID unico
    template <typename T>
    int registerPointer(T* ptr) {
        int id = currentId++;
        pointerMap[id] = ptr;
        refCountMap[id] = 1;
        return id;
    }

    // Metodo para incrementar el conteo de referencias
    void addReference(int id) {
        refCountMap[id]++;
    }

    // Metodo para decrementar el conteo de referencias
    template <typename T>
    void removeReference(int id) {
        if (--refCountMap[id] == 0) {
            delete static_cast<T*>(pointerMap[id]); // Se asume que es de tipo `T*`
            pointerMap.erase(id);
            refCountMap.erase(id);
        }
    }

    // Metodo para obtener un puntero por su ID
    void* getPointer(int id) {
        return pointerMap[id];
    }
};

#endif // MPOINTERGC_H

#ifndef M_POINTER_GC_H
#define M_POINTER_GC_H

#include <list>
#include <thread>
#include <chrono>
#include <iostream>
#include <mutex>

using namespace std;

class MPointerGC {
private:
    struct MemoryEntry {
        void* memory;
        int id;
        int refCount;
    };

    list<MemoryEntry> memoryRegistry;
    int memoryIdAutoIncrement = 0;
    bool running = false;
    thread gcThread;
    mutex gcMutex;

    MPointerGC() {}

    void startGC(int intervalSeconds) {
        running = true;
        gcThread = thread([this, intervalSeconds]() {
            while (running) {
                this_thread::sleep_for(chrono::seconds(intervalSeconds));
                collectGarbage();
            }
        });
    }

    void collectGarbage() {
        lock_guard<mutex> lock(gcMutex); // Bloquear acceso a la lista
        cout << "Revisando las referencias en el Garbage Collector..." << endl;
        for (auto it = memoryRegistry.begin(); it != memoryRegistry.end(); ) {
            if (it->refCount <= 0) {
                // Liberar memoria si el contador de referencias es 0
                delete static_cast<char*>(it->memory);  // Eliminar memoria asignada
                it = memoryRegistry.erase(it);  // Eliminar de la lista
            } else {
                ++it;  // Avanzar en la lista
            }
        }
    }

public:
    // Singleton para obtener la única instancia de MPointerGC
    static MPointerGC& getInstance() {
        static MPointerGC instance;
        return instance;
    }

    // Inicializar el Garbage Collector
    void initialize(int intervalSeconds) {
        if (!running) {
            startGC(intervalSeconds);  // Iniciar el hilo del GC
        }
    }

    // Registrar nueva memoria y asignar un ID
    int registerMemory(void* memory) {
        lock_guard<mutex> lock(gcMutex);  // Bloquear acceso a la lista
        memoryIdAutoIncrement += 1;
        int assignedId = memoryIdAutoIncrement;
        memoryRegistry.push_back({memory, assignedId, 1});  // Inicialmente con 1 referencia
        return assignedId;
    }

    // Aumentar el contador de referencias
    void addReference(int id) {
        lock_guard<mutex> lock(gcMutex);  // Bloquear acceso a la lista
        for (auto& entry : memoryRegistry) {
            if (entry.id == id) {
                entry.refCount++;
                return;
            }
        }
    }

    // Reducir el contador de referencias
    void removeReference(int id) {
        lock_guard<mutex> lock(gcMutex);  // Bloquear acceso a la lista
        for (auto it = memoryRegistry.begin(); it != memoryRegistry.end(); ++it) {
            if (it->id == id) {
                it->refCount--;
                if (it->refCount == 0) {
                    delete static_cast<char*>(it->memory);  // Liberar memoria
                    memoryRegistry.erase(it);  // Eliminar entrada de la lista
                }
                return;
            }
        }
    }

    // Buscar el ID asociado a una dirección de memoria
    int findId(void* memory) {
        lock_guard<mutex> lock(gcMutex);  // Proteger acceso
        for (const auto& entry : memoryRegistry) {
            if (entry.memory == memory) {
                return entry.id;
            }
        }
        return -1;
    }

    void stopGC() {
        running = false;
        if (gcThread.joinable()) {
            gcThread.join();  // Esperar a que el hilo termine
        }
    }

    ~MPointerGC() {
        stopGC();
    }
};

#endif // M_POINTER_GC_H

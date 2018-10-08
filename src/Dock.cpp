#include "Dock.h"

Dock::Dock(int id){
  semaphore = new Semaforo("bin/bash", 1, id);
}

Dock::~Dock() {
  semaphore->eliminar();
}

void Dock::lock() {
  semaphore->p();
}

void Dock::unlock() {
  semaphore->v();
}

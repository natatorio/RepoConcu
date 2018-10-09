#include "Dock.h"

Dock::Dock(int id, int init){
  semaphore = new Semaforo("bin/bash", 1, id, INITIALIZE);
  dockMem.crear("bin/bash", id, 1);
}

Dock::~Dock() {
  if(dockMem.liberar() == LIBERADA)  semaphore->eliminar();
}

void Dock::lock() {
  semaphore->p();
}

void Dock::unlock() {
  semaphore->v();
}

#include "Dock.h"

Dock::Dock(int id, int init) : semaphore("dock.cc", 1, id, init){
  dockMem.crear("dock.cc", id, 1);
}

Dock::~Dock() {
  //if(dockMem.liberar() == LIBERADA)
  dockMem.liberar();
}

void Dock::destroy(){
  semaphore.eliminar();
}

void Dock::lock() {
  semaphore.p();
}

void Dock::unlock() {
  semaphore.v();
}

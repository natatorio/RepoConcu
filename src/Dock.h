#ifndef DOCK_H_
#define DOCK_H_

#include "Semaforo.h"
#include "MemoriaCompartida.h"

class Dock {
public:
  Dock(int id, int init);
  ~Dock();

  void lock();
  void unlock();

private:
  Semaforo semaphore;
  MemoriaCompartida <int> dockMem;
};

#endif /* DOCK_H_ */

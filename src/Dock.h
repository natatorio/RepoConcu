#ifndef DOCK_H_
#define DOCK_H_

#include "Semaforo.h"

class Dock {
public:
  Dock(int id);
  ~Dock();

  void lock();
  void unlock();

private:
  Semaforo* semaphore;
};

#endif /* DOCK_H_ */

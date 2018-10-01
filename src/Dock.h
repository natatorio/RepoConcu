#ifndef DOCK_H_
#define DOCK_H_

#include "Ship.h"

class Dock {
private:
  void* shmem;
  int memid;
public:
  Dock(int id);
  virtual ~Dock();

  void addPassenger();
  int getState();
  int tryToMoorShip(Ship& ship);
};

#endif /* DOCK_H_ */

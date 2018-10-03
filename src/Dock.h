#ifndef DOCK_H_
#define DOCK_H_

#include "Ship.h"
#include "HumanResources.h"

class Dock {
private:
  int id;
  void* shmem;
  void* shmem_currp;
  int memid;
  int fd_passengers;
  int fd_ship;

public:
  Dock(int id);
  virtual ~Dock();

  void addPassenger(Passenger passenger);
  int getState();
  int tryToMoorShip(Ship& ship);
private:
  void buyTicket(Passenger passenger);
  void writePassenger(Passenger passenger);
  void lock(int fd);
  void unlock(int fd);

  void moorShip(Ship& ship);
  void sync();
  void endsync();
};

#endif /* DOCK_H_ */

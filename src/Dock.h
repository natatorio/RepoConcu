#ifndef DOCK_H_
#define DOCK_H_

#include "Ship.h"
#include "HumanResources.h"

class Dock {
private:
  int id;
  void* shmem;
  void* shmem_total_pass;
  void* shmem_current;
  int memid;
  int fd_passengers;
  int fd_ship;

public:
  Dock(int id);
  virtual ~Dock();

  // solo deberia llamarse desde el hilo que cree pasajeros (HumanResources)
  void addPassenger(Passenger passenger);
  // esto es llamado por los hilos de los ships.
  int tryToMoorShip(Ship& ship);

private:
  int getState();
  void buyTicket(Passenger passenger);
  void writePassenger(Passenger passenger);
  void lock(int fd);
  void unlock(int fd);

  void moorShip(Ship& ship);
  void sync();
  void endsync();
};

#endif /* DOCK_H_ */

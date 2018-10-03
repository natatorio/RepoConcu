#include "Dock.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include "Logger.h"
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FREE 0
#define OCCUPIED 1
#define BUY_TICKET_PROBABILITY 0.7
#define SHMEM_SIZE 1000

Logger logger("test");

Dock::Dock(int id) : id(id) {
  key_t key = ftok("/bin/bash", id);
  this->memid = shmget(key, SHMEM_SIZE, IPC_CREAT|0777);
  this->shmem = shmat(this->memid, NULL, 0);
  *(int*)this->shmem = FREE;
  this->shmem_total_pass = this->shmem + sizeof(int);
  //total passengers in queue
  *(int*)this->shmem_total_pass = 0;
  this->shmem_current = this->shmem_total_pass + sizeof(int);

  char str[30];
  sprintf(str, "tmp/passengers_%d", id);
  this->fd_passengers = open(str, O_CREAT | O_RDWR | O_TRUNC);
  sprintf(str, "tmp/ship_%d", id);
  this->fd_ship = open(str, O_CREAT | O_RDWR | O_TRUNC);
}

Dock::~Dock() {
  shmdt(this->shmem);
  shmctl(this->memid, IPC_RMID, NULL);
}

void Dock::addPassenger(Passenger passenger) {
  this->lock(this->fd_passengers);
  this->buyTicket(passenger);
  this->writePassenger(passenger);
  this->unlock(this->fd_passengers);
}

int Dock::tryToMoorShip(Ship& ship) {
  //TODO: cambiar funcionamiento y usar con mutex
  this->sync();
  if (this->getState() == OCCUPIED) {
    this->endsync();
    return 0;
  }
  this->moorShip(ship);
  this->endsync();
  return 1;
}

int Dock::getState() {
  int state = *(int*)this->shmem;
  return state;
}

void Dock::moorShip(Ship& ship) {
  *(int*)this->shmem = OCCUPIED;
}


void Dock::buyTicket(Passenger passenger) {
  if (passenger.ticket == 0 && rand() > BUY_TICKET_PROBABILITY) {
    //add id of dock
    std::string str("Dock : Passenger buy a ticket.");
    logger.write(str);
    passenger.ticket = 1;
  }
}

void Dock::writePassenger(Passenger passenger) {
  memcpy(this->shmem_current, (void*)passenger, sizeof(struct Passenger));
  this->shmem_current +=  sizeof(struct Passenger);
  *(int*)this->shmem_total_pass = *(int*)this->shmem_total_pass + 1;
  std::string str("Dock : Passenger pass through turnstile.");
  logger.write(str);
}

void Dock::lock(int fd) {
  struct flock fl;
  fl.l_whence = SEEK_SET;
  fl.l_start = 0;
  fl.l_len = 0;
  fl.l_type = F_WRLCK;
  fcntl(fd, F_SETLK, fl);
}

void Dock::unlock(int fd) {
  struct flock fl;
  fl.l_whence = SEEK_SET;
  fl.l_start = 0;
  fl.l_len = 0;
  fl.l_type = F_UNLCK;
  fcntl(fd, F_SETLK, fl);
}

void Dock::sync() {
  //TODO:reemplazar con mutex
  this->lock(this->fd_ship);
}

void Dock::endsync() {
  //TODO:reemplazar con mutex
  this->unlock(this->fd_ship);
}

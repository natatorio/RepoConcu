#include "Dock.h"
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

Dock::Dock(int id) {
  key_t key = ftok("/bin/bash", id);
  this->memid = shmget(key, 1000, IPC_CREAT|0777);
  this->shmem = shmat(this->memid, NULL, 0);
}

Dock::~Dock() {
  shmdt(this->shmem);
  shmctl(this->memid, IPC_RMID, NULL);
}

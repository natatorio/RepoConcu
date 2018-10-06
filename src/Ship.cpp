#include "Ship.h"

Ship::Ship(int shipCapacity){
  blockSignals();
  capacity = shipCapacity;
}

void Ship::inspectShip(){
  blockSignals();
  cout << CONFISCATED << flush;
  unblockSignals()
}

void Ship::inspectTickets(){
  blockSignals();
  cout << FINED << flush;
  unblockSignals()
}

void Ship::downloadTourist(){
  blockSignals();
  unblockSignals()
}

void Ship::visitCity(int city, int direction){
  Queue* queue;
  if(direction == TRAVELING_FOWARD) queue = new Queue(Queue::goQueueFilename, i);
  else  queue = new Queue(Queue::backQueueFilename, i);
  
  unblockSignals();

  blockSignals();
}

void Ship::blockSignals(){
  sigset_t sa;
  sigemptyset ( &sa );
  sigaddset ( &sa, SIGRTMIN + CUSTOM_SIG );
  sigaddset ( &sa, SIGRTMIN + INSPECTION_SIG );
  sigaddset ( &sa, SIGRTMIN + TOURIST_SIG );
  sigprocmask ( SIG_BLOCK,&sa,NULL );
}

void Ship::unblockSignals(){
  sigset_t sa;
  sigemptyset ( &sa );
  sigaddset ( &sa, SIGRTMIN + CUSTOM_SIG );
  sigaddset ( &sa, SIGRTMIN + INSPECTION_SIG );
  sigaddset ( &sa, SIGRTMIN + TOURIST_SIG );
  sigprocmask ( SIG_UNBLOCK,&sa,NULL );
}

Ship::~Ship(){
    close(1);
}

#include "Ship.h"

int main(){
  Ship* ship = new Ship();
  cout << ship->FINED << flush;
  delete ship;
  exit(0);
  return 0;
}

Ship::Ship(){

}

void Ship::blockSignals(){
  sigset_t sa;
  sigemptyset ( &sa );
  sigaddset ( &sa,SIGRTMIN+13 );
  sigaddset ( &sa,SIGRTMIN+14 );
  sigaddset ( &sa,SIGRTMIN+15 );
  sigprocmask ( SIG_BLOCK,&sa,NULL );
}

void Ship::unblockSignals(){
  sigset_t sa;
  sigemptyset ( &sa );
  sigaddset ( &sa,SIGRTMIN+13 );
  sigaddset ( &sa,SIGRTMIN+14 );
  sigaddset ( &sa,SIGRTMIN+15 );
  sigprocmask ( SIG_UNBLOCK,&sa,NULL );
}

Ship::~Ship(){
  close(1);
}

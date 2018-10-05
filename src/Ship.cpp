#include "Ship.h"

int main(){
  Ship* ship = new Ship();
  for(int i=0;i!=3;i++){
    sleep(1);
    ship->inspectTickets();
    ship->inspectShip();
  }
  delete ship;
  exit(0);
  return 0;
}

Ship::Ship(){

}

void Ship::inspectShip(){
  cout << CONFISCATED << flush;
}

void Ship::inspectTickets(){
  cout << FINED << flush;
}

void Ship::downloadTourist(){

}

Ship::~Ship(){
    close(1);
}

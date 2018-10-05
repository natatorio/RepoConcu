#include "Ship.h"
#include "SignalHandler.h"


int main(int argc, char* argv[]){
  Ship* ship = new Ship(atoi(argv[0]));
  for(int i=0;i!=3;i++){
    sleep(3);
    ship->inspectTickets();
    ship->inspectShip();
  }
  delete ship;
  exit(0);
  return 0;
}

Ship::Ship(int shipCapacity){
  capacity = shipCapacity;
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

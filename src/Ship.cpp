#include "Ship.h"

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

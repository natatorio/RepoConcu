#include "Ship.h"
#include "SignalHandler.h"


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

void Ship::visitCity(){

}

void Ship::setActualCity(int city){
  actualCity = city;
}

Ship::~Ship(){
    close(1);
}

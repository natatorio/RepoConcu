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

Ship::~Ship(){
  close(1);
}

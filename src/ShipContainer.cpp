#include "ShipContainer.h"

int main(int argc, char* argv[]){
  ShipContainer* shipContainer = new ShipContainer(atoi(argv[0]), atoi(argv[1]));
  shipContainer->startJourney();
  delete shipContainer;
  exit(0);
}

ShipContainer::ShipContainer(int capacity, int nCities){
  this->nCities = nCities;
  ship = new Ship(capacity);
  customHandler.addShip(ship);
  inspectionHandler.addShip(ship);
  touristHandler.addShip(ship);
}

void ShipContainer::startJourney(){
  for(int i = 0; i > -1; i += direction){
    //TODO lock dock i
    ignorePendingSignals();
    char shipState = ship->visitCity(i, direction);
    //TODO unlock dock i
    if(shipState == Ship::CONFISCATED)  break;
    if(i == nCities - 1)  direction = TRAVELING_BACKWARD;
  }
}

void ShipContainer::ignorePendingSignals(){
  SignalHandler :: getInstance()->ignorePending (SIGRTMIN + CUSTOM_SIG);
  SignalHandler :: getInstance()->ignorePending (SIGRTMIN + INSPECTION_SIG);
  SignalHandler :: getInstance()->ignorePending (SIGRTMIN + TOURIST_SIG);
  SignalHandler :: getInstance()->registrarHandler (SIGRTMIN + CUSTOM_SIG, &customHandler, SA_RESTART);
  SignalHandler :: getInstance()->registrarHandler (SIGRTMIN + INSPECTION_SIG, &inspectionHandler, SA_RESTART);
  SignalHandler :: getInstance()->registrarHandler (SIGRTMIN + TOURIST_SIG, &touristHandler, SA_RESTART);
}

ShipContainer::~ShipContainer(){
  SignalHandler :: destruir();
  delete ship;
}

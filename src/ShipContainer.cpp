#include "ShipContainer.h"

int main(int argc, char* argv[]){
  ShipContainer* shipContainer = new ShipContainer(atoi(argv[0]), atoi(argv[1]));
  shipContainer->startJourney();
  delete shipContainer;
  exit(0);
}

ShipContainer::ShipContainer(int capacity, int nCities){
  blockSignals();
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
    ship->setActualCity(i);
    unblockSignals();
    ship->visitCity();
    blockSignals();
    //TODO unlock dock i
    if(i == nCities - 1)  direction = -1;
  }
}

void ShipContainer::blockSignals(){
  sigset_t sa;
  sigemptyset ( &sa );
  sigaddset ( &sa, SIGRTMIN + ship->CUSTOM_SIG );
  sigaddset ( &sa, SIGRTMIN + ship->INSPECTION_SIG );
  sigaddset ( &sa, SIGRTMIN + ship->TOURIST_SIG );
  sigprocmask ( SIG_BLOCK,&sa,NULL );
}

void ShipContainer::ignorePendingSignals(){
  SignalHandler :: getInstance()->ignorePending (SIGRTMIN + ship->CUSTOM_SIG);
  SignalHandler :: getInstance()->ignorePending (SIGRTMIN + ship->INSPECTION_SIG);
  SignalHandler :: getInstance()->ignorePending (SIGRTMIN + ship->TOURIST_SIG);
}

void ShipContainer::unblockSignals(){
  SignalHandler :: getInstance()->registrarHandler (SIGRTMIN + ship->CUSTOM_SIG, &customHandler, SA_RESTART);
  SignalHandler :: getInstance()->registrarHandler (SIGRTMIN + ship->INSPECTION_SIG, &inspectionHandler, SA_RESTART);
  SignalHandler :: getInstance()->registrarHandler (SIGRTMIN + ship->TOURIST_SIG, &touristHandler, SA_RESTART);
  sigset_t sa;
  sigemptyset ( &sa );
  sigaddset ( &sa, SIGRTMIN + ship->CUSTOM_SIG );
  sigaddset ( &sa, SIGRTMIN + ship->INSPECTION_SIG );
  sigaddset ( &sa, SIGRTMIN + ship->TOURIST_SIG );
  sigprocmask ( SIG_UNBLOCK,&sa,NULL );
}

ShipContainer::~ShipContainer(){
  SignalHandler :: destruir();
  delete ship;
}

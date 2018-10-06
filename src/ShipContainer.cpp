#include "ShipContainer.h"

int main(int argc, char* argv[]){
  ShipContainer* shipContainer = new ShipContainer(atoi(argv[0]));
  delete shipContainer;
  exit(0);
}

ShipContainer::ShipContainer(int capacity){
  ship = new Ship(capacity);
  customHandler.addShip(ship);
  SignalHandler :: getInstance()->registrarHandler (SIGRTMIN + ship->CUSTOM_SIG, &customHandler, SA_RESTART);
  inspectionHandler.addShip(ship);
  SignalHandler :: getInstance()->registrarHandler (SIGRTMIN + ship->INSPECTION_SIG, &inspectionHandler, SA_RESTART);
  touristHandler.addShip(ship);
  SignalHandler :: getInstance()->registrarHandler (SIGRTMIN + ship->TOURIST_SIG, &touristHandler, SA_RESTART);
}

void ShipContainer::blockSignals(){
  sigset_t sa;
  sigemptyset ( &sa );
  sigaddset ( &sa, SIGRTMIN + ship->CUSTOM_SIG );
  sigaddset ( &sa, SIGRTMIN + ship->INSPECTION_SIG );
  sigaddset ( &sa, SIGRTMIN + ship->TOURIST_SIG );
  sigprocmask ( SIG_BLOCK,&sa,NULL );
}

void ShipContainer::ignoreAndUnblockSignals(){

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

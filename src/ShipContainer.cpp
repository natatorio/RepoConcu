#include "ShipContainer.h"


int main(){
  ShipContainer* shipContainer = new ShipContainer();
  sleep(10);
  delete shipContainer;
  exit(0);
  return 0;
}
ShipContainer::ShipContainer(){
  ship = new Ship();
  blockSignals();
  customHandler.addShip(ship);
  SignalHandler :: getInstance()->registrarHandler (customHandler.CUSTOM_SIG, &customHandler);
  inspectionHandler.addShip(ship);
  SignalHandler :: getInstance()->registrarHandler (inspectionHandler.INSPECTION_SIG, &inspectionHandler);
  touristHandler.addShip(ship);
  SignalHandler :: getInstance()->registrarHandler (touristHandler.TOURIST_SIG, &touristHandler);
  unblockSignals();
}

void ShipContainer::blockSignals(){
  sigset_t sa;
  sigemptyset ( &sa );
  sigaddset ( &sa,customHandler.CUSTOM_SIG );
  sigaddset ( &sa,inspectionHandler.INSPECTION_SIG );
  sigaddset ( &sa,touristHandler.TOURIST_SIG );
  sigprocmask ( SIG_BLOCK,&sa,NULL );
}

void ShipContainer::unblockSignals(){
  sigset_t sa;
  sigemptyset ( &sa );
  sigaddset ( &sa,customHandler.CUSTOM_SIG );
  sigaddset ( &sa,inspectionHandler.INSPECTION_SIG );
  sigaddset ( &sa,touristHandler.TOURIST_SIG );
  sigprocmask ( SIG_UNBLOCK,&sa,NULL );
}

ShipContainer::~ShipContainer(){
  SignalHandler :: destruir();
}

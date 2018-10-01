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
  CustomHandler customHandler;
  customHandler.addShip(ship);
  SignalHandler :: getInstance()->registrarHandler ( SIGRTMIN+13,&customHandler );
  InspectionHandler inspectionHandler;
  inspectionHandler.addShip(ship);
  SignalHandler :: getInstance()->registrarHandler ( SIGRTMIN+14,&inspectionHandler );
  TouristHandler touristHandler;
  touristHandler.addShip(ship);
  SignalHandler :: getInstance()->registrarHandler ( SIGRTMIN+15,&touristHandler );
  unblockSignals();

}

void ShipContainer::blockSignals(){
  sigset_t sa;
  sigemptyset ( &sa );
  sigaddset ( &sa,SIGRTMIN+13 );
  sigaddset ( &sa,SIGRTMIN+14 );
  sigaddset ( &sa,SIGRTMIN+15 );
  sigprocmask ( SIG_BLOCK,&sa,NULL );
}

void ShipContainer::unblockSignals(){
  sigset_t sa;
  sigemptyset ( &sa );
  sigaddset ( &sa,SIGRTMIN+13 );
  sigaddset ( &sa,SIGRTMIN+14 );
  sigaddset ( &sa,SIGRTMIN+15 );
  sigprocmask ( SIG_UNBLOCK,&sa,NULL );
}

ShipContainer::~ShipContainer(){
  SignalHandler :: destruir();
}

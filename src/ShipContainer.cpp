#include "ShipContainer.h"

int main(int argc, char* argv[]){
  ShipContainer* shipContainer = new ShipContainer(atoi(argv[0]), atoi(argv[1]));
  shipContainer->startJourney();
  delete shipContainer;
  exit(0);
}

ShipContainer::ShipContainer(int capacity, int nCities){
  this->nCities = nCities;
  logger = new Logger("test");
  ship = new Ship(capacity);
  customHandler.addShip(ship);
  inspectionHandler.addShip(ship);
  touristHandler.addShip(ship);
  for(int i = 0; i != nCities; i++) docks.push_back(new Dock(i, NOT_INITIALIZE));
}

void ShipContainer::startJourney(){
  for(int i = 0; i > -1; i += direction){
    docks[i]->lock();
    ostringstream msg;
    msg << "A ship arrived to dock " << i << endl;
    logger->write(msg);
    ignorePendingSignals();
    if(i == nCities - 1)  changeDirection();
    char shipState = ship->visitCity(i);
    docks[i]->unlock();
    msg.str("");
    msg << "A ship left dock " << i << endl;
    logger->write(msg);
    if(shipState == Ship::CONFISCATED)  break;
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

void ShipContainer::changeDirection(){
  ship->changeDirection();
  direction = TRAVELING_BACKWARD;
}

ShipContainer::~ShipContainer(){
  SignalHandler :: destruir();
  for(int i = 0; i != nCities; i++) delete docks[i];
  delete logger;
  delete ship;
}

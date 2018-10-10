#include "LakeConcuContainer.h"

int main (int argc, char* argv[]){
  if(argc != 3){
    cout << "Usage: ./lakeConcu {N Ships} {Capacity of ships}" << endl;
    return 0;
  }
  cout << ". Para consultar la cantidad de pasajeros multados ejecute: kill -";
  cout << SIGRTMIN + InfoHandler::INFO_SIG << " " << getpid() << endl;
  LakeConcuContainer* lakeConcuContainer = new LakeConcuContainer(atoi(argv[1]), atoi(argv[2]));
  lakeConcuContainer->listenShips();
  delete lakeConcuContainer;
  return 0;
}

LakeConcuContainer::LakeConcuContainer(int nShips, int shipCapacity){
  lakeConcu = new LakeConcu(nShips, shipCapacity);
  infoHandler.addLakeConcu(lakeConcu);
  SignalHandler :: getInstance()->registrarHandler (SIGRTMIN + infoHandler.INFO_SIG, &infoHandler, 0);
}

void LakeConcuContainer::listenShips(){
  lakeConcu->listenShips();
}

LakeConcuContainer::~LakeConcuContainer(){
	SignalHandler :: destruir ();
  delete lakeConcu;
}

#include "LakeConcuContainer.h"

int main (int argc, char* argv[]){
  if(argc != 3){
    cout << "Usage: ./lakeConcu {N Ships} {Capacity of ships}" << endl;
    return 0;
  }
  cout << "Mi pid es: " << getpid();
  cout << ". Para consultar la cantidad de pasajeros multados ejecute: kill -47 " << getpid() << endl;
  LakeConcuContainer* lakeConcuContainer = new LakeConcuContainer(atoi(argv[1]), atoi(argv[2]));
  delete lakeConcuContainer;
  return 0;
}

LakeConcuContainer::LakeConcuContainer(int nShips, int shipCapacity){
  lakeConcu = new LakeConcu(nShips, shipCapacity);
  infoHandler.addLakeConcu(lakeConcu);
  SignalHandler :: getInstance()->registrarHandler (SIGRTMIN + infoHandler.INFO_SIG, &infoHandler, 0);
  lakeConcu->listenShips();
  kill(lakeConcu->getGeneratorPid(), SIGINT);
}

LakeConcuContainer::~LakeConcuContainer(){
  int status = 0;
  waitpid(lakeConcu->getGeneratorPid(), &status, 0);
  if(!WEXITSTATUS(status)) cout << "Finalizado correctamente ;)" << endl;
	SignalHandler :: destruir ();
  delete lakeConcu;
}

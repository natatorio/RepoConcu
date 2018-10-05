#include "LakeConcuContainer.h"

int main (int argc, char* argv[]){
  if(argc != 3){
    cout << "Usage: ./lakeConcu {N Ships} {M Cities}" << endl;
    return 0;
  }
  cout << "Mi pid es: " << getpid();
  cout << ". Para consultar la cantidad de pasajeros multados ejecute: kill -47 " << getpid() << endl;
  LakeConcuContainer* lakeConcuContainer = new LakeConcuContainer(atoi(argv[1]), atoi(argv[2]));
  delete lakeConcuContainer;
  int status = 0;
  wait(&status);
  if(!WEXITSTATUS(status)) cout << "Finalizado correctamente ;)" << endl;
  return 0;
}

LakeConcuContainer::LakeConcuContainer(int nShips, int nCities){
  lakeConcu = new LakeConcu(nShips, nCities);
  infoHandler.addLakeConcu(lakeConcu);
  SignalHandler :: getInstance()->registrarHandler (infoHandler.INFO_SIG, &infoHandler);
  lakeConcu->listenShips();
  kill(lakeConcu->getGeneratorPid(), SIGINT);
}

LakeConcuContainer::~LakeConcuContainer(){
	SignalHandler :: destruir ();
  delete lakeConcu;
}

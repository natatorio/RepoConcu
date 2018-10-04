#include "LakeConcuContainer.h"

int main (int argc, char* argv[]){
  if(argc != 3){
    cout << "Usage: ./lakeConcu {N Ships} {M Cities}" << endl;
    return 0;
  }
  LakeConcuContainer* lakeConcuContainer = new LakeConcuContainer(atoi(argv[1]), atoi(argv[2]));
  delete lakeConcuContainer;
  return 0;
}

LakeConcuContainer::LakeConcuContainer(int nShips, int nCities){
  lakeConcu = new LakeConcu(nShips, nCities);
  infoHandler.addLakeConcu(lakeConcu);
  SignalHandler :: getInstance()->registrarHandler (infoHandler.INFO_SIG, &infoHandler);
  lakeConcu->listenShips();
  for(int i=0; i!=nShips+2;i++) wait(NULL);
}

LakeConcuContainer::~LakeConcuContainer(){

}

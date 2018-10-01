#include "LakeConcu.h"

int main (int argc, char* argv[]){
  if(argc != 3){
    cout << "Usage: ./lakeConcu {N Ships} {M Cities}" << endl;
    return 0;
  }
  LakeConcu* lakeConcu = new LakeConcu(atoi(argv[1]), atoi(argv[2]));
  lakeConcu->listenShips();
  for(int i=0; i!=atoi(argv[1])+2;i++) wait(NULL);
  delete lakeConcu;
  return 0;
}

LakeConcu::LakeConcu(int nShips, int nCities){
  confiscatedShips = 0;
  finedPassengers = 0;
  runShips(nShips, nCities);
  runCustom();
  runInspector();
}

void LakeConcu::runShips(int nShips, int nCities){
  pidShips = new char*[nShips+1];
  pid_t pid;
  pipe = new Pipe();
  for(int i=0; i!=nShips; i++){
    pid = fork();
    if(!pid){
      pipe->setearModo(pipe->ESCRITURA);
      dup2(pipe->getFdEscritura(), 1);
      char *argv[] = {NULL};
      execv("ship", argv);
    }
    string s = to_string(pid);
    pidShips[i] =new char[s.length()+1];
    strcpy(pidShips[i], s.c_str());
  }
  pidShips[nShips] = NULL;
  pipe->setearModo(pipe->LECTURA);
}

void LakeConcu::runCustom(){
  if(!fork()){
    execv("custom", pidShips);
  }
}

void LakeConcu::runInspector(){
  if(!fork()){
    execv("inspector", pidShips);
  }
}

void LakeConcu::listenShips(){
  char msg;
  while(pipe->leer(&msg, sizeof(char))){
    if(msg == FINED) finedPassengers++;
    if(msg == CONFISCATED) confiscatedShips++;
  }
  cout << getFinedPassengers() << endl;
  cout << getConfiscatedShips() << endl;
}

int LakeConcu::getConfiscatedShips(){
  return confiscatedShips;
}

int LakeConcu::getFinedPassengers(){
  return finedPassengers;
}

LakeConcu::~LakeConcu(){
  delete[] pidShips;
  pipe->cerrar();
}

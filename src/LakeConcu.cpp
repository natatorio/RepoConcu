#include "LakeConcu.h"

LakeConcu::LakeConcu(int nShips, int nCities){
  confiscatedShips = 0;
  finedPassengers = 0;
  runShips(nShips, nCities);
  runGenerator(nCities);
}

void LakeConcu::runShips(int nShips, int nCities){
//  pidShips = new char*[nShips+1];
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
//    string s = to_string(pid);
//    pidShips[i] =new char[s.length()+1];
//    strcpy(pidShips[i], s.c_str());
  }
//  pidShips[nShips] = NULL;
  pipe->setearModo(pipe->LECTURA);
}

void LakeConcu::runGenerator(int nCities){
  string str = to_string(nCities);
  char arg[str.length()+1];
  strcpy(arg, str.c_str());
  char* argv[] = {arg, NULL};
  generatorPid = fork();
  if(!generatorPid){
    execv("generator", argv);
  }
}

void LakeConcu::listenShips(){
  char msg;
  while(pipe->leer(&msg, sizeof(char))){
    if(msg == FINED) finedPassengers++;
    if(msg == CONFISCATED) confiscatedShips++;
    msg = 0;
  }
}

int LakeConcu::getConfiscatedShips(){
  return confiscatedShips;
}

int LakeConcu::getFinedPassengers(){
  return finedPassengers;
}

pid_t LakeConcu::getGeneratorPid(){
  return generatorPid;
}

void LakeConcu::printFinedAndConfiscated(){
  cout << "La cantidad de pasajeros multados es: " << getFinedPassengers() << endl;
  cout << "La cantidad de barcos decomisados es: " << getConfiscatedShips() << endl;
}

LakeConcu::~LakeConcu(){
//  delete[] pidShips;
  pipe->cerrar();
  delete pipe;
}

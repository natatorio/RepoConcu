#include "LakeConcu.h"
#include "Logger.h"

//Logger logger("test");

LakeConcu::LakeConcu(int nShips, int shipCapacity){
  confiscatedShips = 0;
  finedPassengers = 0;
  runShips(nShips, shipCapacity);
  runGenerator();
  runCustom();
  runInspector();
  runTouristDownloader();
}

void LakeConcu::runShips(int nShips, int shipCapacity){
  pidShips = new char*[nShips+3];
  pid_t pid;
  pipe = new Pipe();
  for(int i=0; i!=nShips; i++){
    pid = fork();
    if(!pid){
      pipe->setearModo(pipe->ESCRITURA);
      dup2(pipe->getFdEscritura(), 1);
      char* argv[SHIP_ARGS + 1];
      strcpy(argv[0], to_string(shipCapacity).c_str());
      strcpy(argv[1], to_string(N_CITIES).c_str());
      argv[2] = NULL;
      execv("ship", argv);
    }
    strcpy(pidShips[i+2], to_string(pid).c_str());
  }
  pidShips[nShips+2] = NULL;
  pipe->setearModo(pipe->LECTURA);
}

void LakeConcu::runGenerator(){
  string str = to_string(N_CITIES);
  char arg[str.length()+1];
  strcpy(arg, str.c_str());
  char* argv[] = {arg, NULL};
  generatorPid = fork();
  if(!generatorPid){
    execv("generator", argv);
  }
}

void LakeConcu::runCustom(){
  string str = to_string(SIGRTMIN + CUSTOM_SIG);
  strcpy(pidShips[0], str.c_str());
  strcpy(pidShips[1], "3");
  if(!fork()){
    execv("signalSender", pidShips);
  }
}

void LakeConcu::runInspector(){
  string str = to_string(SIGRTMIN + INSPECTION_SIG);
  strcpy(pidShips[0], str.c_str());
  strcpy(pidShips[1], "2");
  if(!fork()){
    execv("signalSender", pidShips);
  }
}

void LakeConcu::runTouristDownloader(){
  string str = to_string(SIGRTMIN + TOURIST_SIG);
  strcpy(pidShips[0], str.c_str());
  strcpy(pidShips[1], "1");
  if(!fork()){
    execv("signalSender", pidShips);
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
  delete[] pidShips;
  pipe->cerrar();
  delete pipe;
}

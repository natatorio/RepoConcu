#include "LakeConcu.h"

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
  pidShips = new char[nShips + SIGNALSENDER_ARGS + 1][MAX_ARG_SIZE];
  pid_t pid;
  pipe = new Pipe();
  for(int i=0; i!=nShips; i++){
    pid = fork();
    if(!pid){
      pipe->setearModo(pipe->ESCRITURA);
      dup2(pipe->getFdEscritura(), 1);
      char argv[SHIP_ARGS][MAX_ARG_SIZE];
      strcpy(argv[0], to_string(shipCapacity).c_str());
      strcpy(argv[1], to_string(N_CITIES).c_str());
      char* const args[] = {argv[0], argv[1], NULL};
      execv("ship", args);
    }
    strcpy(pidShips[i + SIGNALSENDER_ARGS], to_string(pid).c_str());
  }
  pipe->setearModo(pipe->LECTURA);
}

void LakeConcu::runGenerator(){
  char argv[GENERATOR_ARGS + 1][MAX_ARG_SIZE];
  strcpy(argv[0], to_string(N_CITIES).c_str());
  char* const args[] = {argv[0], NULL};
  generatorPid = fork();
  if(!generatorPid) execv("generator", args);
}

void LakeConcu::runCustom(){
  strcpy(pidShips[0], to_string(SIGRTMIN + CUSTOM_SIG).c_str());
  strcpy(pidShips[1], to_string(CUSTOM_SLEEP_SECS).c_str());
  char* const args[] = {pidShips, NULL};
  if(!fork()) execv("signalSender", args);
}

void LakeConcu::runInspector(){
  strcpy(pidShips[0], to_string(SIGRTMIN + INSPECTION_SIG).c_str());
  strcpy(pidShips[1], to_string(INSPECTOR_SLEEP_SECS).c_str());

  if(!fork()) execv("signalSender", pidShips);
}

void LakeConcu::runTouristDownloader(){
  strcpy(pidShips[0], to_string(SIGRTMIN + TOURIST_SIG).c_str());
  strcpy(pidShips[1], to_string(TOURISTDOWLOADER_SLEEP_SECS).c_str());
  if(!fork()) execv("signalSender", pidShips);
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

void LakeConcu::stopGeneratorAndSignalSenders(){
  kill(generatorPid, SIGINT);
  kill(customPid, SIGINT);
  kill(inspectorPid, SIGINT);
  kill(touristDownloaderPid, SIGINT);
  for(int i = 0; i != 4; i++) wait(NULL);
}

void LakeConcu::printFinedAndConfiscated(){
  cout << "La cantidad de pasajeros multados es: " << getFinedPassengers() << endl;
  cout << "La cantidad de barcos decomisados es: " << getConfiscatedShips() << endl;
}

LakeConcu::~LakeConcu(){
  delete pidShips;
  pipe->cerrar();
  delete pipe;
}

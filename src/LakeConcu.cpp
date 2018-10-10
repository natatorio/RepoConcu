#include "LakeConcu.h"

Logger logger("test");

LakeConcu::LakeConcu(int nShips, int shipCapacity){
  confiscatedShips = 0;
  finedPassengers = 0;
  runGenerator();
  sleep(3); //TODO: add Sync between generator and ships
  initDocks();
  runShips(nShips, shipCapacity);
  runCustom();
  runInspector();
  runTouristDownloader();
}

void LakeConcu::runShips(int nShips, int shipCapacity){
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
      strcpy(argv[2], to_string(pidShips.size()).c_str());
      char* const args[] = {argv[0], argv[1], argv[2], NULL};
      execv("ship", args);
    }
    pidShips.push_back(pid);
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
  char argv[SIGNALSENDER_ARGS + pidShips.size()][MAX_ARG_SIZE];
  strcpy(argv[0], to_string(SIGRTMIN + CUSTOM_SIG).c_str());
  strcpy(argv[1], to_string(CUSTOM_SLEEP_SECS).c_str());
  for(unsigned int i = 0; i != pidShips.size(); i++) strcpy(argv[i + SIGNALSENDER_ARGS], to_string(pidShips[i]).c_str());
  char* argv2[SIGNALSENDER_ARGS + pidShips.size() + 1];
  for(unsigned int i = 0; i != pidShips.size() + SIGNALSENDER_ARGS; i++)  argv2[i] = argv[i];
  argv2[pidShips.size() + SIGNALSENDER_ARGS] = NULL;
  customPid = fork();
  if(!customPid) execv("signalSender", argv2);
}

void LakeConcu::runInspector(){
  char argv[SIGNALSENDER_ARGS + pidShips.size()][MAX_ARG_SIZE];
  strcpy(argv[0], to_string(SIGRTMIN + INSPECTION_SIG).c_str());
  strcpy(argv[1], to_string(INSPECTOR_SLEEP_SECS).c_str());
  for(unsigned int i = 0; i != pidShips.size(); i++) strcpy(argv[i + SIGNALSENDER_ARGS], to_string(pidShips[i]).c_str());
  char* argv2[SIGNALSENDER_ARGS + pidShips.size() + 1];
  for(unsigned int i = 0; i != pidShips.size() + SIGNALSENDER_ARGS; i++)  argv2[i] = argv[i];
  argv2[pidShips.size() + SIGNALSENDER_ARGS] = NULL;
  inspectorPid = fork();
  if(!inspectorPid) execv("signalSender", argv2);
}

void LakeConcu::runTouristDownloader(){
  char argv[SIGNALSENDER_ARGS + pidShips.size()][MAX_ARG_SIZE];
  strcpy(argv[0], to_string(SIGRTMIN + TOURIST_SIG).c_str());
  strcpy(argv[1], to_string(TOURISTDOWLOADER_SLEEP_SECS).c_str());
  for(unsigned int i = 0; i != pidShips.size(); i++) strcpy(argv[i + SIGNALSENDER_ARGS], to_string(pidShips[i]).c_str());
  char* argv2[SIGNALSENDER_ARGS + pidShips.size() + 1];
  for(unsigned int i = 0; i != pidShips.size() + SIGNALSENDER_ARGS; i++)  argv2[i] = argv[i];
  argv2[pidShips.size() + SIGNALSENDER_ARGS] = NULL;
  touristDownloaderPid = fork();
  if(!touristDownloaderPid) execv("signalSender", argv2);
}

void LakeConcu::listenShips(){
  char msg = 0;
  while(pipe->leer(&msg, sizeof(char))){
    if(msg == FINED) finedPassengers++;
    if(msg == CONFISCATED) confiscatedShips++;
    msg = 0;
  }
}

void LakeConcu::initDocks(){
  for(int i = 0; i != N_CITIES; i++)  docks.push_back(new Dock(i, INITIALIZE));
}

int LakeConcu::getConfiscatedShips(){
  return confiscatedShips;
}

int LakeConcu::getFinedPassengers(){
  return finedPassengers;
}

void LakeConcu::printFinedAndConfiscated(){
  cout << "La cantidad de pasajeros multados es: " << getFinedPassengers() << endl;
  cout << "La cantidad de barcos decomisados es: " << getConfiscatedShips() << endl;
}

LakeConcu::~LakeConcu(){
  printFinedAndConfiscated();
  kill(0, SIGINT);
  while(wait(NULL) > 0);
  pipe->cerrar();
  delete pipe;
  for(int i = 0; i != N_CITIES; i++)  delete docks[i];
}

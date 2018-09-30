#include "LakeConcu.h"

int main (int argc, char* argv[]){
  if(argc != 3){
    cout << "Usage: ./lakeConcu {N Ships} {M Cities}" << endl;
    return 0;
  }
  LakeConcu* lakeConcu = new LakeConcu(atoi(argv[1]), atoi(argv[2]));
  lakeConcu->getFinedPassengers();
  //delete lakeConcu;
  return 0;
}

LakeConcu::LakeConcu(int nShips, int nCities){
  confiscatedShips = 0;
  finedPassengers = 0;
  pidShips = new char*[nShips+1];
  pid_t pid;
  for(int i=0; i!=nShips; i++){
    pid = fork();
    if(!pid){
      char *argv[] = {NULL};
      execv("ship", argv);
    }
    string s = to_string(pid);
    pidShips[i] =new char[s.length()+1];
    strcpy(pidShips[i], s.c_str());
  }
  pidShips[nShips] = NULL;
  pid = fork();
  if(!pid){
    execv("inspector", pidShips);
  }
  pid = fork();
  if(!pid){
    execv("custom", pidShips);
  }
  for(int i=0; i!=nShips+2;i++) wait(NULL);

}
int LakeConcu::getConfiscatedShips(){
  return confiscatedShips;
}
int LakeConcu::getFinedPassengers(){
  return finedPassengers;
}
LakeConcu::~LakeConcu(){
  delete[] pidShips;
}

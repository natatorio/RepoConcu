#include "LakeConcu.h"

int main (int argc, char* argv[]){
  LakeConcu* lakeConcu = new LakeConcu(atoi(argv[1]), atoi(argv[2]));
  delete lakeConcu;
  return 0;
}

LakeConcu::LakeConcu(int nShips, int nCities){
  confiscatedShips = 0;
  finedPassengers = 0;
  pid_t pid;
  for(int i=0; i!=nShips; i++){
    pid = fork();
    if(!pid){
      char *argv[] = {NULL};
      execv("ship", argv);
    }else{
      pidShips.push_back(pid);
    }
  }
  char *argv[nShips+1];
  for(int i=0; i!=nShips; i++){
    std::string s = std::to_string((int)pidShips[i]);
    argv[i] = (char*)s.c_str();
  }
  argv[nShips] = NULL;
  pid = fork();
  if(!pid){
    execv("inspector", argv);
  }
  pid = fork();
  if(!pid){
    execv("custom", argv);
  }


}

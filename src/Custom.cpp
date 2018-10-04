#include "Custom.h"

int main(int argc, char *argv[]){
  Custom* custom = new Custom(argv);
  sleep(1);
  for(int i = 0; i!=10000; i++) kill(custom->getRandomShip(), CustomHandler::CUSTOM_SIG);
  delete custom;
  exit(0);
  return 0;
}

Custom::Custom(char *argv[]){
  for(int i=0; argv[i]; i++)  addShip(argv[i]);
  srand(time(NULL) && (int)getpid());
}
void Custom::addShip(char *ship){
  ships.push_back((pid_t)atoi(ship));
}
pid_t Custom::getRandomShip(){
  return ships[rand()%ships.size()];
}

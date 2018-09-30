#include "Custom.h"

int main(int argc, char *argv[]){
  Custom* custom = new Custom();
  for(int i=0; argv[i]; i++)  custom->addShip(argv[i]);
  delete custom;
  exit(0);
  return 0;
}

Custom::Custom(){
  srand(time(NULL) && (int)getpid());
}
void Custom::addShip(char *ship){
  ships.push_back((pid_t)atoi(ship));
}
pid_t Custom::getRandomShip(){
  return ships[rand()%ships.size()];
}

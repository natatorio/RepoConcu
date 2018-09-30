#include "Inspector.h"

int main(int argc, char *argv[]){
  Inspector* inspector = new Inspector();
  for(int i=0; argv[i]; i++)  inspector->addShip(argv[i]);
  delete inspector;
  exit(0);
  return 0;
}

Inspector::Inspector(){

}
void Inspector::addShip(char *ship){
  ships.push_back((pid_t)atoi(ship));
}
pid_t Inspector::getRandomShip(){
  return ships[rand()%ships.size()];
}

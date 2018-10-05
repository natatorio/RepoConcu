#include "Generator.h"

int main(int argc, char* argv[]){
  Generator* generator = new Generator(atoi(argv[0]));

  while ( generator->sigintHandler.getGracefulQuit() == 0 ) {}
  cout << "Señal de fin. Hay " << generator->nCities << " ciudades" << endl;

  delete generator;
  exit(0);
}

Generator::Generator(int nCities){
  SignalHandler :: getInstance()->registrarHandler(SIGINT,&sigintHandler);
  this->nCities = nCities;
}

Generator::~Generator(){
}

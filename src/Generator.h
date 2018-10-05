#ifndef GENERATOR_H_
#define GENERATOR_H_

#include "Queuer.h"
#include "SignalHandler.h"
#include "SIGINT_Handler.h"

#include <stdlib.h>
#include <iostream>

using namespace std;

class Generator{
  public:

    Generator(int);
    ~Generator();
    int nCities;
    SIGINT_Handler sigintHandler;

  private:

};


#endif /* GENERATORCONTAINER_H_ */

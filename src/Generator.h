#ifndef GENERATOR_H_
#define GENERATOR_H_

#include "Queuer.h"
#include "SignalHandler.h"
#include "SIGINT_Handler.h"

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>
#include <iostream>

using namespace std;

class Generator{
  public:

    Generator(int);
    ~Generator();
    void runEnqueueingProcedure();

    int nCities;
    SIGINT_Handler sigintHandler;

  private:
    void createQueues();
    void runQueuer(unsigned int);
    void deleteQueues();

    vector <Queue*> goQueues;
    vector <Queue*> backQueues;

};


#endif /* GENERATORCONTAINER_H_ */

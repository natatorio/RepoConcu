#ifndef GENERATOR_H_
#define GENERATOR_H_

#include "Queue.h"
#include "SignalHandler.h"
#include "SIGINT_Handler.h"

#include <sys/wait.h>
#include <vector>

class Generator{
  public:
    Generator(int nCities);
    ~Generator();
    void runEnqueueingProcedure();

    int nCities;
    SIGINT_Handler sigintHandler;

  private:
    void runQueuer(const char* queueType, int dock);
    void createQueues();
    void deleteQueues();
    int isGoingQueue(int enqueuedInfo);
    int getDockId(int enqueuedInfo);

    vector <Queue*> goQueues;
    vector <Queue*> backQueues;
    int actualId = 0;
};

#endif /* GENERATORCONTAINER_H_ */

#include "Generator.h"

int main(int argc, char* argv[]){
  Generator* generator = new Generator(atoi(argv[0]));
  generator->runEnqueueingProcedure();
  delete generator;
  exit(0);
}

Generator::Generator(int nCities){
  SignalHandler :: getInstance()->registrarHandler(SIGINT,&sigintHandler);
  this->nCities = nCities;
  createQueues();
}

void Generator::createQueues(){
  //TODO: in dock0, shipSem.p() => wait for first ship

  for(int i=0; i != nCities; i++){
    goQueues.push_back(new Queue(Queue::goQueueFilename, i));
    backQueues.push_back(new Queue(Queue::backQueueFilename, i));
    for(int j = 0; j != Queue::size; j++){
      runQueuer(0); //new passenger in goQueue of dock i TODO define orders
      runQueuer(0); //new passenger in backQueue of dock i TODO define orders
      wait(NULL);
      wait(NULL);
    }
    //run one of each in both queues of dock i
    runQueuer(0);
    runQueuer(0);
    runQueuer(0);
    runQueuer(0);
    runQueuer(0);
    runQueuer(0);
  }
  //TODO: in dock0, generatorSem.v() => let ships start
}

void Generator::runQueuer(unsigned int order){
  if(!fork()){
    char* argv[MAX_ARGS + 1];
    if(isGoingQueue(order)) strcpy(argv[0], Queue::goQueueFilename);
    else strcpy(argv[0], Queue::backQueueFilename);
    string str = to_string(getDockId(order));
    char city[str.length()+1];
    strcpy(city, str.c_str());
    argv[1] = city;
    if(isNewPassengerOrder(order))      strcpy(argv[2], Queue::newPassengerOrder);
    if(isTicketInspectionOrder(order))  strcpy(argv[2], Queue::ticketInspectionOrder);
    if(isCustomInspectionOrder(order))  strcpy(argv[2], Queue::customInspectionOrder);
    argv[3] = NULL;
    //TODO check if priority is simulated with nice or enqueueing diferently (inc/dec value of cont when executing semaphore ops v() and p())
    execv("queuer", argv);
  }
}

void Generator::runEnqueueingProcedure(){
  while ( sigintHandler.getGracefulQuit() == 0 ) {
    int endedOrder = 0;
    wait(&endedOrder);
    unsigned int nextOrder = (unsigned int)WEXITSTATUS(endedOrder);
    runQueuer(nextOrder);
  }
}

void Generator::deleteQueues(){
  for(int i=0; i != nCities; i++){
    goQueues[i]->flush();
    delete goQueues[i];
    backQueues[i]->flush();
    delete backQueues[i];
  }
}

Generator::~Generator(){
  deleteQueues();
}

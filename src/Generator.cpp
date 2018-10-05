#include "Generator.h"

int main(int argc, char* argv[]){
  Generator* generator = new Generator(atoi(argv[0]));
  generator.runEnqueueingProcess();
  delete generator;
  exit(0);
}

Generator::Generator(int nCities){
  SignalHandler :: getInstance()->registrarHandler(SIGINT,&sigintHandler);
  this->nCities = nCities;
  createQueues();
}

Generator::createQueues(){
  //TODO: in dock0, shipSem.p() => wait for first ship

  for(int i=0; i!=nCities; i++){
    goQueues.push_back(new Queue(Queue::goQueueFilename, i));
    backQueues.push_back(new Queue(Queue::backQueueFilename, i));
    for(int j = 0; j!=Queue::size; j++){
      goQueues[i]->enqueueNewPassenger();
      backQueues[i]->enqueueNewPassenger();
    }
  }
  //TODO: in dock0, generatorSem.v() => let ships start
}

Generator::runEnqueueingProcess(){
  int endedOrder = 0;
  wait(&endedOrder);
  while ( sigintHandler.getGracefulQuit() == 0 ) {
    if(!fork()){
      unsigned int nextOrder = (unsigned int)WEXITSTATUS(endedOrder);
      if(isGoingQueue(nextOrder)) char* queueType = Queue::goQueueFilename;
      else char* queueType = Queue::backQueueFilename;
      string str = to_string(getDockId(nextOrder));
      char city[str.length()+1];
      strcpy(city, str.c_str());
      if(isNewPassengerOrder(nextOrder))      char* argv[] = {queueType, city, Queue::newPassengerOrder, NULL};
      if(isTicketInspectionOrder(nextOrder))  char* argv[] = {queueType, city, Queue::ticketInspectionOrder, NULL};
      if(isCustomInspectionOrder(nextOrder))  char* argv[] = {queueType, city, Queue::customInspectionOrder, NULL};
      execv("queuer", argv);
    }
    endedOrder = 0;
    wait(&endedOrder);
  }
}

Generator::deleteQueues(){
  for(int i=0; i!=nCities; i++){
    goQueues[i].flush();
    delete goQueues[i];
    backQueues[i].flush();
    delete backQueues[i];
  }
}

Generator::~Generator(){
  deleteQueues();
}

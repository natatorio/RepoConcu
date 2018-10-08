#include "Generator.h"

int main(int argc, char* argv[]){
  Generator* generator = new Generator(atoi(argv[0]));
  generator->runEnqueueingProcedure();
  delete generator;
  exit(0);
}

Generator::Generator(int nCities){
  SignalHandler :: getInstance()->registrarHandler(SIGINT,&sigintHandler, 0);
  this->nCities = nCities;
  createQueues();
}

void Generator::createQueues(){
  for(int i=0; i != nCities; i++){
    goQueues.push_back(new Queue(Queue::goQueueFilename, i));
    backQueues.push_back(new Queue(Queue::backQueueFilename, i));
    runQueuer(Queue::goQueueFilename, i);
    runQueuer(Queue::backQueueFilename, i);
  }
}

void Generator::runQueuer(const char* queueType, int dock){
  if(!fork()){
    char* argv[QUEUER_ARGS + 1];
    strcpy(argv[0], queueType);
    strcpy(argv[1], to_string(dock).c_str());
    strcpy(argv[2], Queue::newPassengerOrder);
    strcpy(argv[3], to_string(actualId++).c_str());
    argv[4] = NULL;
    execv("queuer", argv);
  }
}

void Generator::runEnqueueingProcedure(){
  while ( sigintHandler.getGracefulQuit() == 0 ) {
    int lastEnqueued = 0;
    if(wait(&lastEnqueued) > 0){
      lastEnqueued = WEXITSTATUS(lastEnqueued);
      if(isGoingQueue(lastEnqueued))  runQueuer(Queue::goQueueFilename, getDockId(lastEnqueued));
      else  runQueuer(Queue::backQueueFilename, getDockId(lastEnqueued));
    }
  }
}

int Generator::getDockId(int enqueuedInfo){
  unsigned int dockId = ((unsigned int)enqueuedInfo & 0xFFFFFFFE) >> 1;
  return (int)dockId;
}

int Generator::isGoingQueue(int enqueuedInfo){
  unsigned int answer = enqueuedInfo & 1;
  return (int)answer;
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
  while(wait(NULL) > 0){}
}

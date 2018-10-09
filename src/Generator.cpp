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
  goQueues.push_back(new Queue(Queue::goQueueFilename, 0, INITIALIZE));
  runQueuer(Queue::goQueueFilename, 0);
  for(int i = 1; i != nCities - 1; i++){
    goQueues.push_back(new Queue(Queue::goQueueFilename, i, INITIALIZE));
    backQueues.push_back(new Queue(Queue::backQueueFilename, i, INITIALIZE));
    runQueuer(Queue::goQueueFilename, i);
    runQueuer(Queue::backQueueFilename, i);
  }
  backQueues.push_back(new Queue(Queue::backQueueFilename, nCities - 1, INITIALIZE));
  runQueuer(Queue::backQueueFilename, nCities - 1);
}

void Generator::runQueuer(const char* queueType, int dock){
  if(!fork()){
    char argv[QUEUER_ARGS + 1][MAX_ARG_SIZE];
    strcpy(argv[0], queueType);
    strcpy(argv[1], to_string(dock).c_str());
    strcpy(argv[2], Queue::newPassengerOrder);
    strcpy(argv[3], to_string(actualId).c_str());
    char* const args[] = {argv[0], argv[1], argv[2], argv[3], NULL};
    execv("queuer", args);
  }
  actualId++;
}

void Generator::runEnqueueingProcedure(){
  while ( sigintHandler.getGracefulQuit() == 0 ) {
    int lastEnqueued = 0;
    if(wait(&lastEnqueued) > 0){
      lastEnqueued = WEXITSTATUS(lastEnqueued);
      if(isGoingQueue(lastEnqueued))  runQueuer(Queue::goQueueFilename, getDockId(lastEnqueued));
      else runQueuer(Queue::backQueueFilename, getDockId(lastEnqueued));
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
  for(int i=0; i != nCities - 1; i++){
    goQueues[i]->flush();
    delete goQueues[i];
    backQueues[i]->flush();
    delete backQueues[i];
  }
}

Generator::~Generator(){
  deleteQueues();
  while(wait(NULL) > 0){}
  cout << "Termina generador" << endl;
}

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
  for(int i=0; i != nCities; i++){
    goQueues.push_back(new Queue(Queue::goQueueFilename, i));
    backQueues.push_back(new Queue(Queue::backQueueFilename, i));
    runQueuer(Queue::goQueueFilename, i);
    runQueuer(Queue::backQueueFilename, i);
  }
}

void Generator::runQueuer(const char* queueType, int dock){
  if(!fork()){
    char* argv[MAX_ARGS + 1];
    strcpy(argv[0], queueType);
    string str = to_string(dock);
    char city[str.length()+1];
    strcpy(city, str.c_str());
    argv[1] = city;
    strcpy(argv[2], "0");
    argv[3] = NULL;
    execv("queuer", argv);
  }
}

void Generator::runEnqueueingProcedure(){
  while ( sigintHandler.getGracefulQuit() == 0 ) {
    int lastEnqueued = 0;
    wait(&lastEnqueued);
    lastEnqueued = WEXITSTATUS(lastEnqueued);
    if(isGoingQueue(lastEnqueued))  runQueuer(Queue::goQueueFilename, getDockId(lastEnqueued));
    else  runQueuer(Queue::backQueueFilename, getDockId(lastEnqueued));
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

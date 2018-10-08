#include "Queuer.h"


//argv[0] => filename to create Queue ("goQueue.cc"/"backQueue.cc")
//argv[1] => dock id to create Queue
/*argv[2] => establishes "what" needs to be enqueued:
                - a random passenger
                - a walking tourist
*/
//argv[3] => id
//argv[4] => walking tourist destiny dock id (only if argv[2] == 2)
//argv[5] => 1 if walking tourist has ticket (only if argv[2] == 2)

int main(int argc, char* argv[]){
  Queue* queue = new Queue((const char*)argv[0],atoi(argv[1]));
  if(!strcmp(argv[2], Queue::newPassengerOrder)) queue->enqueueNewPassenger(atoi(argv[3]));
  else if(!strcmp(argv[2], Queue::walkingTouristOrder)){
    srand(getpid());
    sleep(1 + rand() % MAX_WALKING_SECS);
    queue->enqueueWalkingTourist(atoi(argv[3]),atoi(argv[4]),atoi(argv[5]));;
  }
  delete queue;
  exit(encapsulateEnqueuedInfo(argv[0], (unsigned int)atoi(argv[1])));
}

int encapsulateEnqueuedInfo(char* queueFilename, unsigned int dock){
  unsigned int enqueuedInfo = dock << 1;
  if(!strcmp(queueFilename, Queue::goQueueFilename))  enqueuedInfo++;
  return (int)enqueuedInfo;
}

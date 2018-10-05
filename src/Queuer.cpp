#include "Queuer.h"

//argv[0] => filename to create Queue ("queueGo.cc"/"queueBack.cc")
//argv[1] => dock id to create Queue
/*argv[2] => integer to simulate priority when enqueueing (inc/dec value of cont when executing semaphore ops v() and p())
          => also establishes "what" needs to be enqueued:
                - 1 => a random passenger
                - 2 => a walking tourist
                - 3 => a ticket inspection
                - 4 => a custom inspection
*/
//argv[3] (if argv[2] == 2) argv[3] => walking tourist id else argv[3] => file descriptor for writing in pipe
//argv[4] => walking tourist destiny dock id (only if argv[2] == 2)
//argv[5] => 1 if walking tourist has ticket (only if argv[2] == 2)
int main(int argc, char* argv[]){
  Queue* queue = new Queue(argv[0],atoi(argv[1]));
  switch (atoi(argv[2])) {
    case 1:
      queue->enqueueNewPassenger();
      break;
    case 2:
      queue->enqueueWalkingTourist(atoi(argv[3]),atoi(argv[4]),atoi(argv[5]));
      break;
    case 3:
      queue->enqueueTicketInspection();
      break;
    case 4:
      queue->enqueueCustomInspection();
      break;
  }
  delete queue;
  if(!atoi(argv[2])){
    //TODO: tengo que avisar al proceso generador que es exactamente lo que se encolo y donde para que lo vuelva a lanzar
  }
}

unsigned int encapsulateQueueingCommand(){
  
}

unsigned int isNewPassengerCommand(unsigned int cmd){

}

unsigned int isTicketInspectionCommand(unsigned int cmd){

}

unsigned int isCustomInspectionCommand(unsigned int cmd){

}

unsigned int getDockId(unsigned int cmd){

}

unsigned int isGoingQueue(unsigned int cmd){

}

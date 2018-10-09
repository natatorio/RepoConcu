#include "Ship.h"
#include "SignalHandler.h"


Ship::Ship(int shipCapacity){
  blockSignals();
  capacity = shipCapacity;
  srand(getpid());
  if(rand()%PRECISION < PRECISION * LEGAL_SHIP_PROBABILITY)  legalShip = true;
  else legalShip = false;
}

void Ship::inspectShip(){
  blockSignals();
  state = CONFISCATED;
  cout << CONFISCATED << flush;
}

void Ship::inspectTickets(){
  blockSignals();
  for(list<Passenger>::iterator it = passengers.begin(); it != passengers.end(); it++){
    if((*it).ticket != HAS_TICKET){
      it-- = passengers.erase(it);
      cout << FINED << flush;
    }
  }
  unblockSignals();
}

void Ship::downloadWalkingTourist(){
  blockSignals();
  for(list<Passenger>::iterator it = passengers.begin(); it != passengers.end(); it++){
    if((*it).tourist == IS_TOURIST && (*it).destination != city){
      int touristId = (*it).id;
      int touristTicket = (*it).ticket;
      int touristDestination = (*it).destination;
      if(!fork()){
        char* argv[QUEUER_ARGS + 1];
        if(direction == TRAVELING_FOWARD) strcpy(argv[0], Queue::goQueueFilename);
        else  strcpy(argv[0], Queue::backQueueFilename);
        strcpy(argv[1], to_string(city + direction).c_str());
        strcpy(argv[2], Queue::walkingTouristOrder);
        strcpy(argv[3], to_string(touristId).c_str());
        strcpy(argv[4], to_string(touristTicket).c_str());
        strcpy(argv[5], to_string(touristDestination).c_str());
        argv[6] = NULL;
        execv("queuer", argv);
      }
      passengers.erase(it);
      break;
    }
  }
  unblockSignals();
}

char Ship::visitCity(int city){
  this->city = city;
  Queue* boardingQueue;
  if(direction == TRAVELING_FOWARD) boardingQueue = new Queue(Queue::goQueueFilename, city, NOT_INITIALIZE);
  else  boardingQueue = new Queue(Queue::backQueueFilename, city, NOT_INITIALIZE);
  bool morePassengers;
  do{
    blockSignals();
    morePassengers = downloadPassenger(false);
    unblockSignals();
  }while(morePassengers);
  blockSignals();
  while((int)passengers.size() < capacity && state != CONFISCATED){
    unblockSignals();
    passengers.push_back(boardingQueue->getNextPassenger());
    blockSignals();
  }
  delete boardingQueue;
  if(state == CONFISCATED)  while(downloadPassenger(true)){}
  return state;
}

bool Ship::downloadPassenger(bool everyone){
  for(list<Passenger>::iterator it = passengers.begin(); it != passengers.end(); it++){
    if((*it).destination == city || everyone){
      passengers.erase(it);
      return true;
    }
  }
  return false;
}

void Ship::changeDirection(){
  if(direction == TRAVELING_FOWARD) direction = TRAVELING_BACKWARD;
  else direction = TRAVELING_FOWARD;
}

void Ship::blockSignals(){
  sigset_t sa;
  sigemptyset ( &sa );
  sigaddset ( &sa, SIGRTMIN + CUSTOM_SIG );
  sigaddset ( &sa, SIGRTMIN + INSPECTION_SIG );
  sigaddset ( &sa, SIGRTMIN + TOURIST_SIG );
  sigprocmask ( SIG_BLOCK,&sa,NULL );
}

void Ship::unblockSignals(){
  sigset_t sa;
  sigemptyset ( &sa );
  sigaddset ( &sa, SIGRTMIN + CUSTOM_SIG );
  sigaddset ( &sa, SIGRTMIN + INSPECTION_SIG );
  sigaddset ( &sa, SIGRTMIN + TOURIST_SIG );
  sigprocmask ( SIG_UNBLOCK,&sa,NULL );
}

Ship::~Ship(){
    close(1);
}

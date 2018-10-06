#include "Ship.h"

Ship::Ship(int shipCapacity){
  blockSignals();
  capacity = shipCapacity;
  srand((int)getpid());
  if(rand()%PRECISION < PRECISION * LEGAL_SHIP_PROBABILITY)  legalShip = true;
  else legalShip = false;
}

void Ship::inspectShip(){
  blockSignals();
  state = CONFISCATED;
  cout << CONFISCATED << flush;
  unblockSignals();
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
    if((*it).tourist == TOURIST){
      int touristId = (*it).id;
      int touristTicket = (*it).ticket;
      int touristDestination = (*it).destination;
      if(!fork()){
        char* argv[MAX_ARGS + 1];
        if(direction == TRAVELING_FOWARD) strcpy(argv[0], Queue::goQueueFilename);
        else  strcpy(argv[0], Queue::backQueueFilename);
        string str = to_string(city);
        strcpy(argv[1],str.c_str());
        strcpy(argv[2], Queue::walkingTouristOrder);
        str = to_string(touristId);
        strcpy(argv[3], str.c_str());
        str = to_string(touristTicket);
        strcpy(argv[4], str.c_str());
        str = to_string(touristDestination);
        strcpy(argv[5], str.c_str());
        argv[6] = NULL;
        execv("queuer", argv);
      }
      passengers.erase(it);
      break;
    }
  }
  unblockSignals();
}

char Ship::visitCity(int city, int direction){
  this->direction = direction;
  this->city = city;
  Queue* boardingQueue;
  if(direction == TRAVELING_FOWARD) boardingQueue = new Queue(Queue::goQueueFilename, city);
  else  boardingQueue = new Queue(Queue::backQueueFilename, city);
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

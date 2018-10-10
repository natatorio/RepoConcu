#include "Ship.h"
#include "SignalHandler.h"



Ship::Ship(int shipCapacity, int id){
  blockSignals();
  this->id = id;
  capacity = shipCapacity;
  srand(getpid());
  if(rand()%PRECISION <= PRECISION * LEGAL_SHIP_PROBABILITY)  legalShip = true;
  else legalShip = false;
  logger = new Logger("test");
}

void Ship::inspectShip(){
  blockSignals();
  logShipInspection();
  if(!legalShip){
    state = CONFISCATED;
    cout << CONFISCATED << flush;
    logConfiscated();
  }else unblockSignals();
}

void Ship::inspectTickets(){
  blockSignals();
  logTicketInspection();
  for(list<Passenger>::iterator it = passengers.begin(); it != passengers.end(); it++){
    if((*it).ticket != HAS_TICKET){
      sleep(GETING_OFF_DELAY);
      logFined(*it);
      it = passengers.erase(it);
      if(it != passengers.end())  it--;
      cout << FINED << flush;
    }
  }
  unblockSignals();
}

void Ship::downloadWalkingTourist(){
  blockSignals();
  for(list<Passenger>::iterator it = passengers.begin(); it != passengers.end(); it++){
    if((*it).tourist == IS_TOURIST && (*it).destination != city){
      sleep(GETING_OFF_DELAY);
      logTouristWalk(*it);
      if(!fork()){
        char argv[QUEUER_ARGS][MAX_ARG_SIZE];
        if(direction == TRAVELING_FOWARD){
          if(city + direction == N_CITIES - 1) strcpy(argv[0], Queue::backQueueFilename);
          else  strcpy(argv[0], Queue::goQueueFilename);
        }else{
          if(city + direction == 0)  strcpy(argv[0], Queue::goQueueFilename);
          else  strcpy(argv[0], Queue::backQueueFilename);
        }
        strcpy(argv[1], to_string(city + direction).c_str());
        strcpy(argv[2], Queue::walkingTouristOrder);
        strcpy(argv[3], to_string((*it).id).c_str());
        strcpy(argv[4], to_string((*it).destination).c_str());
        strcpy(argv[5], to_string((*it).ticket).c_str());
        char* const args[] = {argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], NULL};
        execv("queuer", args);
      }
      passengers.erase(it);
      break;
    }
  }
  unblockSignals();
}

char Ship::visitCity(int city){
  blockSignals();
  sleep(MOORING_DELAY);
  logMooring();
  bool morePassengers;
  do{
    morePassengers = downloadPassenger(false);
    unblockSignals();
    blockSignals();
  }while(morePassengers);
  if(direction == TRAVELING_BACKWARD && city == 0){
    logUnmooring();
    return state;
  }
  Queue* boardingQueue;
  if(direction == TRAVELING_FOWARD) boardingQueue = new Queue(Queue::goQueueFilename, city, NOT_INITIALIZE);
  else  boardingQueue = new Queue(Queue::backQueueFilename, city, NOT_INITIALIZE);
  cerr <<"llego 1" << endl;
  while((int)passengers.size() < capacity && state != CONFISCATED){
    Passenger passenger = boardingQueue->getNextPassenger();
    passengers.push_back(passenger);
    logBoarding(passenger);
    unblockSignals();
    blockSignals();
  }
  delete boardingQueue;
  if(state == CONFISCATED)  while(downloadPassenger(true)){}
  else logUnmooring();
  return state;
}

bool Ship::downloadPassenger(bool everyone){
  for(list<Passenger>::iterator it = passengers.begin(); it != passengers.end(); it++){
    if((*it).destination == city || everyone){
      passengers.erase(it);
      sleep(GETING_OFF_DELAY);
      logUnboarding(*it);
      return true;
    }
  }
  return false;
}

void Ship::changeDirection(){
  if(direction == TRAVELING_FOWARD) direction = TRAVELING_BACKWARD;
  else direction = TRAVELING_FOWARD;
}

void Ship::setCity(int city){
  this->city = city;
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

void Ship::logMooring(){
  ostringstream msg;
  msg << "Ship " << id << " arrived Dock " << city << endl;
  logger->write(msg);
}

void Ship::logUnmooring(){
  ostringstream msg;
  msg << "Ship " << id << " left Dock " << city << endl;
  logger->write(msg);
}

void Ship::logBoarding(Passenger passenger){
  ostringstream msg;
  msg << "Passenger " << passenger.id;
  if(passenger.tourist == IS_TOURIST) msg << " is a tourist,";
  if(passenger.ticket == HAS_TICKET)  msg << " has a ticket,";
  msg << " got on Ship " << id << " in Dock " << city << " and is traveling to Dock " << passenger.destination << endl;
  logger->write(msg);
}

void Ship::logUnboarding(Passenger passenger){
  ostringstream msg;
  msg << "Passenger " << passenger.id << " got off Ship " << id << " in Dock " << city << endl;
  logger->write(msg);
}

void Ship::logFined(Passenger passenger){
  ostringstream msg;
  msg << "Passenger " << passenger.id << " was fined and taken off Ship " << id << " in Dock " << city << endl;
  logger->write(msg);
}

void Ship::logTouristWalk(Passenger passenger){
  ostringstream msg;
  msg << "Passenger " << passenger.id << " (Tourist) got off Ship " << id << " for sightseeing in Dock " << city << endl;
  logger->write(msg);
}

void Ship::logConfiscated(){
  ostringstream msg;
  msg << "Ship " << id << " was confiscated in dock " << city << endl;
  logger->write(msg);
}

void Ship::logTicketInspection(){
  ostringstream msg;
  msg << "Inspector board Ship " << id << " in Dock " << city << endl;
  logger->write(msg);
}

void Ship::logShipInspection(){
  ostringstream msg;
  msg << "Custom board Ship " << id << " in Dock " << city << endl;
  logger->write(msg);
}

Ship::~Ship(){
  delete logger;
  close(1);
  cerr << "Ship " << id << " reach destructor" << endl;
  while(wait(NULL) > 0){}
  cerr << "Ship " << id << " ends" << endl;
}

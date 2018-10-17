#include "Queue.h"


const char* Queue::goQueueFilename = "goqueue.cc";
const char* Queue::backQueueFilename = "backqueue.cc";
const char* Queue::newPassengerOrder = "NewPassenger";
const char* Queue::walkingTouristOrder = "walkingTourist";

Queue::Queue(const char *filename, int city, int init)
 : semaforo_prod(filename, PASSENGER_QUEUE_SIZE, 1+city, init), semaforo_cons(filename, 0, -1-city, init) {
    this->buffer.crear(filename, city, PASSENGER_QUEUE_SIZE);
    if(!strcmp(filename, goQueueFilename)) travelingWay = TRAVELING_FOWARD;
    else  travelingWay = TRAVELING_BACKWARD;
    srand(getpid());
    this->city = city;
    this->logger = new Logger("test");
}

void Queue::destroy(){
  int memState = NO_LIBERADA;
  while(memState != LIBERADA) memState = this->buffer.liberar();
  this->semaforo_prod.eliminar();
  this->semaforo_cons.eliminar();
  delete logger;
}

Queue::~Queue(){

};

void Queue::enqueueNewPassenger(int id) {
    this->semaforo_prod.p();
    Passenger passenger = this->createNewPassenger(id);
    logRegularArrival(passenger);
    this->writePassenger(passenger);
    this->semaforo_cons.v();
}

void Queue::enqueueWalkingTourist(int touristId, int destinationDock, int hasTicket) {
    Passenger passenger;
    passenger.destination = destinationDock;
    passenger.id = touristId;
    passenger.ticket = hasTicket;
    passenger.tourist = IS_TOURIST;
    if(passenger.destination == city){
      logWalkingTouristArrival(passenger);
      return;
    }
    this->semaforo_prod.p();
    logWalkingTouristArrival(passenger);
    this->writePassenger(passenger);
    this->semaforo_cons.v();
}

Passenger Queue::getNextPassenger() {
    this->semaforo_cons.p();
    Passenger passenger = this->readPassenger();
    sleep(GETING_ON_DELAY);
    this->semaforo_prod.v();
    return passenger;
}

Passenger Queue::createNewPassenger(int id) {
    Passenger passenger;
    passenger.id = id;
    int posibleCities = city;
    if(travelingWay == TRAVELING_FOWARD)  posibleCities = N_CITIES - 1 - city;
    passenger.destination = city + travelingWay * (1 + rand() % posibleCities);
    if(rand() % PRECISION < PRECISION * TOURIST_PROBABILITY)  passenger.tourist = IS_TOURIST;
    else passenger.tourist = ISNT_TOURIST;
    if(rand() % PRECISION < PRECISION * BUY_TICKET_PROBABILITY) passenger.ticket = HAS_TICKET;
    else passenger.ticket = HASNT_TICKET;
    return passenger;
}

void Queue::flush(){
  for(int i = this->semaforo_cons.getCont(); i != 0; i--){
    this->semaforo_cons.p();
    this->semaforo_prod.v();
  }
}

void Queue::writePassenger(Passenger passenger) {
    this->buffer.escribir(passenger, this->posWrite);
    this->posWrite = (this->posWrite + 1) % PASSENGER_QUEUE_SIZE;
}

Passenger Queue::readPassenger() {
    Passenger passenger = this->buffer.leer(this->posRead);
    this->posRead = (this->posRead + 1) % PASSENGER_QUEUE_SIZE;
    return passenger;
}

void Queue::logWalkingTouristArrival(Passenger passenger){
  ostringstream msg;
  msg << "Passenger " << passenger.id << " arrived walking to Dock " << city;
  if(passenger.destination == city) msg << " which is his/her final destination" << endl;
  else  msg << " and is traveling to Dock " << passenger.destination << endl;
  logger->write(msg);
}

void Queue::logRegularArrival(Passenger passenger){
    ostringstream msg;
    msg << "Passenger " << passenger.id;
    if(passenger.tourist == IS_TOURIST) msg << " is a tourist,";
    if(passenger.ticket == HAS_TICKET)  msg << " bought a ticket,";
    msg << " arrived at Dock " << city << " and is traveling to Dock " << passenger.destination << endl;
    logger->write(msg);
}

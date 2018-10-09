#include "Queue.h"


Logger logger("test");
const char* Queue::goQueueFilename = "goqueue.cc";
const char* Queue::backQueueFilename = "backqueue.cc";
const char* Queue::newPassengerOrder = "worker";
const char* Queue::walkingTouristOrder = "tourist";

Queue::Queue(const char *filename, int city, int init)
 : semaforo_prod(filename, QUEUE_SIZE, 1+city, init), semaforo_cons(filename, 0, -1-city, init) {
    this->buffer.crear(filename, city, QUEUE_SIZE);
    if(!strcmp(filename, goQueueFilename)) travelingWay = TRAVELING_FOWARD;
    else  travelingWay = TRAVELING_BACKWARD;
    srand(getpid());
    this->city = city;
}

Queue::~Queue(){
    if(this->buffer.liberar() == LIBERADA){ // solo elimino la cola cuando soy el último proceso cerrando la cola
      this->semaforo_prod.eliminar();
      this->semaforo_cons.eliminar();
    }
};

void Queue::enqueueNewPassenger(int id) {
    cout << "Se pueden encolar " << semaforo_prod.getCont() << endl;
    this->semaforo_prod.p();
    Passenger passenger = this->createNewPassenger(id);
    //printf("Passenger %d", passenger.id);
    ostringstream msg;
    msg << "Passenger " << passenger.id;
    if(passenger.tourist == IS_TOURIST) msg << " is a tourist,";
    msg << " arrived at dock " << city;
    if(passenger.ticket == HAS_TICKET)  msg << ", bought a ticket";
    msg << " and is traveling to city " << passenger.destination << "." << endl;
    string s = msg.str();
    logger.write(s);
    this->writePassenger(passenger);
    this->semaforo_cons.v();
}

void Queue::enqueueWalkingTourist(int touristId, int destinationDock, int hasTicket) {
    ostringstream msg;
    msg << "Tourist " << touristId << " arrived walking to city " << city;
    if(destinationDock == city){
      msg << " which is his/her final destination." << endl;
      string s = msg.str();
      logger.write(s);
      return;
    }
    msg << "and is traveling to city " << destinationDock << "." << endl;
    this->semaforo_prod.p();
    Passenger passenger;
    passenger.destination = destinationDock;
    passenger.id = touristId;
    passenger.ticket = hasTicket;
    passenger.tourist = IS_TOURIST;
    string s = msg.str();
    logger.write(s);
    this->writePassenger(passenger);
    this->semaforo_cons.v();
}

Passenger Queue::getNextPassenger() {
    this->semaforo_cons.p();
    Passenger passenger = this->readPassenger();
    ostringstream msg;
    msg << "Passenger " << passenger.id;
    if(passenger.tourist == IS_TOURIST) msg << " is a tourist";
    if(passenger.ticket == HAS_TICKET)  msg << ", has a ticket";
    msg << " and got onboard of a ship in city " << city << " traveling to city " << passenger.destination << "." << endl;
    string s = msg.str();
    logger.write(s);
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
    this->posWrite = (this->posWrite + 1) % QUEUE_SIZE;
    //printf("passenger added at pos: %d\n", posWrite);
}

Passenger Queue::readPassenger() {
    Passenger passenger = this->buffer.leer(this->posRead);
    this->posRead = (this->posRead + 1) % QUEUE_SIZE;
    //printf("readPassenger: %d, pos: %d\n", passenger.id, posRead);
    return passenger;
}

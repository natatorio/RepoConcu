#include "Queue.h"
#include "Logger.h"
#include <string>
#include <stdlib.h>
#include <time.h>

#define TOURIST 1
#define BUY_TICKET_PROBABILITY 0.87

Logger logger("test");
const char* Queue::backQueueFilename = "backqueue";

Queue::Queue(const char *filename, int id) : semaforo_prod(filename, this->size), semaforo_cons(filename, 0) {
    this->buffer.crear(filename,'a',10);
}

Queue::~Queue(){
    this->buffer.liberar();
    this->semaforo_prod.eliminar();
    this->semaforo_cons.eliminar();

};

void Queue::enqueueNewPassenger(int id) {
    this->semaforo_prod.p();
    Passenger passenger = this->createNewPassenger(id);
    printf("passenger %d", passenger.id);
    std::string str("passenger add.");
    logger.write(str);
    this->buyTicket(passenger);
    this->writePassenger(passenger);
    this->semaforo_cons.v();
}

void Queue::enqueueWalkingTourist(int touristId, int destinationDock, int hasTicket) {
    this->semaforo_prod.p();
    Passenger passenger;
    passenger.destination = destinationDock;
    passenger.id = touristId;
    passenger.ticket = hasTicket;
    passenger.tourist = TOURIST;
    std::string str("Dock : Tourist walk to next city.");
    logger.write(str);
    this->writePassenger(passenger);
    this->semaforo_cons.v();
}

Passenger Queue::getNextPassenger() {
    this->semaforo_cons.p();
    Passenger passenger = this->readPassenger();
    this->semaforo_prod.v();
    return passenger;
}

void Queue::buyTicket(Passenger passenger) {
  if (passenger.ticket == 0 && rand() > BUY_TICKET_PROBABILITY) {
      passenger.ticket = 1;
      //add id of dock
      printf("passenger buy ticket\n");
      std::string str("Dock : Passenger buy a ticket.");
      logger.write(str);
  }
}

Passenger Queue::createNewPassenger(int id) {
    Passenger passenger;
    passenger.id = id;
    passenger.destination = rand() % 4 + 1;
    passenger.tourist = rand() % 1;
    return passenger;
}

void Queue::writePassenger(Passenger passenger) {
    this->buffer.escribir(passenger, this->pos);
    this->pos++;
    printf("passanger added at pos: %d\n", pos);
    std::string str("Dock : Passenger pass through turnstile.");
    logger.write(str);
}

Passenger Queue::readPassenger() {
    Passenger passenger = this->buffer.leer(this->pos);
    this->pos++;
    printf("readPassenger: %d, pos: %d\n", passenger.id, pos);
    std::string str("Dock : Passenger left queue turnstile.");
    logger.write(str);
    return passenger;
}
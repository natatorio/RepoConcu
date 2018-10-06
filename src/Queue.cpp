#include "Queue.h"
#include "Logger.h"
#include <string>
#include <stdlib.h>
#include <time.h>

#define TOURIST 1
#define BUY_TICKET_PROBABILITY 0.87

Logger logger("test");

void Queue::enqueueNewPassenger() {
    this->semaforo_prod.p();
    Passenger passenger = this->createNewPassenger();
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

void Queue::buyTicket(Passenger passenger) {
  if (passenger.ticket == 0 && rand() > BUY_TICKET_PROBABILITY) {
    //add id of dock
    std::string str("Dock : Passenger buy a ticket.");
    logger.write(str);
    passenger.ticket = 1;
  }
}

Passenger Queue::createNewPassenger() {
    Passenger passenger;
    passenger.destination =
}

void Queue::writePassenger(Passenger passenger) {
  this->buffer.escribir(passenger, this->pos);
  this->pos++;
  std::string str("Dock : Passenger pass through turnstile.");
  logger.write(str);
}
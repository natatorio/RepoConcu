#include "Queue.h"
#include "Logger.h"
#include <string>

Logger logger("test");

void Queue::enqueueNewPassenger() {
    this->semaforo_prod.p();
    Passenger passenger = this->createNewPassenger();
    this->buyTicket(passenger);
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

void Queue::writePassenger(Passenger passenger) {
  this->buffer.escribir(passenger, this->pos);
  this->pos++;
  std::string str("Dock : Passenger pass through turnstile.");
  logger.write(str);
}
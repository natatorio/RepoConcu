#ifndef SHIP_H_
#define SHIP_H_

#define CUSTOM_SIG 13
#define INSPECTION_SIG 14
#define TOURIST_SIG 15
#define LEGAL_SHIP_PROBABILITY 0.78
#define QUEUER_ARGS 6

#include "Queue.h"

#include <signal.h>
#include <iostream>
#include <list>
#include <iterator>

class Ship{
  public:
    static const char FINED = 'F';
    static const char CONFISCATED = 'C';

    Ship(int shipCapacity);
    void blockSignals();
    void unblockSignals();
    void inspectTickets();
    void inspectShip();
    void downloadWalkingTourist();
    char visitCity(int city);
    void changeDirection();
    ~Ship();

  private:
    int finedPassengers;
    int capacity;
    int direction = TRAVELING_FOWARD;
    int city;
    list<Passenger> passengers;
    bool legalShip;
    char state = 0;

    bool downloadPassenger(bool everyone);
};

#endif /* SHIP_H_ */

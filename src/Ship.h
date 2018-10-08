#ifndef SHIP_H_
#define SHIP_H_

#define CUSTOM_SIG 13
#define INSPECTION_SIG 14
#define TOURIST_SIG 15
#define LEGAL_SHIP_PROBABILITY 0.78
#define MAX_ARGS 6

#include "Queue.h"

#include <signal.h>
#include <iostream>
#include <unistd.h>
#include <ctime>
#include <list>
#include <iterator>

using namespace std;

class Ship{
  public:
    static const char FINED = 'F';
    static const char CONFISCATED = 'C';

    Ship(int);
    void blockSignals();
    void unblockSignals();
    void inspectTickets();
    void inspectShip();
    void downloadWalkingTourist();
    char visitCity(int);
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

    bool downloadPassenger(bool);
};

#endif /* SHIP_H_ */

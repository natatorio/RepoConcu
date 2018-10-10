#ifndef SHIP_H_
#define SHIP_H_

#include "Queue.h"

#include <sys/wait.h>
#include <signal.h>
#include <iostream>
#include <list>
#include <iterator>

class Ship{
  public:
    static const char FINED = 'F';
    static const char CONFISCATED = 'C';

    Ship(int shipCapacity, int id);
    void blockSignals();
    void unblockSignals();
    void inspectTickets();
    void inspectShip();
    void downloadWalkingTourist();
    char visitCity(int city);
    void changeDirection();
    void setCity(int city);
    ~Ship();

  private:
    int finedPassengers;
    int capacity;
    int direction = TRAVELING_FOWARD;
    int city;
    int id;
    list<Passenger> passengers;
    bool legalShip;
    char state = 0;
    Logger* logger;

    void logShipInspection();
    void logTicketInspection();
    void logMooring();
    void logUnmooring();
    void logConfiscated();
    void logTouristWalk(Passenger);
    void logFined(Passenger);
    void logBoarding(Passenger);
    void logUnboarding(Passenger passenger);
    bool downloadPassenger(bool everyone);
};

#endif /* SHIP_H_ */

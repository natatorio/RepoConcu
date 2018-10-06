#ifndef SHIP_H_
#define SHIP_H_

#include "Queuer.h"

#include <signal.h>
#include <iostream>
#include <unistd.h>
#include <list>
#include <iterator>

using namespace std;

class Ship{
  public:
    static const int CUSTOM_SIG = 13;
    static const int INSPECTION_SIG = 14;
    static const int TOURIST_SIG = 15;
    static const int TRAVELING_FOWARD = 1;
    static const int TRAVELING_BACKWARD = -1;
    static const char FINED = 'F';
    static const char CONFISCATED = 'C';

    Ship(int);
    void blockSignals();
    void unblockSignals();
    void inspectTickets();
    void inspectShip();
    void downloadTourist();
    void visitCity(int, int);
    ~Ship();

  private:
    int finedPassengers;
    int capacity;
    list<Passenger> passengers;
};

#endif /* SHIP_H_ */

#ifndef SHIP_H_
#define SHIP_H_

#include "Queuer.h"

#include <iostream>
#include <unistd.h>

using namespace std;

class Ship{
  public:
    static const int CUSTOM_SIG = 13;
    static const int INSPECTION_SIG = 14;
    static const int TOURIST_SIG = 15;
    static const char FINED = 'F';
    static const char CONFISCATED = 'C';

    Ship(int);
    void inspectTickets();
    void inspectShip();
    void downloadTourist();
    ~Ship();

  private:
    int finedPassengers;
    int capacity;

};


#endif /* SHIP_H_ */

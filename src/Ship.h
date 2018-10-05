#ifndef SHIP_H_
#define SHIP_H_

#include <iostream>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

class Ship{
  public:
    static const char FINED = 'F';
    static const char CONFISCATED = 'C';

    void inspectTickets();
    void inspectShip();
    void downloadTourist();
    Ship(int);
    ~Ship();

  private:
    int finedPassengers;
    int capacity;

};


#endif /* SHIP_H_ */

#ifndef SHIP_H_
#define SHIP_H_

#include <iostream>
#include <unistd.h>

using namespace std;

class Ship{
  public:
    static const char FINED = 'F';
    static const char CONFISCATED = 'C';

    Ship();
    ~Ship();

  private:
    int finedPassengers;

    void blockSignals();
    void unblockSignals();
};

#endif

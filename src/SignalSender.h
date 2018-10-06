#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "CustomHandler.h"

using namespace std;

class SignalSender{
  public:
    SignalSender(char**);
    pid_t getRandomShip();

  private:
    vector<pid_t> ships;
    int signum;
    int sleepTime;
    SIGINT_Handler sigintHandler;

    void addShip(char*);
};

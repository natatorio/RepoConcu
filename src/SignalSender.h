#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <vector>
#include <ctime>
#include <cstdlib>

#include "SignalHandler.h"
#include "SIGINT_Handler.h"

using namespace std;

class SignalSender{
  public:
    SignalSender(char**);
    void startSending();
    ~SignalSender();

  private:
    vector<pid_t> ships;
    int signum;
    int sleepTime;
    SIGINT_Handler sigintHandler;

    void addShip(char*);
    pid_t getRandomShip();
};

#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <vector>
#include <ctime>
#include <cstdlib>

#include "SignalHandler.h"
#include "SIGINT_Handler.h"

class SignalSender{
  public:
    SignalSender(char** argv);
    void startSending();
    ~SignalSender();

  private:
    vector<pid_t> ships;
    int signum;
    int sleepTime;
    SIGINT_Handler sigintHandler;

    void addShip(pid_t shipPid);
    pid_t getRandomShip();
};

#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <sys/types.h>
#include <signal.h>

using namespace std;

class Custom{
  public:
    Custom(char**);

    pid_t getRandomShip();
  private:
    vector<pid_t> ships;

    void addShip(char*);
};

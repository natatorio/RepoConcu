#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

class Custom{
  public:
    Custom();
    void addShip(char*);

  private:
    vector<pid_t> ships;
    pid_t getRandomShip();
};

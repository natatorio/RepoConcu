#include <iostream>
#include <unistd.h>
#include <vector>

using namespace std;

class Inspector{
  public:
    Inspector();
    void addShip(char*);

  private:
    vector<pid_t> ships;

    pid_t getRandomShip();
};

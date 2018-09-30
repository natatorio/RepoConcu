#include <vector>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <cstring>

using namespace std;

class LakeConcu{
  public:
    LakeConcu(int, int);
    ~LakeConcu();
    void startSimulation();
    int getConfiscatedShips();
    int getFinedPassengers();

  private:
    char** pidShips;
    int confiscatedShips;
    int finedPassengers;

};

#include "Pipe.h"
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
    static const char FINED = 'F';
    static const char CONFISCATED = 'C';

    LakeConcu(int, int);
    ~LakeConcu();
    void startSimulation();
    void listenShips();


  private:
    char** pidShips;
    int confiscatedShips;
    int finedPassengers;
    Pipe* pipe;

    void createShips(int, int);
    void createInspector();
    void createCustom();
    int getConfiscatedShips();
    int getFinedPassengers();
};

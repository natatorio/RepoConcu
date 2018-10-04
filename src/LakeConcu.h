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
    void printFinedAndConfiscated();


  private:
    char** pidShips;
    int confiscatedShips;
    int finedPassengers;
    Pipe* pipe;

    void runShips(int, int);
    void runInspector();
    void runCustom();
    int getConfiscatedShips();
    int getFinedPassengers();
};

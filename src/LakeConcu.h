#include <vector>
#include <string>
#include <stdlib.h>
#include <unistd.h>

class LakeConcu{
  public:
    LakeConcu(int, int);
    void startSimulation();
    int getConfiscatedShips();
    int getFinedPassengers();

  private:
    std::vector<pid_t> pidShips;
    int confiscatedShips;
    int finedPassengers;

};

#ifndef LAKECONCU_H_
#define LAKECONCU_H_

#include "Pipe.h"
#include "Ship.h"
#include "Dock.h"

#include <vector>
#include <sys/wait.h>

class LakeConcu{
  public:
    static const char FINED = 'F';
    static const char CONFISCATED = 'C';

    LakeConcu(int nShips, int shipCapacity);
    ~LakeConcu();
    void listenShips();
    void printFinedAndConfiscated();

  private:
    vector <Dock*> docks;
    vector <pid_t> pidShips;
    pid_t generatorPid;
    pid_t customPid;
    pid_t inspectorPid;
    pid_t touristDownloaderPid;
    int confiscatedShips;
    int finedPassengers;
    Pipe* pipe;
    vector <Queue*> goQueues;
    vector <Queue*> backQueues;

    void initDocks();
    void initQueues();
    void runShips(int nShips, int shipCapacity);
    void runGenerator();
    void runCustom();
    void runInspector();
    void runTouristDownloader();
    int getConfiscatedShips();
    int getFinedPassengers();
    void stopGeneratorAndSignalSenders();
};

#endif /* LAKECONCU_H_ */

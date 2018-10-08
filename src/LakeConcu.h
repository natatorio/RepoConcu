#ifndef LAKECONCU_H_
#define LAKECONCU_H_

#define SHIP_ARGS 2
#define GENERATOR_ARGS 1
#define SIGNALSENDER_ARGS 2
#define MAX_ARG_SIZE 50
#define CUSTOM_SLEEP_SECS 3
#define INSPECTOR_SLEEP_SECS 2
#define TOURISTDOWLOADER_SLEEP_SECS 1

#include "Pipe.h"
#include "Ship.h"

#include <sys/wait.h>

class LakeConcu{
  public:
    static const char FINED = 'F';
    static const char CONFISCATED = 'C';

    LakeConcu(int nShips, int shipCapacity);
    ~LakeConcu();
    void listenShips();
    void printFinedAndConfiscated();
    void stopGeneratorAndSignalSenders();

  private:
    char (*pidShips)[MAX_ARG_SIZE];
    pid_t generatorPid;
    pid_t customPid;
    pid_t inspectorPid;
    pid_t touristDownloaderPid;
    int confiscatedShips;
    int finedPassengers;
    Pipe* pipe;

    void runShips(int nShips, int shipCapacity);
    void runGenerator();
    void runCustom();
    void runInspector();
    void runTouristDownloader();
    int getConfiscatedShips();
    int getFinedPassengers();
};

#endif /* LAKECONCU_H_ */

#ifndef LAKECONCUCONTAINER_H_
#define LAKECONCUCONTAINER_H_

#include "LakeConcu.h"
#include "SignalHandler.h"
#include "InfoHandler.h"

class LakeConcuContainer{
  public:
    LakeConcuContainer(int nShips, int shipCapacity);
    void listenShips();
    ~LakeConcuContainer();

  private:
    LakeConcu* lakeConcu;
    InfoHandler infoHandler;

};

#endif /* LAKECONCUCONTAINER_H_ */

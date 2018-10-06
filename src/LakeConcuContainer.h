#ifndef LAKECONCUCONTAINER_H_
#define LAKECONCUCONTAINER_H_

#include "LakeConcu.h"
#include "SignalHandler.h"
#include "InfoHandler.h"

using namespace std;

class LakeConcuContainer{
  public:

    LakeConcuContainer(int, int);
    ~LakeConcuContainer();

  private:
    LakeConcu* lakeConcu;
    InfoHandler infoHandler;

};


#endif /* LAKECONCUCONTAINER_H_ */

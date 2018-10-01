#include "SignalHandler.h"
#include "CustomHandler.h"
#include "TouristHandler.h"
#include "InspectionHandler.h"

using namespace std;

class ShipContainer{
  public:
    Ship* ship;

    ShipContainer();
    ~ShipContainer();

  private:


    void blockSignals();
    void unblockSignals();
};

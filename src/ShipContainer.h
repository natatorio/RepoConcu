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
    CustomHandler customHandler;
    InspectionHandler inspectionHandler;
    TouristHandler touristHandler;

    void blockSignals();
    void unblockSignals();
};

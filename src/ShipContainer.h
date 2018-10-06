#include "CustomHandler.h"
#include "TouristHandler.h"
#include "InspectorHandler.h"
#include "SignalHandler.h"

class ShipContainer{
  public:
    Ship* ship;
    ShipContainer(int);
    ~ShipContainer();

  private:
    CustomHandler customHandler;
    InspectionHandler inspectionHandler;
    TouristHandler touristHandler;

    void blockSignals();
    void ignoreAndUnblockSignals();
};

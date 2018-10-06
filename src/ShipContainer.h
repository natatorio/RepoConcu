#include "CustomHandler.h"
#include "TouristHandler.h"
#include "InspectorHandler.h"
#include "SignalHandler.h"

class ShipContainer{
  public:
    Ship* ship;
    ShipContainer(int, int);
    void startJourney();
    ~ShipContainer();

  private:
    CustomHandler customHandler;
    InspectionHandler inspectionHandler;
    TouristHandler touristHandler;
    int nCities;
    int direction = 1;

    void blockSignals();
    void ignorePendingSignals();
    void unblockSignals();
};

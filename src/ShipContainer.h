#ifndef SHIPCONTAINER_H_
#define SHIPCONTAINER_H_

#include "CustomHandler.h"
#include "TouristHandler.h"
#include "InspectorHandler.h"
#include "SignalHandler.h"
#include "Dock.h"

#include <vector>

class ShipContainer{
  public:
    Ship* ship;
    ShipContainer(int capacity, int nCities, int id);
    void startJourney();
    ~ShipContainer();

  private:
    CustomHandler customHandler;
    InspectionHandler inspectionHandler;
    TouristHandler touristHandler;
    int id;
    int nCities;
    int direction = TRAVELING_FOWARD;
    vector <Dock*> docks;
    Logger* logger;

    void ignorePendingSignals();
    void changeDirection();
};
#endif /* SHIPCONTAINER_H_ */

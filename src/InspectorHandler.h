#ifndef INSPECTION_HANDLER_H_
#define INSPECTION_HANDLER_H_

#include "EventHandler.h"

class InspectionHandler : public EventHandler {
  private:
    Ship* ship;

  public:
    InspectionHandler () {
		}

    ~InspectionHandler () {
		}

    virtual int handleSignal ( int signum ) {
			assert ( signum == SIGRTMIN + ship->INSPECTION_SIG );
			ship->inspectTickets();
			return 0;
		}

		virtual void addShip(Ship* ship){
			this->ship = ship;
		}
};
#endif /* INSPECTION_HANDLER_H_ */

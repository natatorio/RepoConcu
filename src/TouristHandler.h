#ifndef TOURIST_HANDLER_H_
#define TOURIST_HANDLER_H_

#include "EventHandler.h"

class TouristHandler : public EventHandler {
  private:
		Ship* ship;

 	public:
    TouristHandler () {
		}

    ~TouristHandler () {
		}

    virtual int handleSignal ( int signum ) {
			assert ( signum == SIGRTMIN + TOURIST_SIG );
			ship->downloadWalkingTourist();
			return 0;
		}

    virtual void addShip(Ship* ship){
			this->ship = ship;
		}
};
#endif /* TOURIST_HANDLER_H_ */

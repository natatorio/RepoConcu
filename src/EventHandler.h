#ifndef EVENTHANDLER_H_
#define EVENTHANDLER_H_

#include "Ship.h"

class EventHandler {

public:
	virtual int handleSignal ( int signum ) = 0;
	virtual void addShip(Ship* ship){
		this->ship = ship;
	}
	virtual ~EventHandler () {};

protected:
	Ship* ship;
};

#endif /* EVENTHANDLER_H_ */

#ifndef EVENTHANDLER_H_
#define EVENTHANDLER_H_

#include "Ship.h"

class EventHandler {

public:
	virtual int handleSignal ( int signum ) = 0;
	virtual void addShip(Ship* ship) = 0;
	virtual ~EventHandler () {};
};

#endif /* EVENTHANDLER_H_ */

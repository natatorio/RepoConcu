#ifndef EVENTHANDLER_H_
#define EVENTHANDLER_H_

#include "Ship.h"

#include <signal.h>
#include <assert.h>

class EventHandler {

public:
	virtual int handleSignal ( int signum ) = 0;
	virtual ~EventHandler () {};

protected:
	Ship* ship;
};

#endif /* EVENTHANDLER_H_ */

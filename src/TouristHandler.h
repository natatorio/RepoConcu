#ifndef TOURIST_HANDLER_H_
#define TOURIST_HANDLER_H_

#include <signal.h>
#include <assert.h>

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
			assert ( signum == SIGRTMIN+15 );
			ship->downloadTourist();
			return 0;
		}

};

#endif /* TOURIST_HANDLER_H_ */

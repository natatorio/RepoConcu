#ifndef CUSTOM_HANDLER_H_
#define CUSTOM_HANDLER_H_

#include <signal.h>
#include <assert.h>

#include "EventHandler.h"

class CustomHandler : public EventHandler {

	private:
		Ship* ship;

	public:

		CustomHandler () {
		}

		~CustomHandler () {
		}

		virtual int handleSignal ( int signum ) {
			assert ( signum == SIGRTMIN+13 );
			std::cout << "aoin" << std::endl;
			ship->inspectShip();
			return 0;
		}

};

#endif /* CUSTOM_HANDLER_H_ */

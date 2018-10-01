#ifndef INSPECTION_HANDLER_H_
#define INSPECTION_HANDLER_H_

#include <signal.h>
#include <assert.h>

#include "EventHandler.h"

class InspectionHandler : public EventHandler {

	public:

		InspectionHandler () {
		}

		~InspectionHandler () {
		}

		virtual int handleSignal ( int signum ) {
			assert ( signum == SIGRTMIN+14 );
			ship->inspectTickets();
			return 0;
		}

};

#endif /* INSPECTION_HANDLER_H_ */

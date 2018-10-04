#ifndef INSPECTION_HANDLER_H_
#define INSPECTION_HANDLER_H_

#include "EventHandler.h"

class InspectionHandler : public EventHandler {

	public:

		static const int INSPECTION_SIG = 48;

		InspectionHandler () {
		}

		~InspectionHandler () {
		}

		virtual int handleSignal ( int signum ) {
			assert ( signum == INSPECTION_SIG );
			ship->inspectTickets();
			return 0;
		}
		virtual void addShip(Ship* ship){
			this->ship = ship;
		}

};

#endif /* INSPECTION_HANDLER_H_ */

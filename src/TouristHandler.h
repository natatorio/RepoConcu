#ifndef TOURIST_HANDLER_H_
#define TOURIST_HANDLER_H_

#include "EventHandler.h"

class TouristHandler : public EventHandler {

	private:
		Ship* ship;

	public:

		static const int TOURIST_SIG = 49;

		TouristHandler () {
		}

		~TouristHandler () {
		}

		virtual int handleSignal ( int signum ) {
			assert ( signum == TOURIST_SIG );
			ship->downloadTourist();
			return 0;
		}
		virtual void addShip(Ship* ship){
			this->ship = ship;
		}

};

#endif /* TOURIST_HANDLER_H_ */

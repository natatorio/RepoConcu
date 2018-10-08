#ifndef CUSTOM_HANDLER_H_
#define CUSTOM_HANDLER_H_

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
      assert ( signum == SIGRTMIN + CUSTOM_SIG );
			ship->inspectShip();
			return 0;
		}

		virtual void addShip(Ship* ship){
			this->ship = ship;
		}
};
#endif /* CUSTOM_HANDLER_H_ */

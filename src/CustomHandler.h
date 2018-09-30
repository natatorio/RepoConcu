#ifndef CUSTOM_HANDLER_H_
#define CUSTOM_HANDLER_H_

#include <signal.h>
#include <assert.h>

#include "EventHandler.h"

class CustomHandler : public EventHandler {

	private:
		Ship* ship;

	public:

		SIGINT_Handler () {
		}

		~SIGINT_Handler () {
		}

		virtual int handleSignal ( int signum ) {
			assert ( signum == SIGINT );
			this->gracefulQuit = 1;
			return 0;
		}

		sig_atomic_t getGracefulQuit () const {
			return this->gracefulQuit;
		}

};

#endif /* CUSTOM_HANDLER_H_ */

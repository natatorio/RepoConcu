#ifndef SIGNALHANDLER_H_
#define SIGNALHANDLER_H_

#include <memory.h>

#include "EventHandler.h"

class SignalHandler {

	private:
		static SignalHandler* instance;
		static EventHandler* signal_handlers [ NSIG ];

		SignalHandler ( void );
		static void dispatcher ( int signum );

	public:
		static SignalHandler* getInstance ();
		static void destruir ();
		EventHandler* registrarHandler ( int signum,EventHandler* eh, int flags);
		int removerHandler ( int signum );
		void ignorePending(int signum);

};

#endif /* SIGNALHANDLER_H_ */

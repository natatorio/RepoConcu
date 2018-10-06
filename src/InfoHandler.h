#ifndef INFO_HANDLER_H_
#define INFO_HANDLER_H_

#include "EventHandler.h"

class InfoHandler : public EventHandler {

	private:
		LakeConcu* lakeConcu;

	public:

		static const int INFO_SIG = 13;

		InfoHandler () {
		}

		~InfoHandler () {
		}

		virtual int handleSignal ( int signum ) {
			assert ( signum == SIGRTMIN + INFO_SIG );
			lakeConcu->printFinedAndConfiscated();
			return 0;
		}
		virtual void addLakeConcu(LakeConcu* lakeConcu){
			this->lakeConcu = lakeConcu;
		}

};

#endif /* INFO_HANDLER_H_ */

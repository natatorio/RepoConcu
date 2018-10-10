#ifndef QUEUER_H_
#define QUEUER_H_

#include "Queue.h"
#include "SignalHandler.h"
#include "SIGINT_Handler.h"

int encapsulateEnqueuedInfo(char* filename, unsigned int dock);

#endif /* QUEUER_H_ */

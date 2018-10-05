#ifndef QUEUER_H_
#define QUEUER_H_

#define MAX_ARGS 6

#include "Queue.h"

#include <stdlib.h>

unsigned int encapsulateQueueingOrder();
unsigned int isNewPassengerOrder(unsigned int);
unsigned int isTicketInspectionOrder(unsigned int);
unsigned int isCustomInspectionOrder(unsigned int);
unsigned int getDockId(unsigned int);
unsigned int isGoingQueue(unsigned int);


#endif /* QUEUER_H_ */

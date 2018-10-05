#ifndef QUEUER_H_
#define QUEUER_H_

#include <stdlib.h>

unsigned int encapsulateQueueingCommand();
unsigned int isNewPassengerCommand(unsigned int);
unsigned int isTicketInspectionCommand(unsigned int);
unsigned int isCustomInspectionCommand(unsigned int);
unsigned int getDockId(unsigned int);
unsigned int isGoingQueue(unsigned int);


#endif /* QUEUER_H_ */

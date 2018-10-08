#ifndef QUEUER_H_
#define QUEUER_H_

#define MAX_WALKING_SECS 3

#include "Queue.h"

#include <string.h>
#include <stdlib.h>

int encapsulateEnqueuedInfo(char*, unsigned int);
int getDockId(int);
int isGoingQueue(int);


#endif /* QUEUER_H_ */

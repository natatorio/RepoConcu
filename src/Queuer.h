#ifndef QUEUER_H_
#define QUEUER_H_

#define MAX_ARGS 6

#include "Queue.h"

#include <string.h>
#include <stdlib.h>

int encapsulateEnqueuedInfo(char*, int);
int getDockId(int);
int isGoingQueue(int);


#endif /* QUEUER_H_ */

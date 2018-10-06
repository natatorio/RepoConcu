
#include "../Queue.h"
#include <sys/types.h>
#include <unistd.h>

void testQueue() {
    int pid = fork();
    printf("pid hijo: %d", pid);
    if (pid) {
        Queue queuePush(Queue::backQueueFilename, 1);
        printf("padre va a pushear");
        queuePush.enqueueNewPassenger(1);
        printf("padre pusheo");
    } else {
        Queue queueRetrieve(Queue::backQueueFilename, 1);
        printf("hijo va a sacar");
        Passenger passenger = queueRetrieve.getNextPassenger();
        printf("%s", passenger.id);
    }

}

int main() {
    printf("enter main");
    testQueue();
    return 0;
}
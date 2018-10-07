
#include "../Queue.h"
#include "../Logger.h"
#include <sys/types.h>
#include <unistd.h>

void testQueue() {
    std::string logname("testlogQueue");
    Logger logger(logname);

    int pid = fork();
    printf("pid hijo: %d", pid);
    logger.write("fork");
    if (pid) {
        Queue queuePush(Queue::backQueueFilename, 1);
        printf("padre va a pushear");
        logger.write("padre va a pushear");
        queuePush.enqueueNewPassenger(1);
        printf("padre pusheo");
    } else {
        sleep(5);
        Queue queueRetrieve(Queue::backQueueFilename, 1);
        printf("hijo va a sacar");
        Passenger passenger = queueRetrieve.getNextPassenger();
        printf("hijos aco: %d", passenger.id);
    }

}

void testQueue2() {
    std::string logname("testlogQueue\n");
    Logger logger(logname);

    int pid = fork();
    printf("pid hijo: %d\n", pid);
    logger.write("fork");
    if (pid) {
        Queue queuePush(Queue::backQueueFilename, 1);
        for (int i = 0; i < 5; ++i) {
            printf("padre va a pushear\n");
            logger.write("padre va a pushear");
            queuePush.enqueueNewPassenger(i);
            printf("padre pusheo\n");
        }
    } else {
        Queue queueRetrieve(Queue::backQueueFilename, 1);
        for (int i = 0; i < 5; ++i) {
            printf("hijo va a sacar\n");
            Passenger passenger = queueRetrieve.getNextPassenger();
            printf("hijos aco: %d\n", passenger.id);
        }
    }

}

int main() {
    printf("enter main\n");
    testQueue2();
    return 0;
}
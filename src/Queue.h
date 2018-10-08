#ifndef QUEUE_H_
#define QUEUE_H_

#define N_CITIES 5
#define IS_TOURIST 1
#define ISNT_TOURIST 0
#define HAS_TICKET 1
#define HASNT_TICKET 0
#define TOURIST_PROBABILITY 0.44
#define BUY_TICKET_PROBABILITY 0.87
#define PRECISION 100
#define QUEUE_SIZE 10
#define TRAVELING_FOWARD 1
#define TRAVELING_BACKWARD -1

#include "Logger.h"
#include "Semaforo.h"
#include "MemoriaCompartida.h"

struct Passenger {
    int id;
    short int ticket;
    short int destination;
    short int tourist;
};

class Queue {
  public:
    static const char* goQueueFilename;
    static const char* backQueueFilename;
    static const char* newPassengerOrder;
    static const char* walkingTouristOrder;

    Queue(const char* filename, int city);
    void enqueueNewPassenger(int id);
    void enqueueWalkingTourist(int touristId, int destinationDock, int hasTicket);
    Passenger getNextPassenger();
    void flush();
    ~Queue();

  private:
    int posRead = 0;
    int posWrite = 0;
    Semaforo semaforo_prod;
    Semaforo semaforo_cons;
    MemoriaCompartida<Passenger> buffer;
    Passenger readPassenger();
    Passenger createNewPassenger(int id);
    char travelingWay;
    int city;

    void writePassenger(Passenger passenger);
};


#endif /* QUEUE_H_ */

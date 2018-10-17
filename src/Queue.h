#ifndef QUEUE_H_
#define QUEUE_H_

#include "Constants.h"
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

    Queue(const char* filename, int city, int init);
    void enqueueNewPassenger(int id);
    void enqueueWalkingTourist(int touristId, int destinationDock, int hasTicket);
    Passenger getNextPassenger();
    void flush();
    void destroy();
    ~Queue();

  private:
    int posRead = 0;
    int posWrite = 0;
    Semaforo semaforo_prod;
    Semaforo semaforo_cons;
    MemoriaCompartida<Passenger> buffer;
    MemoriaCompartida<int> posiciones;
    Passenger readPassenger();
    Passenger createNewPassenger(int id);
    char travelingWay;
    int city;
    Logger* logger;

    void writePassenger(Passenger passenger);
    void logRegularArrival(Passenger passenger);
    void logWalkingTouristArrival(Passenger passenger);
};


#endif /* QUEUE_H_ */

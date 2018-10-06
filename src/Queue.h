#ifndef QUEUE_H_
#define QUEUE_H_

#define TOURIST 1
#define HAS_TICKET 1

struct Passenger {
    int id;
    short int ticket;
    short int origin;
    short int destination;
    short int tourist;
};

class Queue{
  public:
    static char const* goQueueFilename;
    static char const* backQueueFilename;
    static char const* newPassengerOrder;
    static char const* walkingTouristOrder;
    static const int size = 10;

    Queue(const char*, int);
    void enqueueNewPassenger();
    void enqueueWalkingTourist(int, int, int);
    void flush();
    Passenger getNextPassenger();
    ~Queue();

  private:

};


#endif /* QUEUE_H_ */

#ifndef QUEUE_H_
#define QUEUE_H_



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
    ~Queue();

  private:

};


#endif /* QUEUE_H_ */

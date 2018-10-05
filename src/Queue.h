#ifndef QUEUE_H_
#define QUEUE_H_



class Queue{
  public:
    static char const* goQueueFilename;
    static char const* backQueueFilename;
    static char const* newPassengerOrder;
    static char const* walkingTouristOrder;
    static char const* ticketInspectionOrder;
    static char const* customInspectionOrder;
    static const int size = 10;
    //size >= newPassengerOrder + ticketInspectionOrder + customInspectionOrder

    Queue(const char*, int);
    void enqueueNewPassenger();
    void enqueueWalkingTourist(char*, char*, char*);
    void enqueueTicketInspection();
    void enqueueCustomInspection();
    void flush();
    ~Queue();

  private:

};


#endif /* QUEUE_H_ */

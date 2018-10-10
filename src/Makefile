CPP = g++
CPPFLAGS = -std=gnu++11 -Wall
LAKECONCU = LakeConcuContainer.o LakeConcu.o Pipe.o SignalHandler.o Logger.o $(DOCK)
SHIP = ShipContainer.o Ship.o Pipe.o SignalHandler.o Dock.o $(QUEUE)
GENERATOR = Generator.o SignalHandler.o $(QUEUE)
QUEUER = Queuer.o SignalHandler.o $(QUEUE)
QUEUE = Queue.o Logger.o Semaforo.o
SIGNALSENDER = SignalSender.o SignalHandler.o
DOCK = Dock.o Semaforo.o
execLakeConcu = lakeConcu
execShip = ship
execGenerator = generator
execQueuer = queuer
execSignalSender = signalSender

.PHONY: all *.o

all:	buildLakeConcu buildShip buildSignalSender buildGenerator buildQueuer
	rm test

LakeConcuContainer.o: LakeConcuContainer.cpp LakeConcuContainer.h
	$(CPP) $(CPPFLAGS) -c LakeConcuContainer.cpp

LakeConcu.o: LakeConcu.cpp LakeConcu.h
	$(CPP) $(CPPFLAGS) -c LakeConcu.cpp

Generator.o:	Generator.cpp Generator.h
	$(CPP) $(CPPFLAGS) -c Generator.cpp

Queuer.o:	Queuer.cpp Queuer.h
	$(CPP) $(CPPFLAGS) -c Queuer.cpp

Queue.o:	Queue.cpp Queue.h
	$(CPP) $(CPPFLAGS) -c Queue.cpp

ShipContainer.o:	ShipContainer.cpp ShipContainer.h
	$(CPP) $(CPPFLAGS) -c ShipContainer.cpp

Ship.o:	Ship.cpp Ship.h
	$(CPP) $(CPPFLAGS) -c Ship.cpp

Pipe.o:	Pipe.cpp Pipe.h
	$(CPP) $(CPPFLAGS) -c Pipe.cpp

SignalHandler.o: SignalHandler.cpp SignalHandler.h
	$(CPP) $(CPPFLAGS) -c SignalHandler.cpp

SignalSender.o: SignalSender.cpp SignalSender.h
	$(CPP) $(CPPFLAGS) -c SignalSender.cpp

Logger.o: Logger.cpp Logger.h
	$(CPP) $(CPPFLAGS) -c Logger.cpp

Dock.o: Dock.cpp Dock.h
	$(CPP) $(CPPFLAGS) -c Dock.cpp

Semaforo.o: Semaforo.cpp Semaforo.h
	$(CPP) $(CPPFLAGS) -c Semaforo.cpp

buildLakeConcu: $(LAKECONCU)
	$(CPP) $(CPPFLAGS) $(LAKECONCU) -o $(execLakeConcu)

buildShip: $(SHIP)
	$(CPP) $(CPPFLAGS) $(SHIP) -o $(execShip)

buildGenerator: $(GENERATOR)
	$(CPP) $(CPPFLAGS) $(GENERATOR) -o $(execGenerator)

buildQueuer: $(QUEUER)
	$(CPP) $(CPPFLAGS) $(QUEUER) -o $(execQueuer)

buildSignalSender: $(SIGNALSENDER)
	$(CPP) $(CPPFLAGS) $(SIGNALSENDER) -o $(execSignalSender)

clean:
	rm -f *.o $(execLakeConcu) $(execShip) $(execGenerator) $(execSignalSender) $(execQueuer)

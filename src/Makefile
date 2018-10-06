CPP = g++
CPPFLAGS = -std=gnu++11 -Wall
LAKECONCU = LakeConcuContainer.o LakeConcu.o Pipe.o SignalHandler.o
SHIP = ShipContainer.o Ship.o Pipe.o SignalHandler.o
GENERATOR = Generator.o SignalHandler.o Queuer.o
QUEUER = Queuer.o
execLakeConcu = lakeConcu
execShip = ship
execGenerator = generator
execQueuer = queuer
execSignalSender = signalSender

.PHONY: all *.o

all: buildLakeConcu buildShip buildGenerator buildQueuer buildSignalSender

LakeConcuContainer.o: LakeConcuContainer.cpp LakeConcuContainer.h
	$(CPP) $(CPPFLAGS) -c LakeConcuContainer.cpp

LakeConcu.o: LakeConcu.cpp LakeConcu.h
	$(CPP) $(CPPFLAGS) -c LakeConcu.cpp

Generator.o:	Generator.cpp Generator.h
	$(CPP) $(CPPFLAGS) -c Generator.cpp

Queuer.o:	Queuer.cpp Queuer.h
	$(CPP) $(CPPFLAGS) -c Queuer.cpp

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

CPP = g++
CPPFLAGS = -std=gnu++11 -Wall
LAKECONCU = LakeConcu.o Pipe.o SignalHandler.o
CUSTOM = Custom.o
INSPECTOR = Inspector.o
SHIP = ShipContainer.o Ship.o Pipe.o SignalHandler.o
execLakeConcu = lakeConcu
execShip = ship
execInspector = inspector
execCustom = custom


.PHONY: all *.o

all: buildLakeConcu buildShip buildCustom buildInspector

LakeConcu.o: LakeConcu.cpp LakeConcu.h
	$(CPP) $(CPPFLAGS) -c LakeConcu.cpp

Custom.o:	Custom.cpp Custom.h
	$(CPP) $(CPPFLAGS) -c Custom.cpp

Inspector.o: Inspector.cpp Inspector.h
	$(CPP) $(CPPFLAGS) -c Inspector.cpp

Ship.o:	Ship.cpp Ship.h
	$(CPP) $(CPPFLAGS) -c Ship.cpp

ShipContainer.o:	ShipContainer.cpp ShipContainer.h CustomHandler.h TouristHandler.h InspectionHandler.h EventHandler.h
	$(CPP) $(CPPFLAGS) -c ShipContainer.cpp

Pipe.o:	Pipe.cpp Pipe.h
	$(CPP) $(CPPFLAGS) -c Pipe.cpp

SignalHandler.o: SignalHandler.cpp SignalHandler.h
	$(CPP) $(CPPFLAGS) -c SignalHandler.cpp

buildLakeConcu: $(LAKECONCU)
	$(CPP) $(CPPFLAGS) $(LAKECONCU) -o $(execLakeConcu)

buildShip: $(SHIP)
	$(CPP) $(CPPFLAGS) $(SHIP) -o $(execShip)

buildCustom: $(CUSTOM)
	$(CPP) $(CPPFLAGS) $(CUSTOM) -o $(execCustom)

buildInspector: $(INSPECTOR)
	$(CPP) $(CPPFLAGS) $(INSPECTOR) -o $(execInspector)

clean:
	rm -f *.o $(execLakeConcu) $(execShip) $(execInspector) $(execCustom)

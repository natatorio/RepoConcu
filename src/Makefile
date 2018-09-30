CPPC = g++
CPPFLAGS = -std=gnu++11 -Wall
LAKECONCU = LakeConcu.o
CUSTOM = Custom.o
INSPECTOR = Inspector.o
SHIP = Ship.o
execLakeConcu = lakeConcu
execShip = ship
execInspector = inspector
execCustom = custom




LakeConcu.o: LakeConcu.cpp LakeConcu.h

Custom.o:	Custom.cpp Custom.h

Inspector.o:	Inspector.cpp Inspector.h

Ship.o:	Ship.cpp Ship.h

buildLakeConcu: $(LAKECONCU)
	$(CPP) $(CPPFLAGS) $(LAKECONCU) -o $(execLakeConcu)

buildShip: $(SHIP)
	$(CPP) $(CPPFLAGS) $(SHIP) -o $(execShip)

buildCustom: $(CUSTOM)
	$(CPP) $(CPPFLAGS) $(CUSTOM) -o $(execCustom)

buildInspector: $(INSPECTOR)
	$(CPP) $(CPPFLAGS) $(INSPECTOR) -o $(execInspector)

all:
	buildLakeConcu buildShip buildCustom buildInspector

clean:
	rm -f *.o $(lakeConcu)

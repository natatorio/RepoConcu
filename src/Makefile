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


.PHONY: all *.o

LakeConcu.o: LakeConcu.cpp LakeConcu.h

Custom.o:	Custom.cpp Custom.h

Inspector.o: Inspector.cpp Inspector.h

Ship.o:	Ship.cpp Ship.h

buildLakeConcu:
	$(CPP) $(CPPFLAGS) -o $(execLakeConcu) $(LAKECONCU)

buildShip:
	$(CPP) $(CPPFLAGS) -o $(execShip) $(SHIP)

buildCustom:
	$(CPP) $(CPPFLAGS) -o $(execCustom) $(CUSTOM)

buildInspector:
	$(CPP) $(CPPFLAGS) -o $(execInspector) $(INSPECTOR)

all:
	buildLakeConcu buildShip buildCustom buildInspector

clean:
	rm -f *.o $(execLakeConcu) $(execShip) $(execInspector) $(execCustom)

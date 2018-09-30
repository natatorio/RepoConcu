CPP = g++
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

all: buildLakeConcu buildShip buildCustom buildInspector

LakeConcu.o: LakeConcu.cpp LakeConcu.h
	$(CPP) $(CPPFLAGS) -c LakeConcu.cpp

Custom.o:	Custom.cpp Custom.h
	$(CPP) $(CPPFLAGS) -c Custom.cpp

Inspector.o: Inspector.cpp Inspector.h
	$(CPP) $(CPPFLAGS) -c Inspector.cpp

Ship.o:	Ship.cpp Ship.h
	$(CPP) $(CPPFLAGS) -c Ship.cpp

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

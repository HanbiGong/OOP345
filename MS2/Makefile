Station.o: Utilities.h Station.h Station.cpp
	g++ -c Station.cpp

Utilities.o: Utilities.h Utilities.cpp
	g++ -c Utilities.cpp

CustomerOrder.o: Station.h CustomerOrder.h CustomerOrder.cpp
	g++ -c CustomerOrder.cpp

ms2.o : ms2.cpp Station.h Utilities.h CustomerOrder.h
	g++ -c ms2.cpp

main : Station.o Utilities.o CustomerOrder.o ms2.o
	g++ Station.o Utilities.o CustomerOrder.o ms2.o -o main

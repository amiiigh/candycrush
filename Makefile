a.out : main.o graphic.o candy.o 
	g++ *.o  -lSDL -lSDL_ttf

main.o : main.cpp candy.cpp candy.h 
	g++ -c main.cpp -lSDL -lSDL_ttf

candy.o : candy.cpp candy.h graphic.cpp graphic.h 
	g++ -c candy.cpp -lSDL -lSDL_ttf
	
graphic.o : graphic.cpp graphic.h
	g++ -c graphic.cpp -lSDL -lSDL_ttf


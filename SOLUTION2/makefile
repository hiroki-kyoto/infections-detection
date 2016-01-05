CC = g++ -o

all: cil.app

cil.app: cil.o
	$(CC) cil.app cil.o
	
cil.o: cil.cpp config.h

clean:
	-rm *.app
	-rm *.o

run:
	./cil.app

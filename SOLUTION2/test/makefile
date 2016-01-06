# makefile for test build
all : t_node.app

CC = g++ -o

t_node.app : t_node.o
	$(CC) t_node.app t_node.o

t_node.o : t_node.cpp


clean : 
	-rm *.o
	-rm *.app

run :
	./t_node.app

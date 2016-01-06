# makefile for test build
all : t_node.app t_list.app

CC = g++ -o

t_node.app : t_node.o
	$(CC) t_node.app t_node.o
t_node.o : t_node.cpp

t_list.app : t_list.o
	$(CC) t_list.app t_list.o
t_list.o : t_list.cpp

clean : 
	-rm *.o
	-rm *.app

run :
	./t_node.app
	./t_list.app

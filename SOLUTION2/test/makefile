# makefile for test build
all : t_node.app t_list.app t_encode.app t_memcpy.app

CC = g++ -o

t_node.app : t_node.o
	$(CC) t_node.app t_node.o
t_node.o : t_node.cpp

t_list.app : t_list.o
	$(CC) t_list.app t_list.o
t_list.o : t_list.cpp

t_encode.app:t_encode.o
	$(CC) t_encode.app t_encode.o
t_encode.o:t_encode.cpp

t_memcpy.app:t_memcpy.o
	$(CC) t_memcpy.app t_memcpy.o
t_memcpy.o:t_memcpy.cpp

clean : 
	-rm *.o
	-rm *.app

run :
	./t_node.app
	./t_list.app
	./t_encode.app
	./t_memcpy.app

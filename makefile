# for sequence searching program
all : freq_search.o
t_freq_search.o : test/t_freq_search.cpp
freq_search.o : freq_search.h

.PHONY : clean

clean :
	-rm *.o
	-rm .app
install :
	./infect_detect.app

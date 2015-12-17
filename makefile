# for sequence searching program
all : build_lib.app

build_lib.app : build_lib.o
	g++ -o build_lib.app build_lib.o
build_lib.o : build_lib.cpp settings.h

check_index.app : check_index.o
	g++ -o check_index.app check_index.o
check_index.o : check_index.cpp

.PHONY : clean
clean :
	-rm *.o
	-rm *.app
install :
	./build_lib.app

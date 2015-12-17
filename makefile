# for sequence searching program
all : build_human_lib.app

build_human_lib.app : build_human_lib.o
	g++ -o build_human_lib.app build_human_lib.o
build_human_lib.o : build_human_lib.cpp settings.h

check_index.app : check_index.o
	g++ -o check_index.app check_index.o
check_index.o : check_index.cpp

.PHONY : clean
clean :
	-rm *.o
	-rm *.app
install :
	./build_human_lib.app

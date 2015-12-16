# for sequence searching program
all : build_lib.app
build_lib.app : build_lib.o
	g++ -o build_lib.app build_lib.o
build_lib.o : build_lib.cpp settings.h
.PHONY : clean
clean :
	-rm *.o
	-rm *.app
install :
	./build_lib.app

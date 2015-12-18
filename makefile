# for sequence searching program
all : build_human_lib.app build_influenza_lib.app

# influenza
build_influenza_lib.app : build_influenza_lib.o
	g++ -o build_influenza_lib.app build_influenza_lib.o
build_influenza_lib.o : build_influenza_lib.cpp settings.h

# human
build_human_lib.app : build_human_lib.o
	g++ -o build_human_lib.app build_human_lib.o
build_human_lib.o : build_human_lib.cpp settings.h

# virus
build_virus_lib.app : build_virus_lib.o
	g++ -o build_virus_lib.app build_virus_lib.o
build_virus_lib.o : build_virus_lib.cpp settings.h

# prokaryote
build_prokaryote_lib.app : build_prokaryote_lib.o
	g++ -o build_prokaryote_lib.app build_prokaryote_lib.o
build_prokaryote_lib.o : build_prokaryote_lib.cpp settings.h

# check
check_sequence.app : check_sequence.o
	g++ -o check_sequence.app check_sequence.o
check_sequence.o : check_sequence.cpp

.PHONY : clean
clean :
	-rm *.o
	-rm *.app
run_app :
	./build_human_lib.app
	./build_influenza_lib.app
	./build_virus_lib.app
	./build_prokaryote_lib.app
human_lib :
	./build_human_lib.app
influenza_lib :
	./build_influenza_lib.app
virus_lib:
	./build_virus_lib.app
prokaryote_lib:
	./build_prokaryote_lib.app
check_sequence:
	./check_sequence.app ../../AI/RAW/LIB_VIRUS.fa

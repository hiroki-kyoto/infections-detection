# SOLUTION 2 FOR FAST-SEARCH IN GENETIC CODE LIB
**1.HOW TO RUN THIS APPLICATION**
	To run this application, you must have C11 compiler installed!

	change the header file [config.h]:

		const char ** P_RAW_DATA = "../../../AI/RAW/";

		to :

		const char ** P_RAW_DATA = "[PATH OF YOUR LOCAL DATA]";

	then:

		compile with makefile :

		> make all

		and run it with :

		> make run

	the output is in output.txt if you will never change the default settings.

**2.HOW IT WORKS?**
	i.  search for k-gram[k=10 in this application] patterns, and store their
	    statistical data into files, which is an inverted list.
	ii. scan through the test file to match with patterns and then math with
	    secondary patterns and then third, etc. Til no more pattern could be 
	    matched.
	iii.report DocID(Chromsome Name) to final list. It is the output expected.

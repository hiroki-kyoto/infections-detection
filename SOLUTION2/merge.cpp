// merge.cpp
#include <iostream>
#include <sstream>
#include "config.h"
#include "basic.h"

using namespace std;

int main(int argc, const char ** argv)
{
	// get parameter from stdin
	if(argc!=2)
	{
		cout<<"usage: ./merge.o [number of inverted-list files]\n";
		return 1;
	}

	// find all files and merge them into a big file
	stringstream ss;

	ss.str("");

	return 0;
}

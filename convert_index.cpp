// convert_index.cpp
// convert index data(N=9847x65536) into matrix 
// of 65536x9847
#include <iostream>
#include <fstream>
#include <string.h>
#include "settings.h"

using namespace std;

int main(int argc, const char ** argv)
{
	// load index database
	fstream reader;
	fstream writer;

	reader.open(IDX_BASE, ios::in);
	writer.open(TRN_IN, ios::out);

	

	return 0;
}


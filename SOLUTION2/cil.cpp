// construct inverted list for Genetic Library
// 2 files: ONE FOR POSITION IN CURRENT FILE LIST
// ANOTHER FOR POSITION IN WHOLE LIBRARY
#include <iostream>
#include <fstream>
#include <cstring>
#include "config.h"

using namespace std;

const int FILE_NAME_LEN = 256;
const int CHRM_NAME_LEN = 256;

// declation of functions
inline void loadName(char * name, fstream & fs);

int main(int argc, const char ** argv)
{
	// files to read and write
	fstream fin;
	fstream fout;
	
	// data path configuration
	char fname[FILE_NAME_LEN]; // file name
	char cname[CHRM_NAME_LEN]; // chromsome name

	memcpy(fname, P_RAW_DATA, strlen(P_RAW_DATA)+1);
	memcpy(fname + strlen(fname), \
		F_HUMAN, strlen(F_HUMAN) + 1);
	// show the file name
	cout<<fname<<endl;
	fin.open(fname, ios::in);
	loadName(cname, fin);
	cout<<cname<<endl;
	fin.close();

	return 0;
}

inline void loadName(char * name, fstream & fs)
{
	char ch = fs.get();
	int i = 0;
	while(ch!=EOF&&ch!='\n')
	{
		name[i++] = ch;
		ch = fs.get();
	}
	name[i] = 0;
}


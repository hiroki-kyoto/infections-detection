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
inline bool loadName(char * name, fstream & fs);

int main(int argc, const char ** argv)
{
	// files to read and write
	fstream fin;
	fstream fout;
	
	// data path configuration
	char fname[FILE_NAME_LEN]; // file name
	char cname[CHRM_NAME_LEN]; // chromsome name

	// open human genetic code file to read
	memcpy(fname, P_RAW_DATA, strlen(P_RAW_DATA)+1);
	memcpy(fname + strlen(fname), \
		F_HUMAN, strlen(F_HUMAN) + 1);
	cout<<"human: "<<fname<<endl;
	fin.open(fname, ios::in);
	
	// open namelist file to write
	memcpy(fname,P_OUTPUT, strlen(P_OUTPUT)+1);
	memcpy(fname + strlen(fname), \
		F_NAME_LIST, strlen(F_NAME_LIST) + 1);
	cout<<"name list: "<<fname<<endl;
	fout.open(fname, ios::out);
	
	// process human chromsome lib
	if(loadName(cname, fin))
	{
		// store its chromsome name
		fout<<cname<<endl;
		// process genetic code
			
	}
	fin.close();
	fout.close();

	return 0;
}

inline bool loadName(char * name, fstream & fs)
{
	char ch = fs.get();
	int i = 0;
	while(ch!='\n')
	{
		if(ch==EOF)
			return false;
		name[i++] = ch;
		ch = fs.get();
	}
	name[i] = 0;
	return true;
}


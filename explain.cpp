// explain.cpp
// explain the result
#include <iostream>
#include <fstream>
#include "settings.h"

using namespace std;

int main(int argc, const char ** argv)
{
	// get file to explain
	if(argc<2)
	{
		cout<<"err: too few arguments!"
			<<endl;
		return 1;
	}

	const char * file = argv[1];

	ifstream reader(file);
	
	// get indexes of nonzero elements 
	int ids[MAJOR_SIZE];
	int length = 0;
	
	double weit;

	for(int i=0; i<SPECIES_NUMBER; i++)
	{
		reader>>weit;
		if(weit>0)
		{
			ids[length] = i;
			length ++;
		}
	}
	
	reader.close();

	// load the name list into memory
	char species[256];
	char ch = 0;	
	int reads = 0;
	int index = 0;
	
	reader.open("NOT_BASE.nt");
	ch = reader.get();
	
	int cur = 0;
	
	while(ch!=EOF)
	{
		if(cur>=length)
			break;
		if(ch=='\n')
		{
			species[reads] = '\0';

			if(ids[cur]==index)
			{
				cout<<species<<endl;
				cur ++;
			}
			
			index ++;
			reads = 0;
			// debug
			//cout<<species<<endl;
		}
		else
		{
			species[reads] = ch;
			reads ++;
		}
		ch = reader.get();
	}

	reader.close();

	return 0;
}

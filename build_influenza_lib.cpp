// build_influenza_lib.cpp
#include <iostream>
#include <fstream>
#include <string.h>
#include "settings.h"

using namespace std;

int main(int argc, const char ** argv)
{
	// check environment
	if(sizeof(int)<4)
	{
		cout<<"err: [int] type has to be 4 byte!";
		cout<<endl;
		cout<<"[Incompatible runtime environment]";
		cout<<endl;
	}
	cout<<">>>BUILDING GENOME LIBRARY<<<"<<endl;
	/* load raw data from local path*/
	// first, load settings
	ifstream in(RAW_DATA_PATH);
	char raw_data[100];
	in>>raw_data;
	cout<<"RAW DATA PATH="<<raw_data<<endl;
	in.close();
	cout<<">>>PROGRAM SETTINGS LOADED<<<"<<endl;
	// then read human lib
	char lib_influenza[100];
	memset(lib_influenza, 0, sizeof(lib_influenza));
	// path of influenza path
	if(strlen(raw_data) + 
		strlen(LIB_INFLUENZA) + 1 > 
		sizeof(lib_influenza))
	{
		cout<<"error: file path too long!"<<endl;
		return 2;
	}
	memcpy(lib_influenza, raw_data, strlen(raw_data));
	memcpy(lib_influenza + strlen(lib_influenza),
		LIB_INFLUENZA, strlen(LIB_INFLUENZA));
	cout<<"LIB_INFLUENZA="<<lib_influenza<<endl;
	cout<<">>>LIBS PATH SOLVED<<<"<<endl;
	/* LOAD DATA FROM LIB */
	// raw data of human	
	in.open(lib_influenza);
	// setting output header stream and index stream
	ofstream index_stream;
	ofstream title_stream;
	index_stream.open(IDX_BASE, ios::app);
	title_stream.open(NOT_BASE, ios::app);
	
	char ch;
	char species[100]; // species name
	char card[CARD_SIZE];
	int reads = 0;
	int mode = 0; // MUST BE 0 AS INITIAL VALUE
	unsigned int index = 0;
	// allocation of bars [histogram analysis]
	unsigned int dim = 1;
	dim <<= (CARD_SIZE*2);
	cout<<"try to allocate memory for map: ";
	cout<<(sizeof(unsigned long long))*dim
		<<" Bytes"<<endl;
	unsigned long long * bars = 
		new unsigned long long[dim];
	// check if allocating is successful or not
	if(!bars)
	{
		cout<<"err: failed to allocate memory";
		cout<<endl;
		return -1;
	}
	else
	{
		// initialize bars
		memset(bars, 0, 
			dim*sizeof(unsigned long long));
	}
	// mode=0 means title, mode=1 means body
	ch = in.get();
	while(ch!=EOF)
	{
		// CASE CONVERT
		if(ch>='a'&&ch<='z')
			ch -= ('a'-'A');
		// FASTA Format
		if(ch=='>')
		{
			// check if exists any unsaved index data
			if(mode==1)
			{
				// save last species index data and reset
				for(unsigned int i=0; i<dim; i++)
				{
					index_stream<<bars[i]<<" ";
					bars[i] = 0;
				}
			}
			// switch to title mode
			mode = 0;
			reads = 0;
		}
		else
		{
			if(!mode)
			{
				if(ch=='\n')
				{
					species[reads] = '\0';
					// write name of species to notation file
					title_stream<<species<<endl;
					cout<<species<<endl;
					// switch to body mode
					mode = 1;
					reads = 0;
				}
				else
				{
					species[reads] = ch;
					reads ++;
				}
			}
			else
			{
				// ignore concat-sign of genome
				if(ch=='\n')
				{
					// ignore it
				} // else if it is {A,C,G,T,N}
				else if(ch==N)
					reads = 0;
				else
				{
					reads ++;
					if(reads == CARD_SIZE)
					{
						// do stats
						card[reads-1] = ch;
						index = map(card);
						bars[index] ++;
						// shift left
						memcpy(card, card+1, 
							CARD_SIZE-1);
						reads --;
					}
					else
						card[reads-1] = ch;
				}
			}
		}
		// read in next char
		ch = in.get();
	}
	// save the last species index data
	for(unsigned int i=0; i<dim; i++)
		index_stream<<bars[i]<<" ";
	// close reader
	in.close();
	index_stream.close();
	title_stream.close();
	cout<<">>>INFLUENZA LIB CONSTRUCTED<<<"<<endl;
	// never forget to recycle memory
	delete[] bars;
	cout<<"memory of bars recycled"<<endl;
	return 0;
}

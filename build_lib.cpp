#include <iostream>
#include <fstream>
#include <string.h>
#include "settings.h"

using namespace std;

int main(int argc, const char ** argv)
{
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
	char lib_human[100];
	char lib_influenza[100];
	char lib_prokaryote[100];
	char lib_virus[100];
	memset(lib_human, 0, sizeof(lib_human));
	memset(lib_influenza, 0, sizeof(lib_influenza));
	memset(lib_prokaryote, 0, sizeof(lib_prokaryote));
	memset(lib_virus, 0, sizeof(lib_virus));
	// concat path of human lib
	if(strlen(raw_data) + 
		strlen(LIB_HUMAN) + 1 > 
		sizeof(lib_human))
	{
		cout<<"error: file path too long!"<<endl;
		return 1;
	}
	memcpy(lib_human, raw_data, strlen(raw_data));
	memcpy(lib_human + strlen(lib_human),
		LIB_HUMAN, strlen(LIB_HUMAN));
	cout<<"LIB_HUMAN="<<lib_human<<endl;
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
	// path of prokaryote lib
	if(strlen(raw_data) + 
		strlen(LIB_PROKARYOTE) + 1 > 
		sizeof(lib_prokaryote))
	{
		cout<<"error: file path too long!"<<endl;
		return 3;
	}
	memcpy(lib_prokaryote, raw_data, 
		strlen(raw_data));
	memcpy(lib_prokaryote + strlen(lib_prokaryote),
		LIB_PROKARYOTE, strlen(LIB_PROKARYOTE));
	cout<<"LIB_PROKARYOTE="<<lib_prokaryote<<endl;
	// path of virus lib
	if(strlen(raw_data) + 
		strlen(LIB_VIRUS) + 1 > 
		sizeof(lib_virus))
	{
		cout<<"error: file path too long!"<<endl;
		return 4;
	}
	memcpy(lib_virus, raw_data, strlen(raw_data));
	memcpy(lib_virus + strlen(lib_virus),
		LIB_VIRUS, strlen(LIB_VIRUS));
	cout<<"LIB_VIRUS="<<lib_virus<<endl;
	cout<<">>>LIBS PATH SOLVED<<<"<<endl;
	/* LOAD DATA FROM LIB */
	// raw data of human	
	in.open(lib_human, ios::binary);
	char ch;
	char chromsome[100]; // chromsome name
	char card[CARD_SIZE];
	int reads = 0;
	int mode = 0;
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
	while(ch!=EOF)
	{
		// CASE CONVERT
		if(ch>='a'&&ch<='z')
			ch -= ('a'-'A');
		// FASTA Format
		if(ch=='>')
		{
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
					chromsome[reads] = '\0';
					// here forms a new strip of DNA
					cout<<chromsome<<endl;
					// switch to body mode
					mode = 1;
					reads = 0;
				}
				else
				{
					chromsome[reads] = ch;
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
	in.close();
	cout<<">>>HUMAN LIB INDEXING FINISHED"<<endl;
	// now write index to disk
	// check environment
	if(sizeof(int)!<4)
	{
		cout<<"err: [int] type has to be 4 byte!";
		cout<<endl;
		cout<<"[Incompatible runtime environment]";
		cout<<endl;
	}
	ofstream out;
	out.open(IDX_HUMAN, ios);
	for(unsigned int i=0; i<dim; i++)
		out.put(bars[i]);
	out.close();
	cout<<">>>HUMAN LIB CONSTRUCTED<<<"<<endl;

	// never forget to recycle memory
	delete[] bars;
	cout<<"memory of bars recycled"<<endl;
	return 0;
}

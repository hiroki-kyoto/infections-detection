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
	in.open(lib_human);
	char ch;
	char card[CARD_SZE];
	while(!in.eof())
	{
		in>>ch;
		
	}
	in.close();

	return 0;
}

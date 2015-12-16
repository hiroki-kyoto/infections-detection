// settings.h
#include <iostream>
// RAW DATA FILE PATH
const char * RAW_DATA_PATH = "raw_data_path.txt";
const char * LIB_HUMAN = "LIB_HUMAN.fa";
const char * LIB_INFLUENZA = "LIB_INFLUENZA.fa";
const char * LIB_PROKARYOTE = "LIB_PROKARYOTE.fa";
const char * LIB_VIRUS = "LIB_VIRUS.fa";

// INDEX DATA FILE PATH
const char * IDX_HUMAN = "IDX_HUMAN.dx";
const char * IDX_INFLUENZA = "IDX_INFLUENZA.dx";
const char * IDX_PROKARYOTE = "IDX_PROKARYOTE.dx";
const char * IDX_VIRUS = "IDX_VIRUS.dx";

// CARD GENERATING CONFIURATION
const int CARD_SIZE = 8;
const char A = 'A';
const char C = 'C';
const char G = 'G';
const char T = 'T';
const char N = 'N';
// lowercase2uppercase: if ch <= T

// HASH MAP
inline unsigned int map(char* card)
{
	unsigned int id = 0;
	for(int i=0; i<CARD_SIZE; i++)
	{
		id <<= 2;
		if(card[i]==A)
			id += 0; // 00
		else if(card[i]==C)
			id += 1; // 01
		else if(card[i]==G)
			id += 2; // 10
		else if(card[i]==T)
			id += 3; // 11
		else
			std::cout<<"err: encoding card\n";
	}
	return id;
}

inline void map(char* card, unsigned int id)
{
	for(int i=CARD_SIZE-1; i>=0; i--)
	{
		int code = id % 4;
		id >> 2;
		if(code==0)
			card[i] = A;
		else if(code==1)
			card[i] = C;
		else if(code==2)
			card[i] = G;
		else if(code==3)
			card[i] = T;
		else
			std::cout<<"err: decoding index\n";
	}
}


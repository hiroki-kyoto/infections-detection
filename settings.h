// settings.h
#include <iostream>
// RAW DATA FILE PATH
const char * RAW_DATA_PATH = "raw_data_path.txt";
const char * LIB_HUMAN = "LIB_HUMAN.fa";
const char * LIB_INFLUENZA = "LIB_INFLUENZA.fa";
const char * LIB_PROKARYOTE = "LIB_PROKARYOTE.fa";
const char * LIB_VIRUS = "LIB_VIRUS.fa";

// RAW DATA OF TEST SAMPLES
const char * TST_CASE_A1 = "TEST_A_1.fq";
const char * TST_CASE_A2 = "TEST_A_2.fq";
const char * TST_CASE_B1 = "TEST_B_1.fq";
const char * TST_CASE_B2 = "TEST_B_2.fq";
const char * TST_CASE_C = "TEST_C.fq";

// SETTING FOR READING TEST CASE
const int TST_CASE_LINE = 1024;

// RAW DATA OF CASE TO BE RESOLVED
const char * RSL_CASE_D = "SOLVE_D.fq";
const char * RSL_CASE_E = "SOLVE_E.fq";

// NOTATION OF INDEX
const char * NOT_BASE = "NOT_BASE.nt";

// INDEX FILE
const char * IDX_BASE = "IDX_BASE.dx";
const char * IDX_TEST_A = "IDX_TEST_A.dx";
const char * IDX_TEST_B = "IDX_TEST_B.dx";
const char * IDX_TEST_C = "IDX_TEST_C.dx";
const char * IDX_RSLV_D = "IDX_RSLV_D.dx";
const char * IDX_RSLV_E = "IDX_RSLV_E.dx";

// TRAINING DATA
const char * TRN_IN = "TRN_IN.dt";
const char * TRN_OUT = "TRN_OUT.dt";
const int SPECIES_NUMBER = 9847;
// ABOVE GOT FROM NOTATION FIEL

// TRAINING SETTINGS
const int MAX_REPEAT = 500;
const double MAX_ERROR = 1e-3;
const double LEARNING_RATE = 1.0;
const int MAJOR_SIZE = 3;

// CARD GENERATING CONFIURATION
const int CARD_SIZE = 8;
const char A = 'A';
const char C = 'C';
const char G = 'G';
const char T = 'T';
const char N = 'N';

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
		{
			std::cout<<"err: encoding card\n";
			std::cout<<"cause: "<<card[i]<<std::endl;
		}
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
	}
}


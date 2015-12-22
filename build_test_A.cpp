#include <iostream>
#include <fstream>
#include <string.h>
#include "settings.h"

using namespace std;

// define my desired getline function
int _getline_(ifstream & in, char * line)
{
	// the delimeter is ENTER sign
	char ch;
	ch = in.get();
	int i = 0;
	while(ch!='\n'&&i<TST_CASE_LINE)
	{
		line[i] = ch;
		ch = in.get();
		i++;
	}
	return i;
}


int main(int argc, const char ** argv)
{
	cout<<">>>INDEXING TEST DATASET<<<"<<endl;
	/* load raw data from local path*/
	// first, load settings
	ifstream in(RAW_DATA_PATH);
	char raw_data[100];
	in>>raw_data;
	cout<<"RAW DATA PATH="<<raw_data<<endl;
	in.close();
	cout<<">>>PROGRAM SETTINGS LOADED<<<"<<endl;

	char test_A1[100];
	char test_A2[100];
	memset(test_A1, 0, sizeof(test_A1));
	memset(test_A2, 0, sizeof(test_A2));
	
	if(strlen(raw_data) + 
		strlen(TST_CASE_A1) + 1 > 
		sizeof(test_A1))
	{
		cout<<"error: file path too long!"<<endl;
		return 1;
	}

	memcpy(test_A1, raw_data, strlen(raw_data));
	memcpy(test_A1 + strlen(test_A1),
		TST_CASE_A1, strlen(TST_CASE_A1));
	cout<<"TST_CASE_A1="<<test_A1<<endl;
	
	memcpy(test_A2, raw_data, strlen(raw_data));
	memcpy(test_A2 + strlen(test_A2),
		TST_CASE_A2, strlen(TST_CASE_A2));
	cout<<"TST_CASE_A2="<<test_A2<<endl;

	cout<<">>>TEST DATASET PATH SOLVED<<<"<<endl;
	
	/* LOAD DATA FROM TEST CASE */
	// FROM A1
	in.open(test_A1);
	// FIND OUT HOW LONG THE FILE IS
	in.seekg(0, ios::end);
	streampos file_size = in.tellg();
	cout<<"A1: FILE SIZE = "<<file_size<<endl;
	in.seekg(0, ios::beg);
	// flag to show progress
	unsigned long long reads = 0;// piece number

	char code[TST_CASE_LINE]; // 1024 as max
	char score[TST_CASE_LINE];
	int len = 0;
	int pos = 0;
	char card[CARD_SIZE]; // 8 as a gram
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

	reads = 0;
	while(1)
	{
		// read a peice of genetic code and score
		len = _getline_(in, code);
		reads += len + 1;
		
		if(len<1) // no more lines
		{
			cout<<"CASE A1 IS OVER!"<<endl;
			break;
		}
		
		len = _getline_(in, code);
		reads += len + 1;
		pos = 0;
		
		int score_size = _getline_(in, score);
		reads += score_size + 1;

		score_size = _getline_(in, score);
		reads += score_size + 1;

		if(len!=score_size)
		{
			cout<<"err: sequence length "
				<<"does not match with "
				<<"score length!"<<endl;
			break;
		}

		//begin to process sequence of gene
		// transform the genetic code
		for(int i=0; i<len; i++)
		{
			if(code[i]<='z'&&code[i]>='a')
				code[i] -= ('a'-'A');
			// now apply filters
			if(code[i]==A||code[i]==C||
				code[i]==G||code[i]==T)
			{
				if(((int)score[i])>=10) // over 0.90
				{
					pos ++;
					if(pos == CARD_SIZE)
					{
						// do stats
						card[pos-1] = code[i];
						index = map(card);
						bars[index] ++;
						// shift left
						memcpy(card, card+1, 
							CARD_SIZE-1);
						pos --;
					}
					else
						card[pos-1] = code[i];
				}
				else
					pos = 0;
			}
			else
				pos = 0;
		}

		// show progress
		cout<<"A1 : "<<reads<<" / "
			<<file_size<<endl;
	}

	in.close();
	in.open(test_A2);
	// FIND OUT HOW LONG THE FILE IS
	in.seekg(0, ios::end);
	file_size = in.tellg();
	in.seekg(0, ios::beg);

	// repeat with A2
	reads = 0;
	while(1)
	{
		// read a peice of genetic code and score
		len = _getline_(in, code);
		reads += len + 1;
		
		if(len<1) // no more lines
		{
			cout<<"CASE A1 IS OVER!"<<endl;
			break;
		}
		
		len = _getline_(in, code);
		reads += len + 1;
		pos = 0;
		
		int score_size = _getline_(in, score);
		reads += score_size + 1;

		score_size = _getline_(in, score);
		reads += score_size + 1;

		if(len!=score_size)
		{
			cout<<"err: sequence length "
				<<"does not match with "
				<<"score length!"<<endl;
			break;
		}

		//begin to process sequence of gene
		// transform the genetic code
		for(int i=0; i<len; i++)
		{
			if(code[i]<='z'&&code[i]>='a')
				code[i] -= ('a'-'A');
			// now apply filters
			if(code[i]==A||code[i]==C||
				code[i]==G||code[i]==T)
			{
				if(((int)score[i])>=10) // over 0.90
				{
					pos ++;
					if(pos == CARD_SIZE)
					{
						// do stats
						card[pos-1] = code[i];
						index = map(card);
						bars[index] ++;
						// shift left
						memcpy(card, card+1, 
							CARD_SIZE-1);
						pos --;
					}
					else
						card[pos-1] = code[i];
				}
				else
					pos = 0;
			}
			else
				pos = 0;
		}

		// show progress
		cout<<"A2 : "<<reads<<" / "
			<<file_size<<endl;
	}	
	cout<<">>>TEST CASE A INDEXING FINISHED"<<endl;
	// now write index to disk
	// check environment
	if(sizeof(int)<4)
	{
		cout<<"err: [int] type has to be 4 byte!";
		cout<<endl;
		cout<<"[Incompatible runtime environment]";
		cout<<endl;
	}

	// close input stream
	in.close();

	// tranform index data into weight vector
	double sum = 0;
	int com = dim >> 3;
	double * weit = new double[com];

	// check if allocation is successful
	if(!weit)
	{
		cout<<"err: allocation for [weit] failed!";
		cout<<endl;
		return -1;
	}

	for(int i=0; i<com; i++)
	{
		for(int j=0; j<8; j++)
			weit[i] += bars[8*i+j];
		sum +=  weit[i];
	}
	for(int i=0; i<com; i++)
		weit[i] /= sum;

	// write weight vector into case A output
	ofstream out;
	out.open(IDX_TEST_A);
	for(unsigned int i=0; i<com; i++)
		out<<weit[i]<<" ";
	out.close();

	cout<<">>>TEST A INDEX CONSTRUCTED<<<"<<endl;
	// never forget to recycle memory
	delete [] bars;
	delete [] weit;
	cout<<"memory of bars recycled"<<endl;
	return 0;
}

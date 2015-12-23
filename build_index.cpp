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

	while(ch!='\n'&&i<TST_CASE_LINE&&ch!=EOF)
	{
		line[i] = ch;
		ch = in.get();
		i++;
	}
	return i;
}


int main(int argc, const char ** argv)
{
	
	// GET STREAM IN AND OUT PATH
	if(argc<3)
	{
		cout<<"err: unacceptable arguments"<<endl;
		cout<<"tip: ./build_index.app"
			<<" [input file] [output file]";
	}

	const char * src = argv[1];
	const char * dst = argv[2];

	cout<<"PLEASE CONFIRM YOUR INPUT?[Y/N]"<<endl;
	cout<<"GENETIC CODE FILE TO READ: "<<src<<endl;
	cout<<"WEIGHT VECTOR FILE TO WRITE: "<<dst<<endl;
	char user_input;
	cin>>user_input;
	if(user_input>='a'&&user_input<='z')
		user_input -= ('a'-'A');
	if(user_input!='Y')
		return 1;
	
	// LOAD DATA FROM GENETIC CODE FILE
	ifstream in(src);
	// FIND OUT HOW LONG THE FILE IS
	in.seekg(0, ios::end);
	streampos file_size = in.tellg();
	cout<<"SOURCE: FILE SIZE = "<<file_size<<endl;
	in.seekg(0, ios::beg);
	// flag to show progress
	unsigned long long reads = 0;// bytes read already
	int tick = 0;

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
			cout<<"READING OVER!"<<endl;
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
		tick++;
		if(tick==10000)
		{
			tick = 0;
			double progress = file_size;
			progress = reads/progress*100;
			cout<<"PROCESSING : "<<progress<<" % "<<endl;
		}
	}

	in.close();
	cout<<">>>INDEXING FINISHED"<<endl;
	// now write index to disk
	// check environment
	if(sizeof(int)<4)
	{
		cout<<"err: [int] type has to be 4 byte!";
		cout<<endl;
		cout<<"[Incompatible runtime environment]";
		cout<<endl;
	}

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
	else
	{
		// initialize
		memset(weit, 0, sizeof(double)*com);
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
	out.open(dst);
	for(unsigned int i=0; i<com; i++)
		out<<weit[i]<<" ";
	out.close();

	cout<<">>>WEIGHT VECTOR WRITTEN FINISHED!<<<"<<endl;
	// never forget to recycle memory
	delete [] bars;
	delete [] weit;
	cout<<"memory of bars recycled"<<endl;
	return 0;
}

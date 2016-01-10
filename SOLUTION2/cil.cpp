// construct inverted list for Genetic Library
// 2 files: ONE FOR POSITION IN CURRENT FILE LIST
// ANOTHER FOR POSITION IN WHOLE LIBRARY
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include "config.h"
#include "basic.h"

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
	fstream flst;
	
	// data path configuration
	char fname[FILE_NAME_LEN]; // file name
	char cname[CHRM_NAME_LEN]; // chromsome name

	// open human genetic code file to read
	memcpy(fname, P_RAW, strlen(P_RAW) + 1);
	memcpy(fname + strlen(fname), \
		F_HUMAN, strlen(F_HUMAN) + 1);
	cout<<"human: "<<fname<<endl;
	fin.open(fname, ios::in);
	
	// open namelist file to write
	memcpy(fname, P_OUT, strlen(P_OUT) + 1);
	memcpy(fname + strlen(fname), \
		F_NAME_LIST, strlen(F_NAME_LIST) + 1);
	cout<<"name list: "<<fname<<endl;
	fout.open(fname, ios::out);

	// close last IL file and create a new one to write into.
	ss.str(""); // make it empty
	ss<<"INVERTED_LIST_"file_id<<".txt";
	const char * f_list =  ss.str().c_str();
	memcpy(fname, P_OUT, strlen(P_OUT) + 1);
	memcpy(fname + strlen(fname), \
			f_list, strlen(f_list) + 1);
	cout<<"writing inverted list into file: "<<fname<<endl;
	flst.close();
	flst.open(fname, ios::out);
	file_id ++;
	
	// process human chromsome lib
	char card[CARD_SIZE];
	char next[CARD_SIZE];
	int csize, nsize;

	// inverted list in cache
	list * lst = new list;
	int item_counter = 0;
	int doc_counter = 0;
	int id, nid;
	Lini(lst);

	// inverted list file
	stringstream ss;
	int file_id = 0;
	
	bool _continue_ = true;
	while(loadName(cname, fin) && _continue_)
	{
		// store its chromsome name
		fout<<cname<<endl;
		// process genetic code
		while((ch=fin.get())!='\n')
		{
			if(ch==EOF)
			{
				cout<<"Error: ";
				cout<<"FASTA bad format!";
				_continue_ = false;
				break;
			}
			if(ch!=A&&ch!=C&&ch!=G&&ch!=T)
			{
				csize = 0;
				nsize = 0;
			}
			else if(csize<CARD_SIZE)
			{
				if(nsize<CARD_SIZE)
					next[nsize++] = ch;
				else
				{
					card[csize++] = next[0];
					memcpy( next,
						next + 1,
						CARD_SIZE - 1
						);
					next[nsize++] = ch;
				}
			}
			else
			{
				// process two card
				id = encode(card);
				nid = encode(next);
				Ladd(l, id, doc_counter, nid);
				item_counter ++;
			}
		}
	}
	
	// finalize
	Lempty(lst);
	delete lst;

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


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
	// inverted list in cache
	int n = 1<<20;
	list * lst = new list[n];

	if(!lst)
	{
		cout<<"memory allocation failed!"<<endl;
		return 1; // return error!
	}

	for(int i=0; i<n; i++)
		Lini(lst+i);

	// files to read and write
	fstream fin;
	fstream fout;
	fstream flst;
	fstream fpos;
	
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

	// process human chromsome lib
	char card[CARD_SIZE];
	char next[CARD_SIZE];
	int csize, nsize;
	int item_counter = 0;
	int doc_counter = 0;
	int id, nid;

	// inverted list file
	stringstream ss;
	int file_id = 0;
	
	bool _continue_ = true;
	while(loadName(cname, fin) && _continue_)
	{
		// store its chromsome name
		fout<<cname<<endl;
		doc_counter ++;
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
				Ladd(lst+id, doc_counter, nid);
				item_counter ++;

				// if it reached memory limit, save ilist to files
				if(item_counter>IL_CACHE_SIZE)
				{
					// close last IL file and create a new one to write into.
					ss.str(""); // make it empty
					ss<<"IL_"<<file_id<<".txt";
					const char * f_list =  ss.str().c_str();
					memcpy(fname, P_OUT, strlen(P_OUT) + 1);
					memcpy(fname+strlen(fname), f_list, strlen(f_list)+1);
					cout<<"writing inverted list into file: "<<fname<<endl;
					flst.open(fname, ios::out|ios::binary);

					ss.str("");
					ss<<"POS_"<<file_id<<".txt";
					const char * f_pos = ss.str().c_str();
					memcpy(fname, P_OUT, strlen(P_OUT)+1);
					memcpy(fname+strlen(fname), f_pos, strlen(f_pos)+1);
					cout<<"writing position information into file: "<<fname<<endl;
					fpos.open(fname, ios::out|ios::binary);

					file_id ++;

					// clear all items in memory and save into local disk
					int _doc, _next;

					for(int i=0; i<n; i++)
					{
						fpos.write(lst[i].size);
						while(lst[i].size>0)
						{
							Lpop(lst+i, _doc, _next);
							flst.write(_doc);
							flst.write(_next);
						}
					}

					fpos.close();
					flst.close();
					item_counter = 0;
				}
			}
		}
	}
	
	// finalize
	Lempty(lst);
	delete lst;

	fin.close();
	fout.close();
	fpos.close();
	flst.close();

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


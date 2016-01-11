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
		F_HUM, strlen(F_HUM) + 1);
	cout<<"human: "<<fname<<endl;
	fin.open(fname, ios::in);
	
	// open namelist file to write
	memcpy(fname, P_OUT, strlen(P_OUT) + 1);
	memcpy(fname + strlen(fname), \
		F_NAME_LIST, strlen(F_NAME_LIST) + 1);
	cout<<"name list: "<<fname<<endl;
	fout.open(fname, ios::out);

	// process human chromsome lib
	char band[CARD_SIZE*2]; // current + next
	int band_size = 0;
	int item_counter = 0;
	int doc_counter = 0;
	int id, next;

	// inverted list file
	int mode = 0; // data set index
	stringstream ss;
	int file_id = 0;
	bool _continue_ = true;
	char ch; // to read

_CST_IL_:
	_continue_ = true;
	fin.get(); // drop ">"
	while(_continue_)
	{
		if(!loadName(cname, fin))
			break;
		// store its chromsome name
		fout<<cname<<endl;
		// process genetic code
		band_size = 0;
		
		while((ch=fin.get())!='>')
		{
			if(ch==EOF)
			{
				_continue_ = false;
				break;
			}
			if(ch=='\n')
				continue;
			if(ch!=A&&ch!=C&&ch!=G&&ch!=T)
				band_size = 0;
			else if(band_size<CARD_SIZE*2)
				band[band_size++] = ch;
			else
			{
				// process two card
				encode(band, id);
				encode(band+CARD_SIZE, next);

				// update band
				move_left(band, sizeof(band), 1, ch);

				Ladd(lst+id, doc_counter, next);
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
						fpos.write((char*)&(lst[i].size), sizeof(int));
						while(lst[i].size>0)
						{
							Lpop(lst+i, _doc, _next);
							flst.write((char*)&_doc, sizeof(int));
							flst.write((char*)&_next, sizeof(int));
						}
					}

					fpos.close();
					flst.close();
					item_counter = 0;
				}
			}
		}

		// write the last few cards
		for(; band_size>=CARD_SIZE; band_size--)
		{
			encode(band, id);
			if(band_size==2*CARD_SIZE)
				encode(band+CARD_SIZE, next);
			else
				next = END;
			Ladd(lst+id, doc_counter, next);
			item_counter ++;
			move_left(band, sizeof(band), 1);
		}

		// document number auto-increment
		doc_counter ++;
	}

	// close filestream
	fin.close();
	mode ++;

	// open virus genetic code file to read
	if(mode==1)
	{
		memcpy(fname, P_RAW, strlen(P_RAW) + 1);
		memcpy(fname + strlen(fname), F_VIR, strlen(F_VIR) + 1);
		cout<<"virus: "<<fname<<endl;
		fin.open(fname, ios::in);
		goto _CST_IL_;
	}

	// open influenza genetic code file to read
	if(mode==2)
	{
		memcpy(fname, P_RAW, strlen(P_RAW) + 1);
		memcpy(fname + strlen(fname), F_INF, strlen(F_INF) + 1);
		cout<<"flu: "<<fname<<endl;
		fin.open(fname, ios::in);
		goto _CST_IL_;
	}

	// open all infectious genetic code file to read
	if(mode==3)
	{
		memcpy(fname, P_RAW, strlen(P_RAW) + 1);
		memcpy(fname + strlen(fname), F_ALL, strlen(F_ALL) + 1);
		cout<<"all: "<<fname<<endl;
		fin.open(fname, ios::in);
		goto _CST_IL_;
	}

	// deal with rest of inverted list
	ss.str("");
	ss<<"IL_"<<file_id<<".txt";
	const char * fl =  ss.str().c_str();
	memcpy(fname, P_OUT, strlen(P_OUT) + 1);
	memcpy(fname+strlen(fname), fl, strlen(fl)+1);
	cout<<"writing inverted list into file: "<<fname<<endl;
	flst.open(fname, ios::out|ios::binary);
	
	ss.str("");
	ss<<"POS_"<<file_id<<".txt";
	const char * fn = ss.str().c_str();
	memcpy(fname, P_OUT, strlen(P_OUT)+1);
	memcpy(fname+strlen(fname), fn, strlen(fn)+1);
	cout<<"writing position information into file: "<<fname<<endl;
	fpos.open(fname, ios::out|ios::binary);
	file_id ++;
	// clear all items in memory and save into local disk
	int _doc_, _next_;
	for(int i=0; i<n; i++)
	{
		fpos.write((char*)&(lst[i].size), sizeof(int));
		while(lst[i].size>0)
		{
			Lpop(lst+i, _doc_, _next_);
			flst.write((char*)&_doc_, sizeof(int));
			flst.write((char*)&_next_, sizeof(int));
		}
	}

	fpos.close();
	flst.close();
	item_counter = 0;
	
	// finalize
	fout.close();
	delete[] lst;

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


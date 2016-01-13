// merge.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include "config.h"
#include "basic.h"

using namespace std;

int main(int argc, const char ** argv)
{
	// check environment
	if(sizeof(streamoff)<8)
	{
		cout<<"Error: sizeof(streamoff)<8"<<endl;
		return 1;
	}
	if(sizeof(long long)<8)
	{
		cout<<"Error: sizeof(long long)<8"<<endl;
		return 1;
	}
	
	// get parameter from stdin
	if(argc!=2)
	{
		cout<<"usage: ./merge.app [number of inverted-list files]\n";
		return 1;
	}
	
	int fn = 0; // file number
	stringstream ss;
	ss<<argv[1];
	ss>>fn;
	cout<<"total files: "<<fn<<endl;
	
	// allocation for offset
	int n = 1<<20;
	int * offset = new int[n];
	int size = 0; // temp variable
	
	if(!offset)
	{
		cout<<"error: allocation failed!"<<endl;
		return 1;
	}
	
	// reset offset
	memset((char*)offset, 0, sizeof(int)*n);
	
	// merge offset file
	for(int i=0; i<fn; i++)
	{
		ss.str("");
		ss.clear();
		ss<<P_OUT<<"POS_"<<i<<".txt";
		fstream fpos;
		fpos.open(ss.str().c_str(), ios::binary|ios::in);
		
		for(int k=0; k<n; k++)
		{
			fpos.read((char*)&size, sizeof(size));
			offset[k] += size;
		}
		
		fpos.close();
	}
	
	// write them into offset file
	fstream foff;
	ss.str("");
	ss.clear();
	ss<<P_OUT<<F_OFF;
	cout<<"offset: "<<ss.str().c_str()<<endl;
	foff.open(ss.str().c_str(), ios::binary|ios::out);
	foff.write((char*)offset, sizeof(int)*n); // write offset information
	foff.close();
	
	// construct distance map
	long long * dist = new long long[n];
	if(!dist)
	{
		cout<<"error: allocation failed!"<<endl;
		return 1;
	}
	
	// the first offset is 0
	dist[0] = 0;
	
	for(int i=1; i<n; i++)
		dist[i] = dist[i-1] + offset[i-1];
	
	// reset offset for other use
	memset((char*)offset, 0, sizeof(int)*n);
	
	// open a file and try to write data in fixed position
	fstream fall;
	ss.str("");
	ss.clear();
	ss<<P_OUT<<F_LST;
	cout<<"inverted-list: "<<ss.str().c_str()<<endl;
	fall.open(ss.str().c_str(), ios::binary|ios::out);

	// merge offset file
	for(int i=0; i<fn; i++)
	{
		// position file for IL
		ss.str("");
		ss.clear();
		ss<<P_OUT<<"POS_"<<i<<".txt";
		fstream fpos;
		fpos.open(ss.str().c_str(), ios::binary|ios::in);
		
		// inverted-list file
		ss.str("");
		ss.clear();
		ss<<P_OUT<<"IL_"<<i<<".txt";
		fstream flst;
		flst.open(ss.str().c_str(), ios::binary|ios::in);
		
		for(int k=0; k<n; k++)
		{
			int size = 0;
			fpos.read((char*)&size, sizeof(size));
			// a gram is ([int][int])
			int * data = new int[2*size];
			flst.read((char*)data, 2*sizeof(int)*size);
			
			streamoff pos = (dist[k] + offset[k])*sizeof(int)*2;
			fall.seekp(pos);
			fall.write((char*)data, 2*sizeof(int)*size);
			
			offset[k] += size; // update offset by each row
			delete [] data;
		}
		
		fpos.close();
		flst.close();
	}
	
	fall.close();
	
	// finalize
	delete [] offset;
	delete [] dist;

	return 0;
}

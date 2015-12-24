// convert_index.cpp
// convert index data(N=9847x65536) into matrix 
// of 65536x9847
#include <iostream>
#include <fstream>
#include <string.h>
#include "settings.h"

using namespace std;

int main(int argc, const char ** argv)
{
	// dimension compresssing
	int dim = 1;
	dim <<= CARD_SIZE*2; // that's 65536
	int com = dim>>3; // dim/8
	
	// allocation of memory
	int * bars = new int[com];
	if(!bars)
	{
		cout<<"err: failed to allocate memory";
		cout<<endl;
		return 1;
	}
	memset(bars, 0, sizeof(int)*com);

	double ** mat = new double*[com];
	if(!mat)
	{
		cout<<"err: failed to allocate memory";
		cout<<endl;
		return 2;

	}
	
	for(int i=0; i<com; i++)
	{
		// feature vector shadow on species
		mat[i] = new double[SPECIES_NUMBER];
		if(!mat[i])
		{
			cout<<"err: failed to allocate memory";
			cout<<endl;
			return 3;
		}
		memset(mat[i], 0, 
			sizeof(double)*SPECIES_NUMBER);
	}

	long long sum = 0; // sum of each species
	int num = 0;

	// load index database
	fstream reader;
	fstream writer;

	reader.open(IDX_BASE, ios::in);
	writer.open(TRN_IN, ios::out);
	
	for(int species=0; species<SPECIES_NUMBER;
		species ++)
	{
		sum = 0;
		num = 0;
		// load data from file
		for(int i=0; i<com; i++)
		{
			bars[i] = 0;
			for(int j=0; j<8; j++)
			{
				reader>>num;
				bars[i] += num;
			}
			sum += bars[i];
		}
		
		// weight vector of this species
		for(int i=0; i<com; i++)
			mat[i][species] = 
				((double)bars[i])/((double)sum);
		cout<<"SPECIES-";
		cout<<species<<endl;
	}
	cout<<"PROCESS OF CONVERTING DONE!"<<endl;

	// write matrix into training dataset
	for(int i=0; i<com; i++)
		for(int j=0; j<SPECIES_NUMBER; j++)
			writer<<mat[i][j]<<" ";

	cout<<"MATRIX WRITING INTO DISK DONE!"<<endl;
	// close all streams
	reader.close();
	writer.close();
	cout<<"PROGRAM COMPLETE SUCCESSFUL!"<<endl;

	// recycle memory
	delete [] bars;
	for(int i=0; i<com; i++)
		delete [] mat[i];
	delete [] mat;

	return 0;
}


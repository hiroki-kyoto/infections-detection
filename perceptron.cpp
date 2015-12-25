// perceptron.cpp'
// 1.BUILD PERCEPTRON MODEL
// 2.TRAIN THE MODEL WITH TRN_IN.dt 
// 3.APPLY OUTPUT FEEDBACK TO MODEL
// 4.SAVE FINAL VECTOR OF WEIGHT
#include <iostream>
#include <string.h>
#include <fstream>
#include "settings.h"

using namespace std;

int main(int argc, const char ** argv)
{
	if(argc<3)
	{
		cout<<"err: Illegal Parameters!"
			<<endl;
		cout<<"tip: ./perceptron.app "
			<<"[INPUT FILE] [OUTPUT FILE]"
			<<endl;
			return 1;
	}

	const char * train_in = argv[1];
	const char * train_st = argv[2];
	// now read input vector of weight from file
	cout<<"PLEASE CONFIRM YOUR INPUT:[Y/N]?"
		<<endl;
	cout<<"TRAINING INPUT FILE: "
		<<train_in<<endl;
	cout<<"TRAINING FEEDBACK FILE: "
		<<train_st<<endl;
	char confirm;
	cin>>confirm;
	if(confirm != 'Y'&&confirm !='y')
	{
		// abortion of program running
		cout<<"YOU JUST CANCELLED PROGRAM..."
			<<endl;
		return 1;
	}
	
	// now build the model of perceptron
	ifstream reader(train_in);
	ofstream writer("TRN_OUT.dt");
	
	int dim = 1;
	dim <<= (CARD_SIZE*2);
	dim >>= 3; // 8192

	// allocation of memory
	double ** mat = new double*[dim];
	
	if(!mat)
	{
		cout<<"err: allocation failed!"
			<<endl;
		return 1;
	}

	for(int i=0; i<dim; i++)
	{
		mat[i] = new double[SPECIES_NUMBER];
		if(!mat[i])
		{
			cout<<"err: allocation failed!"
				<<endl;
			return 1;
		}

	}

	// load data into memory
	for(int i=0; i<dim; i++)
		for(int j=0; j<SPECIES_NUMBER; j++)
			reader>>mat[i][j];

	// allocation for feedback data
	double * feedback = new double[dim];
	if(!feedback)
	{
		cout<<"err: allocation failed!"
			<<endl;
		return 1;
	}

	// prepare the output feedback data
	reader.close();
	reader.open(train_st);
	
	for(int i=0; i<dim; i++)
		reader>>feedback[i];

	// clean up
	reader.close();

	// weight vector of perceptron
	double * weit = new double[SPECIES_NUMBER];
	
	if(!weit)
	{
		cout<<"err: allocation failed!"
			<<endl;
		return 1;
	}

	// initialize the arguments
	weit[0] = 1; // for human
	for(int i=1; i<SPECIES_NUMBER; i++)
		weit[i] = 0;
	
	// initial bias 
	double bias = 0.0;
	double error = 0.0;
	double output = 0.0;
	double weit_net = 0.0;

	int repeat = 0;
	int satisfied = 0;
	double major[MAJOR_SIZE];
	int mid[MAJOR_SIZE];
	double ex = 0;
	int exid = 0;

	while(repeat<MAX_REPEAT)
	{
		repeat ++;
		satisfied = 0;
		cout<<"TRAINING "<<repeat<<" TIMES."
			<<endl;	
		for(int i=0; i<dim; i++)
		{
			// forward computing
			output = 0;
			for(int j=0; j<SPECIES_NUMBER; j++)
				output += mat[i][j]*weit[j];
			
			//output += bias;
			error = feedback[i] - output;
			
			// backward computing
			if(error*error<MAX_ERROR*MAX_ERROR)
			{
				satisfied ++;
				continue;
			}
			
			// adjust weit of connections
			for(int k=0; k<MAJOR_SIZE; k++)
			{
				major[k] = -1;
				mid[k] = -1;
			}

			for(int j=0; j<SPECIES_NUMBER; j++)
			{
				weit[j] +=
					LEARNING_RATE*mat[i][j]*error;
				if(weit[j]<0)
					weit[j] = 1e-8;
				if(weit[j]>major[0])
				{
					major[0] = weit[j];
					mid[0] = j;
					for(int k=0; k<MAJOR_SIZE-1; k++)
					{
						if(major[k]>major[k+1])
						{
							// exchange
							ex = major[k+1];
							exid = mid[k+1];
							major[k+1] = major[k];
							mid[k+1] = mid[k];
							major[k] = ex;
							mid[k] = exid;
						}
						else
							break;
					}
				}
			}

			// unify
			weit_net = 0;
			for(int k=0; k<MAJOR_SIZE; k++)
				weit_net += major[k];
			memset(weit, 0, 
				sizeof(double)*SPECIES_NUMBER);
			for(int k=0; k<MAJOR_SIZE; k++)
				weit[mid[k]] = major[k]/weit_net;
		}

		// show current error
		cout<<"error: "<<error<<endl;
		cout<<"SATISFIED : "<<satisfied<<endl;

		if(satisfied==dim)
		{
			cout<<"SUCCEED!"<<endl;
			cout<<"FINAL ERROR: "<<error<<endl;
			break;
		}
	}

	// write final weit vector into file
	for(int i=0; i<SPECIES_NUMBER; i++)
	{
		if(weit[i]<1e-4)
			weit[i] = 0;
		writer<<weit[i]<<" ";
	}

	// tips for running this program
	cout<<"FINAL OUTPUT OF VECTOR OF WEIGHT"
		<<" IS SAVED IN FILE [TRN_OUT.dt]."
		<<endl;

	// finalizing
	writer.close();
	for(int i=0; i<dim; i++)
		delete[] mat[i];
	delete [] mat;
	delete [] feedback;
	delete [] weit;

	return 0;
}

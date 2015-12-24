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
	if(argc<4)
	{
		cout<<"err: Illegal Parameters!"
			<<endl;
		cout<<"tip: ./perceptron.app "
			<<"[INPUT FILE] [OUTPUT FILE]"
			<<endl;
			return 1;
	}

	const char * input = argv[1];
	const char * output = argv[2];
	// now read input vector of weight from file
	cout<<"PLEASE CONFIRM YOUR INPUT:[Y/N]?"
		<<endl;
	cout<<"TRAINING INPUT FILE: "
		<<input<<endl;
	cout<<"TRAINING OUTPUT FILE: "
		<<output<<endl;
	char confirm;
	if(confirm != 'Y'&&confirm=='y')
	{
		// abortion of program running
		cout<<"YOU JUST CANCEL PROGRAM..."
			<<endl;
		return 1;
	}
	
	// now build the model of perceptron
	ifstream reader(input);
	ofstream writer(output);
	
	int dim = 1;
	dim <<= (CARD_SIZE*2);
	dim >>= 3; // 8192

	// allocation of memory
	double * mat = new double*[dim];
	
	// load data into memory
	for(int i=0; i<dim; i++)
	{
		
	}

	int repeat = 0;
	while(1)
	{
		repeat ++;
		cout<<"TRAINING "<<repeat<<" TIMES."
			<<endl;	
		for(int i=0; i<dim; i++)
		{
			
		}
	}
	
	// backward computing

	
	// tips for running this program
	cout<<"FINAL OUTPUT OF VECTOR OF WEIGHT"
		<<" IS SAVED IN FILE [TRN_OUT.dt]."
		<<endl;

}

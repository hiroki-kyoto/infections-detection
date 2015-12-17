// check_index.cpp
// check index data file
// if the format or the data is abnormal,
// we have to modify our code and 
// rebuild the library
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, const char ** argv)
{
	ifstream in;
	in.open(argv[1]);
	cout<<argv[1]<<endl;
	// only read the first 100 data
	unsigned long long bar;
	for(int i=0; i<30; i++)
	{
		in>>bar;
		cout<<bar;
	}
	in.close();
}

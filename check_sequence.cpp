// check if sequence is ok
#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

int main(int argc, const char ** argv)
{
	fstream reader;
	if(argc<2)
	{
		cout<<
		"PLEASE INPUT AT LEAST ONE PARAMETER"
		<<endl;
		return -1;
	}
	reader.open(argv[1], ios::in);
	char ch;
	ch = reader.get();
	while(ch!=EOF)
	{
		if(ch>='a'&&ch<='z')
			ch -= ('a'-'A');
		if(ch!='A'&&ch!='C'&&
			ch!='G'&&ch!='T'&&
			ch!='N'&&ch!='\n')
			cout<<ch;
		ch = reader.get();
	}
	reader.close();
	cout<<endl;

	return 0;
}

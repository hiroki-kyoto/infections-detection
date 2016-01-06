#include <iostream>
#include "../basic.h"

using namespace std;

int main()
{
	list * l = new list;
	Lini(l);
	
	Ladd(l, 1, 323);
	Ladd(l, 2, 3459);
	Ladd(l, 5, 3324);
	
	int docId, nextPattern;
	Lpop(l, docId, nextPattern);
	cout<<"docId="<<docId;
	cout<<"nextPattern="<<nextPattern;
	cout<<endl;
	cout<<"===empty==="<<endl;
	Lempty(l);
	
	delete l;

	return 0;
}

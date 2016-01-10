// t_encode.cpp
// test for encode module
#include <iostream>
#include "../basic.h"

using namespace std;

int main()
{
	char card[CARD_SIZE+1] = "TTTTTTTTTT";
	int code = 0;
	cout<<card<<endl;
	encode(card, code);
	cout<<code<<endl;
	decode(card, code);
	cout<<card<<endl;
	return 0;
}

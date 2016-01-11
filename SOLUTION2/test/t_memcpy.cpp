// test for memory copy function

#include <iostream>
#include "../basic.h"

using namespace std;

int main()
{
	char card[100] = "XIANG-CHAO-IS-A-BAD-MAN";
	move_left(card, 100, 3, 0);
	cout<<"move left: "<<card<<endl;
	// move right
	move_right(card, 100, 3, 'X');
	cout<<"move right: "<<card<<endl;

	return 0;
}

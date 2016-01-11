// t_basic.cpp
#include <iostream>
#include "../basic.h"

int main()
{	
	node * n1 = new node;
	node * n2 = new node;
	node * n3 = new node;
	
	n1->doc = 0;
	n1->next = 183;
	
	n2->doc = 1;
	n2->next = 9432;
	
	n3->doc = 4;
	n3->next = 3932;
	
	n3->last = n2;
	n2->last = n1;
	n1->last = NULL;
	
	node * n = n3;
	
	while(n!=NULL)
	{
		std::cout<<n->doc<<"\t";
		std::cout<<n->next<<"\t";
		n = n->last;
	}
	
	delete n1;
	delete n2;
	delete n3;

	return 0;
}

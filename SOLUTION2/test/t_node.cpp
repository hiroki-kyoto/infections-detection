// t_basic.cpp
#include <iostream>
#include "../basic.h"

int main()
{	
	node * n1 = new node;
	node * n2 = new node;
	node * n3 = new node;
	
	int * data1 = new int(3);
	int * data2 = new int(5);
	int * data3 = new int(11);
	
	n1->data = data1;
	n2->data = data2;
	n3->data = data3;
	
	n3->last = n2;
	n2->last = n1;
	n1->last = NULL;
	
	node * n = n3;
	
	while(n!=NULL)
	{
		std::cout<<*(int*)(n->data)<<"\t";
		n = n->last;
	}
	
	delete n1;
	delete n2;
	delete n3;

	delete data1;
	delete data2;
	delete data3;
	return 0;
}

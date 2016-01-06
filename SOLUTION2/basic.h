// basic.h
#ifndef BASIC_H
#define BASIC_H

#include <iostream>

// the structure of node
struct node 
{
	node * last; // last node linked to
	void * data; // data to store
};

// structure of linked list
struct list 
{
	node * head;
	node * tail;
	int size;
};

inline void Lini(list * l)
{
	l->head = NULL;
	l->tail = NULL;
	l->size = 0;
}

inline void Ldel(list * l)
{
	
}

inline void Ladd(list * l, node * n)
{
	// from empty to non-empty
	if(l->size==0)
	{
		l->head = l->tail = n;
		size = 1;
	}
	else
	{
		l->head->last = n;
		l->head = n;
		size ++;
	}
}

inline node * Lpop(list * l)
{
	if(l->size==0)
	{
		std::cout<<"Error: empty list!\n";
		return NULL;
	}
	else
	{
		node * n = l->tail;
		l->tail = l->tail->last;
		l->size --;
		return n;
	}
}

#endif

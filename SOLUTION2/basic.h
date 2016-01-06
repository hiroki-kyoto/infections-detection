// basic.h
#ifndef BASIC_H
#define BASIC_H

#include <iostream>
#include "config.h"

// the structure of node
struct node 
{
	node * last; // last node linked to
	int docId; // Doc ID
	int nextPattern; // Next Pattern ID
};

// structure of linked list
struct list 
{
	node * head;
	node * tail;
	int size;
};


/** function declaration **/
inline void Lini(list *l);
inline void Lempty(list *l);
inline void Ladd(list *l, int docId, int nextPattern);
inline void Lpop(list *l, int &docId, int &nextPattern);


inline void Lini(list * l)
{
	l->head = NULL;
	l->tail = NULL;
	l->size = 0;
}

inline void Lempty(list * l)
{
	int docId, nextPattern;
	while(l->size)
	{
		Lpop(l, docId, nextPattern);
#ifdef _DEBUG_
		std::cout<<"docId="<<docId<<"\t";
		std::cout<<"nextPattern="<<nextPattern;
		std::cout<<"\n";
#endif
	}
}

inline void Ladd(list * l, int docId, int nextPattern)
{
	// from empty to non-empty
	if(l->size==0)
	{
		node * n = new node;
		n->last = NULL;
		n->docId = docId;
		n->nextPattern = nextPattern;
		
		l->head = l->tail = n;
		l->size = 1;
	}
	else
	{
		node * n = new node;
		n->last = NULL;	
		n->docId = docId;
		n->nextPattern = nextPattern;
		
		l->head->last = n;
		l->head = n;
		l->size ++;
	}
}

inline void Lpop(list * l, int & docId, int & nextPattern)
{
	if(l->size==0)
		std::cout<<"Error: empty list!\n";
	else
	{
		node * n = l->tail;
		l->tail = l->tail->last;
		l->size --;
		docId = n->docId;
		nextPattern =  n->nextPattern;
		delete n;
	}
}

#endif

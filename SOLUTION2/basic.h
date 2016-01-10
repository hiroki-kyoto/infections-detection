// basic.h
#ifndef BASIC_H
#define BASIC_H

#include <iostream>
#include "config.h"

// the structure of node
struct node 
{
	node * last; // last node linked to
	int id; // pattern id
	int doc; // document id
	int next; // next pattern id
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
inline void Ladd(list *l, int id, int doc, int next);
inline void Lpop(list *l, int & id, int &doc, int &next);


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

inline void Ladd(list * l, int id, int doc, int next)
{
	// from empty to non-empty
	if(l->size==0)
	{
		node * n = new node;
		n->last = NULL;
		n->id = id;
		n->doc = doc;
		n->next = next;
		
		l->head = l->tail = n;
		l->size = 1;
	}
	else
	{
		node * n = new node;
		n->last = NULL;	
		n->id = id;
		n->doc = doc;
		n->next = next;
		
		l->head->last = n;
		l->head = n;
		l->size ++;
	}
}

inline void Lpop(list * l, int & id, int & docId, int & nextPattern)
{
	if(l->size==0)
		std::cout<<"Error: empty list!\n";
	else
	{
		node * n = l->tail;
		l->tail = l->tail->last;
		l->size --;
		id = n->id;
		doc = n->doc;
		next =  n->next;
		delete n;
	}
}


// hash map encode method
inline void encode(char * card, int & id)
{
	id = 0;
	for(int i=0; i<CARD_SIZE; i++)
	{
		id = 4*id 
			+ (card[i]==A)*0
			+ (card[i]==C)*1
			+ (card[i]==G)*2
			+ (card[i]==T)*3
			;
	}
}

// decode method
inline void decode(char * card, int id)
{
	char gram[4];

	gram[0] = A;
	gram[1] = C;
	gram[2] = G;
	gram[3] = T;

	for(int i=CARD_SIZE-1; i>=0; i--)
	{
		card[i] = gram[id%4];
		id = id/4;
	}
}




#endif

// basic.h
#ifndef BASIC_H
#define BASIC_H

#include <iostream>
#include "config.h"

// the structure of node
struct node 
{
	node * last; // last node linked to
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
inline void Ladd(list *l, int doc, int next);
inline void Lpop(list *l, int &doc, int &next);


inline void Lini(list * l)
{
	l->head = NULL;
	l->tail = NULL;
	l->size = 0;
}

inline void Lempty(list * l)
{
	int doc, next;

	while(l->size)
	{
		Lpop(l, doc, next);
#ifdef _DEBUG_
		std::cout<<"doc="<<doc<<"\t";
		std::cout<<"next="<<next<<"\n";
#endif
	}
}

inline void Ladd(list * l, int doc, int next)
{
	// from empty to non-empty
	if(l->size==0)
	{
		node * n = new node;
		n->last = NULL;
		n->doc = doc;
		n->next = next;
		
		l->head = l->tail = n;
		l->size = 1;
	}
	else
	{
		node * n = new node;
		n->last = NULL;	
		n->doc = doc;
		n->next = next;
		
		l->head->last = n;
		l->head = n;
		l->size ++;
	}
}

inline void Lpop(list * l, int & doc, int & next)
{
	if(l->size==0)
		std::cout<<"Error: empty list!\n";
	else
	{
		node * n = l->tail;
		l->tail = l->tail->last;
		l->size --;
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

// memory move
inline void move_left(char * block, int size, int offset, char ch=0)
{
	if(size<=0)
	{
		std::cout<<"Error: move_left param [size]<=0\n";
		return;
	}
	if(offset<0)
	{
		std::cout<<"Error: move_left param [offset]<=0\n";
		return;
	}

	if(!offset)
		return;
	if(offset>size)
	{
		std::cout<<"Error: move_left param [offset]>[size]\n";
		return;
	}

	for(int i=offset; i<size; i++)
		block[i-offset] = block[i];
	// fill in the blank zone with default char
	for(int i=0; i<offset; i++)
		block[size-1-i] = ch;
}

inline void move_right(char * block, int size, int offset, char ch=0)
{
	if(size<=0)
	{
		std::cout<<"Error: move_right param [size]<=0!\n";
		return;
	}
	if(offset<0)
	{
		std::cout<<"Error: move_right param [offset]<=0!\n";
		return;
	}
	if(!offset)
		return;
	if(offset>size)
	{
		std::cout<<"Error: move_right param [offset]>[size]\n";
		return;
	}

	for(int i=size-1-offset; i>=0; i--)
		block[i+offset] = block[i];
	for(int i=0; i<offset; i++)
		block[i] = ch;
}


#endif


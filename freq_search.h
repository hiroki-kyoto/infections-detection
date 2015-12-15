// freq_search.cpp
// search for frequent items in gene band
// using 11-gram method to split and match
#include <iostream>
using namespace std;
// a card of gene is made of 90 gene code
typedef char GENE;
#define PITCH 90
#define A 'A'
#define T 'T'
#define G 'G'
#define C 'C'
#define U 'U'
// structure 
struct CARD 
{
	GENE data[PITCH];
};

void freq_search()
{
	CARD card;
	GENE L[4]; //LABEL
	L[0] = A;
	L[1] = C;
	L[2] = G;
	L[3] = T;
	L[4] = U;
	L[5] = N; // UNKNOWN
	for(int i=0; i<PITCH; i++)
		card.data[i] = L[i%4];
	for(int i=0; i<PITCH; i++)
		cout<<card.data[i];
	cout<<endl;
	
}


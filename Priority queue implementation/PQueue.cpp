#include "PQueue.h"

void UpdateDown( PQueue*, int l, int p );
void UpdateUp( PQueue*, int l, int p );


PQueue* PQInit( int nSize )
{
	PQueue* pQueue = (PQueue*)calloc( 1, sizeof( PQueue ) ); //glowna alokacja kolejki
	if( pQueue == NULL )
	{
		printf( "Error occured during memory allocation (PQInit1)" );
		return NULL;
	}

	pQueue->itemArr = (PQItem**)calloc( nSize, sizeof( PQItem* )); //alokacja tablicy wskaznikow do elementow

	if( pQueue->itemArr == NULL )
	{
		free( pQueue );
		printf( "Error occured during memory allocation (PQInit2)" );
		return NULL;
	}

	pQueue->maxSize = nSize; //zapisuje w strukturze rozmiar maksymalny

	return pQueue;
}


int PQisEmpty( PQueue* PQ ) // pusta zwraca 1
{
	return !(PQ->currSize);
}

void PQEnqueue( PQueue* PQ, QPRIORINFO* pInfo, int nPrior )
{
	if( PQ->currSize == PQ->maxSize )
	{
		printf( "Queue is full (PQEnqueue)" );
		return;
	}

	PQ->itemArr[PQ->currSize] = (PQItem*)calloc( 1, sizeof( PQItem )); //alokacja pamieci na element
	
	if( PQ->itemArr[PQ->currSize] == NULL )
	{
		printf( "Error occured during memory allocation (PQEnqueue)" );
		return;
	}

	PQ->itemArr[PQ->currSize]->nPriority = nPrior;
	PQ->itemArr[PQ->currSize]->pInfo = pInfo;

	UpdateUp( PQ, 0, PQ->currSize++);//Przywracam kopiec do góry
}

PQItem* PQDequeue( PQueue* PQ )
{
	if( PQisEmpty( PQ ) )
	{
		perror( "Queue is empty (PQDequeue)" );
		return NULL;
	}

	PQItem* temp = PQ->itemArr[0];
	PQ->currSize--;
	PQ->itemArr[0] = PQ->itemArr[PQ->currSize]; // zamiana ostatniego z pierwszym
	PQ->itemArr[PQ->currSize] = NULL;
	if(PQ->currSize>1)
		UpdateDown( PQ, 0, PQ->currSize-1 ); //przywrocenie w dol

	return temp;
}

void PQClearQueue( PQueue* PQ ) //czysci kolejke
{
	while( !PQisEmpty( PQ ) )
	{
		PQItem* temp = PQDequeue( PQ );
		free( temp->pInfo );
		free( temp );
	}
}

void PQRelease( PQueue** PQ ) //usuwanie kolejki
{
	PQClearQueue( *PQ );
	free( (*PQ)->itemArr );
	free( *PQ );
	*PQ = NULL;
}

void PQPrint( PQueue* PQ )
{
	for( int i = 0; i < PQ->currSize; ++i )
	{
		printf( "wartosc: %d, priorytet: %d\n", PQ->itemArr[i]->pInfo->nKey, PQ->itemArr[i]->nPriority );
	}
}

void PrintInOrder( PQueue* PQ, int root )
{
	int leftchild = root * 2 + 1;
	int rightchild = root * 2 + 2;

	if( leftchild < PQ->currSize )
		PrintInOrder( PQ, leftchild ); //maksymalnie do lewej

	printf( "wartosc: %d, priorytet: %d\n",  PQ->itemArr[root]->pInfo->nKey, PQ->itemArr[root]->nPriority );
	if( rightchild < PQ->currSize )
		PrintInOrder( PQ, rightchild ); //maksymalnie do prawej

}

void DecreaseKey( PQueue* PQ, int i, int nPrior )
{
	if( nPrior < PQ->itemArr[i]->nPriority )
	{
		PQ->itemArr[i]->nPriority = nPrior;
		UpdateDown( PQ, i, PQ->currSize - 1 ); //przywrocenie kopca

	}
}

void IncreaseKey( PQueue* PQ, int i, int nPrior )
{
	if( nPrior > PQ->itemArr[i]->nPriority )
	{
		PQ->itemArr[i]->nPriority = nPrior;
		UpdateUp( PQ, 0, i ); //przywrocenie kopca
	}
}

void UpdateUp( PQueue* PQ, int root, int child )
{
	if( root == child ) return; //jezeli kopiec jest pusty to nie ma co przywracac

	int parent = (child - 1) / 2;
	PQItem* x = PQ->itemArr[child];

	while(( child > 0 ) && !( x->nPriority < PQ->itemArr[parent]->nPriority ))
	{
		PQ->itemArr[child] = PQ->itemArr[parent];
		child = parent;
		parent = (child - 1) / 2;
	}
	PQ->itemArr[child] = x;
}

void UpdateDown( PQueue* PQ, int parent, int lower )
{
	if( parent >= lower ) return;

	int child = 2 * parent + 1;
	PQItem* x = PQ->itemArr[lower];

	while( child <= lower )
	{
		if( child < lower )// sprawdzamy czy jest prawe dziecko
			if( PQ->itemArr[child]->nPriority < PQ->itemArr[child + 1]->nPriority ) child++; // jeśli priorytet lewego dziecka jest mniejszy niż prawego to przechodzimy na prawe

		if( x->nPriority > PQ->itemArr[child]->nPriority ) break;// jeśli priorytet rodzica jest większy niż najwiekszedo dziecka mozna przerwac

		PQ->itemArr[parent] = PQ->itemArr[child]; // zamiana z rodzicem wiekszego dziecka
		parent = child;
		child = 2 * child + 1; //zmiana indeksow
	}
	PQ->itemArr[parent] = x;

}
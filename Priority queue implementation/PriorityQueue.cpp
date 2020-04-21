#include <iostream>
#include "PQueue.h"
#include <time.h>

#define QUEUESIZE 10

int main()
{
	PQueue* pQue = PQInit( QUEUESIZE );
	srand( (unsigned int)time( NULL ) );

	for( int i = 0; i < 8; ++i )
	{
		QPRIORINFO* temp = (QPRIORINFO*)calloc( 1, sizeof( QPRIORINFO ) );
		temp->nKey = i;
		int prior = rand() % QUEUESIZE;
		PQEnqueue( pQue, temp, prior );
	}

	for( int i = 4; i < 6; ++i )
	{
		QPRIORINFO* temp = (QPRIORINFO*)calloc( 1, sizeof( QPRIORINFO ) );
		temp->nKey = i;
		PQEnqueue( pQue, temp, i );
	}

	printf( "print:\n" );
	PQPrint( pQue );

	printf( "in order:\n" );
	PrintInOrder( pQue,0);

	printf( "dequeue:\n" );
	while( !PQisEmpty(pQue) )
	{
		PQItem* temp = PQDequeue( pQue );
		printf( "wartosc: %d, priority: %d\n", temp->pInfo->nKey, temp->nPriority );
	}

	PQRelease( &pQue );

	return 0;
}
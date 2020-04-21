#pragma once

#include "global.h"
#include <memory.h>
#include <cstdlib>
#include <stdio.h>

typedef struct
{
	QPRIORINFO* pInfo;
	int nPriority;
} PQItem;

typedef struct
{
	PQItem** itemArr;
	int maxSize;
	int currSize;

} PQueue;

PQueue* PQInit( int nSize );
int PQisEmpty( PQueue* PQ );
void PQEnqueue( PQueue* PQ, QPRIORINFO* pInfo, int nPrior );
PQItem* PQDequeue( PQueue* PQ );
void PQClearQueue( PQueue* PQ );
void PQRelease( PQueue** PQ );
void PQPrint( PQueue* PQ );
void DecreaseKey( PQueue* PQ, int i, int nPrior );
void IncreaseKey( PQueue* PQ, int i, int nPrior );
void PrintInOrder( PQueue* PQ, int root );


#ifndef _DSTACK_H

#define _DSTACK_H

#include <iostream>
using namespace std;

typedef struct tagDStackItem
{
	double dValue;
	tagDStackItem* pNext;
} DStackItem;

void dmakeEmptyStack( DStackItem** pStack );
void dpush( DStackItem**, double dValue );
double dpop( DStackItem** );
double dtop( DStackItem* );
void ddel( DStackItem** );
int disEmpty( DStackItem* );

#endif
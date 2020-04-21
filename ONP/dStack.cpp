#include "dStack.h"

//DStackItem* pHead = NULL; //stack is empty
				//first empty element on the stack

void dpush( DStackItem** pStack, double value )
{
	DStackItem* p = (DStackItem*)malloc( sizeof( DStackItem ) );
	if (p) {
		p->dValue = value;
		p->pNext = *pStack;
		*pStack = p;
	}
	else
	{
		cerr << "Stack overflow! dpush()\n\n'";
	}
}


double dpop( DStackItem** pStack )
{

	double x = 0; //!!!!!
	if (!disEmpty( *pStack ))//!isempty()
	{
		x = dtop( *pStack );
		ddel( pStack );
	}
	else
		printf( "%s\n\n", "Stack underflow! dpop()" );
	return x;
}
double dtop( DStackItem* pStack )
{
	if (!disEmpty( pStack ))
		return pStack->dValue;
	//!!!!
	printf( "%s\n\n", "Stack underflow! dtop()" );
	return 0;
}
void ddel( DStackItem** pStack )
{
	if (!disEmpty( *pStack ))
	{
		DStackItem* p = *pStack;
		*pStack = (*pStack)->pNext;
		free( p );
	}
	else
		printf( "%s\n\n", "Stack udnerflow! ddel()");
}
int disEmpty( DStackItem* pStack )
{
	return !pStack;
}

void dmakeEmptyStack( DStackItem** pStack )
{
	while (!disEmpty( *pStack )) ddel( pStack );
	*pStack = NULL;
}

//
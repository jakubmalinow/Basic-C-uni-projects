#include "stack.h"




StackItem* pHead = NULL; //stack is empty
				//first empty element on the stack

void push( StackItem** pStack, char c )
{
	StackItem* p = (StackItem*)malloc( sizeof( StackItem ) );
	if (p) {
		p->cKey = c;
		p->pNext = *pStack;
		*pStack = p;
	}
	else
	{
		cerr << "Stack overflow! push()\n\n'";
	}
}

char popUntilBracket( StackItem** pStack )
{
	char c = top( *pStack );
	if ((c != '(') && c)//!isempty()
		del( pStack );
	else
		printf( "%s\n\n", "Stack underflow! popUntilBracket()" );
	return c;
}

char pop( StackItem** pStack )
{
	char c = top( *pStack );
	if (c)//!isempty()
		del( pStack );
	else
		printf( "%s\n\n", "Stack underflow! pop()" );
	return c;
}
char top( StackItem* pStack )	//dla stosu znakowego nie wypisuje bledu gdy stos jest pusty, ale zwracamy znak o kodzie 0 co odpowiada wartosci FALSE
{
	if (!isEmpty( pStack ))
		return pStack->cKey;
	return 0;
}
void del( StackItem** pStack )
{
	if (!isEmpty( *pStack ))
	{
		StackItem* p = *pStack;
		*pStack = (*pStack)->pNext;
		free( p );
	}
	else
		printf( "%s\n\n", "Stack underflow! del()" );
}
int isEmpty( StackItem* pStack )
{
	return !pStack;
}

void makeEmptyStack( StackItem** pStack )
{
	while (!isEmpty( *pStack )) del( pStack );
	*pStack = NULL;
}

//
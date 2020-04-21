#ifndef _STACK_H //if not defined, dolacza do kodu tylko jezeli stala stack.h jest niezdefiniowana, 
//jezeli wielokrotnie includujemy ten plik, zostanie to zrobione tylko raz, eliminuje to bledy kompilacji
#define _STACK_H		//tu jest definiowanie

#include <iostream>
using namespace std;

typedef struct tagStackItem
{
	char cKey;
	tagStackItem* pNext;
} StackItem;


void makeEmptyStack( StackItem** pStack );
void push( StackItem** pStack, char c );
char pop( StackItem** pStack );
char top( StackItem* pStack );
void del( StackItem** pStack );
int isEmpty( StackItem* pStack );
char popUntilBracket( StackItem** pStack );

#endif

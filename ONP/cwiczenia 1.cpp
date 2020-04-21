// 10.10.2019
#include <stdio.h>
#include <iostream>
#include "stack.h"
#include "dStack.h"


#define DOT '.'
using namespace std;

void skipSpaces();
double getNum( char, StackItem** );
double isDigit( char c );
int prior( char cOper );
char getOper();
double ONP();
double Calc( double arg1, double arg2, char cOperator );


int main()
{
	while (1)
	{
		printf( "podaj wyra¿enie: " );
		printf("Wynik: %f\n",ONP());//!!!wypis

	}
}

void skipSpaces() {
	char c;
	while ( (c = getchar()) == ' ' );
	ungetc( c, stdin );
}
double getNum( char sgn, StackItem** pStack ) {
	char c;
	double num = 0;

	//schemat hornera 
	double m = 1;
	bool foundDot = false;
	while ( isDigit(c = pop( pStack )) )
	{
		num = num * 10 + c - '0';
	}
	if (c == DOT)
		while ( isDigit(c = pop( pStack )) )
		{
			m = m * 0.1;
			num = num + (c - '0')*m;
		}

	push( pStack, c );
	if (sgn == 'n') return -1 * num;
	return num;
}

double Calc( double arg1, double arg2, char cOperator ) {
	switch (cOperator)
	{
	case '+': return arg1 + arg2;
	case '-': return arg1 - arg2;
	case '*': return arg1 * arg2;
	case '/': if( fabs(arg2) > 1e-14 )
		return arg1 / arg2;
		cerr << "error, division by 0 - calc()";
		break;
	case '^':
		return pow( arg1, arg2 );
	}
	return 0;
}

double isDigit( char c ) {
	return (c >= '0') && (c <= '9');
}
int prior( char cOper ) {
	switch (cOper)
	{
	case '+':
	case'-': return 1;
	case '*':
	case '/': return 2;
	case '^': return 3;

	}
	return 0;
}
int isOper( char cOper ) {
	switch (cOper)
	{
	case '+':
	case'-':
	case '*':
	case'^':
	case '/': return 1;
	}
	return 0;
}

char getOper() {
	skipSpaces();
	return getchar();
}
double ONP() {
	double res = 0;
	char c;

	skipSpaces();

	StackItem* pStack = NULL;
	makeEmptyStack( &pStack );

	StackItem* resStack = NULL;
	makeEmptyStack( &resStack );

	DStackItem* resultDStack = NULL;
	dmakeEmptyStack( &resultDStack );


	bool prevWasDigit = false;
	while ( (c = getchar()) != '\n' )
	{
		skipSpaces();
		if ( !prevWasDigit && c == '-' )//przydpaek -(a+b), -2^2, -(2)^2
		{
			push( &resStack, 'n' ); //obsluga liczb ujemnych : -2 = -1*2, dzieki temu dziala np -2^2= -4
			push( &resStack, '1' );
			ungetc( '*', stdin );
			prevWasDigit = true;
		}

		else if ( (isDigit( c )) || ( c == DOT ) || ( !prevWasDigit && c != '(' && c != ')') ) // -( nie wypisze ' p '
		{
			push( &resStack, 'p' ); 

			while ( isDigit( c ) || c == DOT ) //pobierz liczbe i wypisz znakowo na stos wynikowy
			{
				push( &resStack, c );
				c = getchar();
			}
			ungetc( c, stdin );
			prevWasDigit = true;

		}
		else if (c == '(')
		{
			push( &pStack, c );
			prevWasDigit = false;
		}
		else if (c == ')')
		{
			while ((top( pStack )) != '(') 
				push( &resStack, popUntilBracket( &pStack ) ); //wydaj znaki w nawiasach na stos wynikowy
			del( &pStack ); //usuwa nawias ze stosu
			prevWasDigit = true; //przed nawiasem (lub nawiasami) zawsze bedzie liczba
		}
		else if ( isOper( c ) ) //ONP
		{
			while (prior( c ) <= prior( top( pStack ) )) 
				push( &resStack, pop( &pStack ) );
			push( &pStack, c );
			prevWasDigit = false;

		}
		else cerr << "unrecognized charachter - onp()" << endl;
	}

	while (!isEmpty( pStack ))
		push( &resStack, pop( &pStack ) ); // wypisz reszte operatorow na stos koncowy

	//makeEmptyStack(&pStack);

	while (!isEmpty( resStack ))
		push( &pStack, pop( &resStack ) ); // odwroc stos koncowy

#ifdef _DEBUG_
	while (!isEmpty( pStack ))
		printf( "%c", pop( &pStack ) );
	cout << endl;
#endif 

	while (!isEmpty( pStack )) //oblicznaie wartosci
	{
		c = pop( &pStack );
		if (c == 'p' || c == 'n')
		{
			dpush( &resultDStack, getNum( c, &pStack ) );
		}
		else if (isOper( c ))
		{
			double val1 = dpop( &resultDStack );
			double val2 = dpop( &resultDStack );
			dpush( &resultDStack, Calc( val2, val1, c ) );
		}
	}
	return dpop( &resultDStack );
	//printf( "=%0.2lf\n\n", dpop( &resultDStack ) );
	return 1;
}










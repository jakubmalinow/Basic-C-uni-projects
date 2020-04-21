#include "List.h"
#include "global.h"
#include <iostream>

int compare( const void* p, const void *v );

int main()
{
	int ll = 4;
	int* l = &ll;
	std::cout << *&l << std::endl;
	std::cout << &ll << std::endl;







	ListItem* pHead = CreateList(); //tworze head listy
	
	for( int i = 0; i < 7; i++ ) //dodaje elementy listy
	{
		LISTINFO* data = (LISTINFO*)malloc( sizeof( LISTINFO ) );
		data->nKey = i;
		InsertFront( pHead, data );
	}
	printf( "Lista: " );
	PrintList( pHead );

	SortList( pHead, compare );
	printf( "Lista po sortowaniu: " );
	PrintList( pHead );

	printf( "\nSzukam elementu o wartosci 4, i wstawiwam po nim 999 \n" );
	LISTINFO* x = (LISTINFO*)malloc( sizeof( LISTINFO ) );
	x->nKey =4;
	LISTINFO* y = (LISTINFO*)malloc( sizeof( LISTINFO ) );
	y->nKey = 999;

	ListItem* pPrevious = NULL;
	ListItem* foundItem = Find( pHead, x, &pPrevious, compare );
	
	Insert( foundItem, y );
	printf( "Lista: " );
	PrintList( pHead );

	x->nKey = 0;
	printf( "\nSzukam elementu o wartosci 0, i usuwam nastepny \n" );
	foundItem = Find( pHead, x, &pPrevious, compare );
	Remove( foundItem );
	PrintList( pHead );

	printf( "\nUsuwam pierwszy element\n" );
	RemoveFront( pHead );
	printf( "Lista: " );
	PrintList( pHead );

	x->nKey = 111;
	printf( "\nWstawiam na poczatek element o wartosci 111\n" );
	InsertFront( pHead, x);
	printf( "Lista: " );
	PrintList( pHead );

	printf( "\nZwalniam liste\n" );
	FreeList( pHead );
	printf( "Lista: " );
	PrintList( pHead );
	
	printf( "\nUsuwam cala liste\n" );
	DelList( &pHead );
	printf( "Lista: " );
	PrintList( pHead );

	
}

int compare( const void* p, const void *v )
{
	LISTINFO* x = (LISTINFO*)p;
	LISTINFO* y = (LISTINFO*)v;
	if( x->nKey == y->nKey ) return 0;
	if( x->nKey > y->nKey ) return 1;
	if( x->nKey < y->nKey ) return -1;
}

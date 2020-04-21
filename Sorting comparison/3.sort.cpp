// Sortowania.cpp : Ten plik zawiera funkcjê „main”. W nim rozpoczyna siê i koñczy wykonywanie programu.
//
#include <iostream>
#include "Tab.h"
#define _DEBUG_

int main(int argc, char** argv)
	{

	if( argc != 2 )
	{
		perror( "Nie podano rozmiaru tablicy!" );
		return 1;
	}

	int tabSize = atoi(argv[1]);

	if( tabSize <= 0 )
	{
		perror( "Niepoprwany rozmiar tablicy!" );
		return 1;
	}

	int* pTab = NULL;
	int* pCopyTab = NULL;
	if( !(pTab = createTab( tabSize )))
	{
		perror("Alokacja nie powiodla sie");
			return 1;
	}
	if( !(pCopyTab = createTab( tabSize )))
	{
		perror("Alokacja nie powiodla sie");
			return 1;
	}

	clock_t start;
	clock_t stop;

	ToSort sortingAlghoritms[] = { SelectionSort, BubbleSort, MixedBubbleSort, InsertionSort, HalfInsertionSort, QuickSort, HeapSort, callMerge1 };
	const char* sortingAlghoritmsNames[] = { "SelectionSort", "BubbleSort", "MixedBubbleSort", "InsertionSort", "HalfInsertionSort", "QuickSort", "HeapSort", "MergeSort1" };
	int nAlghoritms = sizeof( sortingAlghoritms ) / sizeof( ToSort );

#ifdef _DEBUG_
	tabSize = 50; //zeby dalo sie zobaczyc czy sortuje poprawnie
#endif 

	randInit( pTab, tabSize ); //inicjowanie losowe
	//constInit( pTab, tabSize, 6 ); //inicjowanie jedna liczba

#ifdef _DEBUG_
	printf( "Wylosowana tablica: \n" );
	printTab( pTab, tabSize ); //wypisanie wylosowanej tablicy
#endif

	//petla z sortowaniami:
	for( int i = 0; i < nAlghoritms; i++ )
	{
		copyTab( pCopyTab, pTab, tabSize ); 
		printf( "Czas sortowania %d elementow %s: ", tabSize, sortingAlghoritmsNames[i] );

		start = clock();
		sortingAlghoritms[i]( pCopyTab, tabSize );
		stop = clock();

		double czas = (double)(stop - start) / CLOCKS_PER_SEC;
		printf( "%lf\n", czas );

#ifdef _DEBUG_
		printTab( pCopyTab, tabSize ); //wypisanie posortowanej tablicy
#endif
	}
	
	//mergesort2 wymaga podwojnego rozmiaru tablicy, wiec nie moze zostac wywolany w petli
	int* pMerge2Tab = createTab( tabSize * 2 );
	copyTab( pMerge2Tab, pTab, tabSize );

	printf( "Czas sortowania %d elementow MergeSort2: ", tabSize);

	start = clock();
	callMerge2( pMerge2Tab, tabSize );
	stop = clock();

	double czas = (double)(stop - start) / CLOCKS_PER_SEC;
	printf( "%lf\n", czas );

#ifdef _DEBUG_
	printTab( pMerge2Tab, 100); //wypisanie posortowanej tablicy
#endif

	freeTab( pTab );
	freeTab( pCopyTab );
	freeTab( pMerge2Tab );

	return 0;
}


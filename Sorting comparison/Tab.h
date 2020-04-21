#ifndef _TAB_
#include <time.h>
#include <stdio.h>
#include <iostream>

#define _TAB_
int* createTab( int nSize );// malloc + memset + if (gdy blad zwraca NULL) //tablica dynamicznie 
void freeTab( int* pTab );
void initTab( int* pTab, int nSize, int nVal ); //inicjuje tablice dowolna liczba
void randInit( int* pTab, int nSize ); //inicjuje tablice o danym rozmiarze losowo, srand i modulo pewna wartosc
void constInit( int *pTab, int nSize, int number);// inicjuje talbice o danym rozmiarze jedn¹ liczb¹
void copyTab( int* pTabTo, int* pTabFrom, int nSize ); //kopiowanie tablicy z pTabFrom do pTabTo o rozmiarze nSize
void printTab( int *pTab, int nSize );

void SelectionSort( int *pTab, int nSize );
void InsertionSort( int *pTab, int nSize ); //od do³u przesuwaæ, czêœæ posortowana dla dolnej czêœci
void HalfInsertionSort( int *pTab, int nSize ); //wyszukiwanie po³ówkowe
void BubbleSort( int *pTab, int nSize ); //u gory jest indeks 0 tam gdzie najlzejsze bombelki, na dole indeks ity tam gdzie ciezsze
void MixedBubbleSort( int *pTab, int nSize); 
void QuickSort( int *pTab, int nSize );
void quicksortt( int* pTab, int l, int p );
void callMerge1( int* pTab, int nSize );
void MergeSort1( int* pTab, int* pHelperTab, int l, int p );
void merge1( int* pTab, int* pHelperTab, int low, int middle, int high );
void callMerge2( int *pTab, int nSize );
void MergeSort2( int* pTab, int low, int high, int nSize);
void merge2( int* pTab, int low, int middle, int high, int nSize );
void HeapSort( int *pTab, int nSize );

typedef void( *ToSort )(int*, int);

#endif
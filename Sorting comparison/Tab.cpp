#include "Tab.h"


int* createTab( int nSize )
{
	if( nSize <= 0 ) {
		perror( "Nie mozna utworzyc tablicy o takim rozmiarze" );
		return NULL;
	}

	int* pTab = (int*)malloc( nSize * sizeof(int) );
	memset( pTab, 0, nSize );

	return pTab;
}

void freeTab( int* pTab )
{
	free( pTab );
	pTab = NULL;
}

void initTab( int* pTab, int nSize, int nVal )
{
	for( int i = 0; i < nSize; i++ )
		*pTab++ = nVal;
}

void copyTab( int* pTabTo, int* pTabFrom, int nSize )
{
	/*for( int i = 0; i < nSize; i++ )
		*pTabTo++ = *pTabFrom++;*/
	//!!!!!!!!!!
	memcpy( pTabTo, pTabFrom, nSize * sizeof( int ) );
}

void randInit( int* pTab, int nSize )
{
	srand((unsigned int) time( NULL ) );
	for( int i = 0; i < nSize; i++ )
	{
		*pTab++ = rand() % nSize + 1;
	}
}

void constInit( int *pTab, int nSize, int number )
{
	for( int i = 0; i < nSize; i++ )
	{
		*pTab++ =number;
	}
}

void printTab( int *pTab, int nSize )
{
	for( int i = 1; i < nSize+1; i++ )
	{
		printf( "%d\t", *pTab++ );
		if( !(i % 5) )printf( "\n" );
	}
}

void SelectionSort( int *pTab, int nSize )
{
	for( int i = 0; i < nSize-1; i++ )
	{
		int min = pTab[i];
		int position = i;
		for( int j = i + 1; j < nSize; j++ )
		{
			if( pTab[j] < min )
			{
				min = pTab[j];
				position = j;
			}
		}		
		pTab[position] =pTab[i];
		pTab[i] = min;
	}
}

void BubbleSort( int *pTab, int nSize )
{
	for( int i = 1; i < nSize; i++ )
	{
		for( int j = nSize-1; j >= i; j-- )
		{
			if( pTab[j - 1] > pTab[j] )
			{
				int temp = pTab[j - 1];
				pTab[j - 1] = pTab[j];
				pTab[j] = temp;
			}
		}
	}
}

void InsertionSort( int *pTab, int nSize )
{
	for( int i = 1; i < nSize; i++ )
	{
		int temp = pTab[i];
		int j = i - 1;
		while( j>=0 && temp < pTab[j])
		{
			pTab[j + 1] = pTab[j--];
		}
		pTab[j + 1] = temp;
	}
}

void HalfInsertionSort( int *pTab, int nSize )
{
	for( int i = 2; i < nSize; i++ )
	{
		int temp = pTab[i];
		int l = 0;
		int p = i - 1;
		while( l <= p )
		{
			int m = (l + p) / 2;
			if( temp < pTab[m] ) p = m - 1;
			else l = m + 1;
		}
		for( int j = i - 1; j >= l; j-- )
		{
			pTab[j + 1] = pTab[j];
		}
		pTab[l] = temp;
	}
}

void MixedBubbleSort( int *pTab, int nSize )
{
	int l = 1;
	int p = nSize-1;
	int k = nSize-1;

	do
	{
		for( int j = p; j >= l; j-- )
			if( pTab[j - 1] > pTab[j] )
			{
				int temp = pTab[j - 1];
				pTab[j - 1] = pTab[j];
				pTab[j] = temp;
				k = j;
			}		
	
		l = k + 1;
		for( int j = l; j <= p; j++ )
			if( pTab[j - 1] > pTab[j] )
			{
				int temp = pTab[j - 1];
				pTab[j - 1] = pTab[j];
				pTab[j] = temp;
				k = j;
			}
		
		p = k - 1;
	} while( l <= p );

}

void quicksortt(int* pCopyTab, int l, int p )
{
	int w;
	int i = l;
	int j = p;
	int	pivot = pCopyTab[(l + p) / 2];
	do
	{
		while( pCopyTab[i] < pivot ) i++;
		while( pivot < pCopyTab[j] ) j--;
		if( i <= j )
		{
			w = pCopyTab[i];
			pCopyTab[i++] = pCopyTab[j];
			pCopyTab[j--] = w;
		}

	} while( !(i > j) );
	if( l < j )quicksortt( pCopyTab, l, j );
	if( i < p )quicksortt( pCopyTab,i, p );
}


void QuickSort( int* pTab, int nSize)
{
	quicksortt( pTab, 0, nSize - 1 ); // zeby dalo sie dodac quicksorta to tablicy, i wywolac jak pozostale funkcje
}

void przesiewanie( int* pTab,  int l, int p ) //do heap sort
{
	if( l == p ) return;
	int i = l;
	int j = 2 * i+1;
	int x = pTab[i];

	while( j <= p )
	{
		if( (j < p) && (pTab[j] < pTab[j + 1]) ) j++;
		if( x >= pTab[j] ) break;
		pTab[i] = pTab[j];
		i = j;
		j = 2 * i+1;
	}
	pTab[i] = x;
}

void HeapSort( int *pTab, int nSize ) 
{
	int l = nSize / 2;
	int p = nSize-1;

	//!!!!!!!!!!
	for(;l>0;l--)
		przesiewanie( pTab, l-1, p ); 

	for( ; p > 0; p-- )
	{
		int x = pTab[0];
		pTab[0] = pTab[p];
		pTab[p] = x;
		przesiewanie( pTab, l, p - 1 );
	}
}

void callMerge1( int* pTab, int nSize ) //aby dalo sie wywowalac mergesorta1 w petli
{
	int* pHelperTab = createTab( nSize );
	MergeSort1( pTab, pHelperTab, 0, nSize - 1 );
	freeTab( pHelperTab );
}

void MergeSort1( int* pTab, int* pHelperTab, int low, int high )
{
	if( low < high )
	{
		int middle = low + (high - low) / 2;
		MergeSort1( pTab, pHelperTab, low, middle );
		MergeSort1( pTab, pHelperTab, middle + 1, high );

		merge1( pTab, pHelperTab, low, middle, high );
	}
}


void merge1( int* pTab, int* pHelperTab, int low, int middle, int high ) //do mergesorta1
{
	//!!!!!!!!
	//for( int i = low; i <= high; i++ )//memcpy
	//	pHelperTab[i] = pTab[i];
	memcpy( pHelperTab+low, pTab+low, (high - low + 1) * sizeof( int ));

	int i = low;
	int j = middle + 1;
	int k = low;

	while( i <= middle && j <= high )
	{
		if( pHelperTab[i] <= pHelperTab[j] )
			pTab[k++] = pHelperTab[i++];
		else
			pTab[k++] = pHelperTab[j++];
	}

	//!!!!!!!!!!!!!!
	////kopiowanie pozostalych elementow z lewej strony
	//while( i <= middle )
	//	pTab[k++] = pHelperTab[i++];
	memcpy( pTab+k, pHelperTab+i, (middle - i + 1) * sizeof( int ) );


}

void callMerge2( int *pTab, int nSize ) //mergesorta2 i tak nie wywolujemy w petli ale ladniej to wyglada w mainie
{
	MergeSort2( pTab, 0, nSize - 1 , nSize);
}

void MergeSort2( int* pTab, int low, int high, int nSize )
{
	if( low < high )
	{
		int middle = low + (high - low) / 2;
		MergeSort2( pTab, low, middle, nSize );
		MergeSort2( pTab, middle + 1, high, nSize );

		merge2( pTab, low, middle, high, nSize );
	}
}

void merge2( int* pTab, int low, int middle, int high, int nSize ) //do mergesorta2
{
	/*for( int i = low; i <= high; i++ )
		pTab[i+nSize] = pTab[i];*/
	//!!!!!!!!!!!
	memcpy( pTab + low + nSize, pTab + low, (high - low + 1) * sizeof( int ) );

	int i = low;
	int j = middle + 1;
	int k = low;

	while( i <= middle && j <= high )
	{
		if( pTab[i+nSize] <= pTab[j+nSize] )
			pTab[k++] = pTab[i++ + nSize];
		else
			pTab[k++] = pTab[j++ + nSize];
	}

	//kopiowanie pozostalych elementow z lewej strony
	/*while( i <= middle )
		pTab[k++] = pTab[i++ + nSize];*/
	memcpy( pTab + k, pTab + i + nSize, (middle - i + 1) * sizeof( int ));


	/*
	for( int i = low; i <= high; i++ )
		pTab[i + nSize] = pTab[i];

	int i = low;
	int j = middle + 1;
	int k = low;
	int iR = low + nSize; // czy szybsze niz pisanie za kazdym razem i+nSize?
	int jR = middle + 1 + nSize;

	while( i <= middle && j <= high )
	{
		if( pTab[iR] <= pTab[jR] )
		{
			pTab[k++] = pTab[iR++];
			i++;
		}
		else
		{
			pTab[k++] = pTab[jR++];
			j++;
		}
	
	}

	//kopiowanie pozostalych elementow z lewej strony
	while( i <= middle )
		pTab[k++] = pTab[i++ + nSize];
		*/


}
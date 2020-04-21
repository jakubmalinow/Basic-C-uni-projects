#include "Matrix.h"
#include <iostream>

int CreateMatrix( double*** pTab, int nSize )
{
	*pTab = (double**)malloc( sizeof( double* ) * nSize ); //tworzymy tablice wskaünikÛw
	if( !*pTab ) return 0;
	memset( *pTab, NULL, sizeof( double* ) * nSize );

	double** creator = *pTab;// tworzymy wskaünik pomocniczy øeby nie zmieniac wskaznika pTab
	for( int i = 0; i < nSize; i++ )
	{
		*creator = (double*)malloc( sizeof( double ) * nSize ); //alokacja dla kazdego wiersza
		if( !*creator ) return 0;
		memset( *creator++, 0, sizeof( double ) * nSize );
	}
	return 1;
}

void ComplementOfElement( double** pFrom, double** pTo, int skipRow, int skipCol, int nSize ) //dopelnienie elemenutu macierzy
{
	for( int i = 0; i < nSize; i++, pFrom++ )
	{
		double* pColO = *pTo;
		double* pColI = *pFrom; //ustawiam na 1 kolumne obecnego wiersza

		if( i == skipRow )	continue;

		for( int j = 0; j < nSize; j++, pColI++ )
		{
			if( j == skipCol )	continue;
			*pColO++ = *pColI;
		}
		pTo++;
	}
}

double Det( double** pMatrix, int nSize )
{
	if( nSize == 2 )
		return pMatrix[1][1] * pMatrix[0][0] - pMatrix[1][0] * pMatrix[0][1];

	double** pComplementMatrix = NULL; // macierz dopelnien o 1 mniejsza
	CreateMatrix( &pComplementMatrix, nSize - 1 );

	int sgn = 1;
	double result = 0;
	double** pRow = pMatrix; //wskaznik pokazujacy na element wzgledem ktorego dopelniamy
	for( int i = 0; i < nSize; i++ )
	{
		ComplementOfElement( pMatrix, pComplementMatrix, i, 0, nSize );//skopiuj dopelnienie macierzy pMatrix do ComplementMatrix
		result += Det( pComplementMatrix, nSize - 1 ) * (**pRow++) * sgn;
		sgn = -sgn; //!! zamiast *=-1
	}
	DeleteMatrix( &pComplementMatrix, nSize - 1 );

	return result;
}

void MakeComplementaryMatrix( double** pMatrix, double** pInvertedMatrix, int nSize ) //macierz dopelnien
{
	double** pComplementaryMatrix = NULL;
	CreateMatrix( &pComplementaryMatrix, nSize - 1 );

	double** pRow = pInvertedMatrix;

	for( int i = 0; i < nSize; i++ )
	{
		int sgn = (i % 2) ? -1 : 1;
		double* pCol = *pInvertedMatrix;

		for( int j = 0; j < nSize; j++ )
		{
			ComplementOfElement( pMatrix, pComplementaryMatrix, i, j, nSize ); //dopelnienie wzgledem elementu
			*pCol++ = Det( pComplementaryMatrix, nSize - 1 )*sgn; //obliczenie wyznacznika i wpis do macierzy wynikowej
			sgn = -sgn;
		}
		pInvertedMatrix++;
	}
	DeleteMatrix( &pComplementaryMatrix, nSize - 1 );
}
void InverseMatrix( double** pMatrix, double** pInversedMatrix, int nSize, double det )
{
	MakeComplementaryMatrix( pMatrix, pInversedMatrix, nSize ); //utworzenie macierzy dopelnien

	double** pP = pInversedMatrix;
	for( int i = 0; i < nSize; ++i )
	{
		double* pCol = *pInversedMatrix;
		for( int j = 0; j < nSize; ++j )
		{
			*pCol++ /= det; //teraz dzielimy tylko kazdy element przez wyznacznik
		}
		pInversedMatrix++;
	}
	TransMatrix( pP, nSize ); //i transponujemy
}

void TransMatrix( double** pMatrix, int nDim )
{		
	double** pRow = pMatrix;  //zmienne pomocnicze

	for( int i = 0; i < nDim - 1; i++ )
	{
		double* pCol = *pRow++ + 1 + i;
		for( int j = i + 1; j < nDim; j++ )
		{
			double temp = *pCol;
			*pCol = pMatrix[j][i];
			pMatrix[j][i] = temp;
			*pCol++;
		}
	}
}

void LayoutEqu( double** pInv, double* pB, double* pRes, int nSize ) //mnozenie przez wektor wyrazow wolnych
{
	for( int i = 0; i < nSize; i++, pRes++, pInv++ )
	{
		double* pCol = *pInv;
		double* pVectorElement = pB;
		for( int j = 0; j < nSize; j++ )
		{
			*pRes += *pCol++ * *pVectorElement++;
		}
	}
}

void PrintMatrix( double** pTab, int nSize )
{
	for( int i = 0; i < nSize; i++ )
	{
		double* pCol = *pTab++;
		for( int j = 0; j < nSize; j++ )
		{
			printf( "%lf \t", *pCol++ );
		}
		printf( "\n" );
	}
}

void DeleteMatrix( double*** pTab, int nSize )
{
	double** pRow = *pTab;
	for( int i = 0; i < nSize; i++ )
	{
		free( *pRow++ ); //zwalniamy kazdy wiersz macierzy
	}
	free( *pTab );//zwalniamy glowny wskaznik
	*pTab = NULL;
}

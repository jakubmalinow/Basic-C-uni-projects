// 2.Macierze.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <iostream>
#include "Matrix.h"
#define MAX 3

void readDataToMatrix( FILE* pFile, int size, double** pMatrix, double* pWektor );

int main( int argc, char** argv )
{
	//!!!argc
	if( argc != 2 )
	{
		perror( "Nie podano pliku do odczytu" );
		return 0;
	}

	FILE* pFile = fopen( argv[1], "r" );

	if( !pFile )
	{
		perror( "Nie udalo sie otworzyc pliku z danymi" );
		return 0;
	}

	int nSize = 0;
	fscanf( pFile, "%d", &nSize ); //wczytaj rozmiar macierzy

	//alokacja pamieci na macierz z pliku, macierz odwrotn¹ i wektor wyrazow wolnych
	double** pMatrix = NULL;
	double** pInversedMatrix = NULL;

	double* pWektorWyrazow = (double*)malloc( nSize * sizeof( double ) );
	double* pResult = (double*)malloc( nSize * sizeof( double ) );
	memset( pResult, 0, nSize * sizeof( double ) ); //inicjujemy zerami wektor wynikowy bo "+=" inaczej nie zadziala w LayouEqu()"

	if( !CreateMatrix( &pMatrix, nSize ) )
	{
		perror( "Nie udalo sie zalokowac pamieci dla macierzy glownej!\n" );  //!!!!!!!!!!!! zamiast if else
		return 0;
	}

	if( !CreateMatrix( &pInversedMatrix, nSize ) )
	{
		perror( "Nie udalo sie zalokowac pamieci dla macierzy odwrotnej!" ); //!!!!!!!!!!!! zamiast if else
		return 0;
	}

	readDataToMatrix( pFile, nSize, pMatrix, pWektorWyrazow ); //wczytanie danych z pliku
	fclose( pFile );

	double determinant = Det( pMatrix, nSize );

	if( fabs( determinant ) < 1e-14 )
	{
		perror( "\nWyznacznik macierzy = 0, nie mozna kontynuowac obliczen" );
		return 0;
	}
	//!!!!!!!!!!!!! wrzucenie do warunkowej
#ifdef _DEBUG_
	printf( "\nWczytana macierz:\n" );
	PrintMatrix( pMatrix, nSize );

	printf( "\nWczytany wektor wyrazow wolnych:\n" ); 
	double *pWW = pWektorWyrazow;
	for( int i = 0; i < nSize; i++ )
		printf( "%lf\t", *pWW++ );
	pWW = NULL;

	printf( "\nWyznacznik glownej macierzy: %lf \n", determinant );
	printf( "\n" );
#endif // _DEBUG_


	InverseMatrix( pMatrix, pInversedMatrix, nSize, determinant ); //obliczanie macierzy odwrotnej

	LayoutEqu( pInversedMatrix, pWektorWyrazow, pResult, nSize ); //mnozymy macierz odworotna przez wektor wyrazow

	double* pResultToPrint = pResult; //pomocniczy wskaznik
	printf( "Wynik: \n" );
	for( int i = 0; i < nSize; i++ )
		printf( "%lf\n", *pResultToPrint++ ); //wyswietlanie wyniku

	free( pResult ); //usuwamy tablice wynikowa
	free( pWektorWyrazow ); //usuwamy tablice z wektorem
	DeleteMatrix( &pInversedMatrix, nSize ); //usuwamy macierz odwrotna
	DeleteMatrix( &pMatrix, nSize ); //usuwamy macierz glowna

	return 1;
}


void readDataToMatrix( FILE* pFile, int size, double** pMatrix, double* pWektor )
{
	for( int i = 0; i < size; i++ )
	{
		double* pColumn = *pMatrix++;
		for( int j = 0; j < size; j++ )
		{
			fscanf( pFile, "%lf", pColumn++ );
		}
		fscanf( pFile, "%lf", pWektor++ );
	}
}

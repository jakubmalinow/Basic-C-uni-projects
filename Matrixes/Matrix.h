#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include <stdio.h>

int CreateMatrix ( double*** pTab, int nSize ); // !!! - error 1 -ok alokuje pamiec dla nowej macierzy
void DeleteMatrix ( double*** pTab, int nSize ); // *pTab==NULL;
void TransMatrix ( double** pTab, int nDim ); // transponowanie macierzy
void InverseMatrix ( double** pMatrix, double** pInvertedMatrix, int nSize, double det ); // odwraca macierz
double Det ( double** pTab, int nSize ); // rozw wzg 0 wiersza rekurencyjnie
void LayoutEqu ( double** pInv, double* pB, double* pRes, int nSize ); // rozwiazuje rowananie
void PrintMatrix ( double** pTab, int nSize ); // wysiwetla macierz
void MakeComplementaryMatrix ( double** pMatrix, double** pInvertedMatrix, int nSize );

#endif


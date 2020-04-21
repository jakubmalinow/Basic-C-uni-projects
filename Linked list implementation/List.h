#ifndef LIST_H
#define LIST_H

#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include "global.h"

typedef int( *pointer_to_compare )( const void*, const void * );

typedef struct tagListItem
{
	LISTINFO* m_pInfo;// o
	tagListItem* m_pNext;
} ListItem;


ListItem* CreateList(); //tworzy pusty element i zwraca jego adres (poczatek listy)
int isEmpty( ListItem* p ); //pusta zwraca 1
ListItem* Front( ListItem* p );
void RemoveFront( ListItem* p ); // funkcja usuwa pierwszy element
void Remove( ListItem* pAfter );
void Insert( ListItem* pAfter, LISTINFO* pInfo );
void FreeList( ListItem* p );
void DelList( ListItem** p );
void InsertFront( ListItem* p, LISTINFO* pInfo );
ListItem* Find( ListItem *p, const void* value, ListItem** previous, pointer_to_compare compare );
void SortList( ListItem* p, pointer_to_compare compare );
void PrintList( ListItem* p);
#endif
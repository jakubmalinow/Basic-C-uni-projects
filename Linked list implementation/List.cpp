#include "List.h"

ListItem* CreateList() 
{
	ListItem* pHead = (ListItem*)malloc( sizeof( ListItem ) ); //alokacja pamieci na element listy
	if( pHead == NULL )
	{
		perror( "Unable to allocate memory (CreateList)" );
		return NULL;
	}
	pHead->m_pInfo = NULL;
	pHead->m_pNext = NULL; //ustawienie wskaznika pNext na null, bo nie mamy jeszcze nastepnego elementu
	return pHead; //zwracamy adres poczatku listy
}

int isEmpty( ListItem* p )
{
	return p->m_pNext == NULL; //pusta = 1 , niepusta = 0
}

ListItem* Front( ListItem* p ) //zwraca wskaznik na pierwszy wlasciwy element listy
{
	if( isEmpty( p ) )
	{
		perror( "List is empty, unable to return pointer to first element (Front)" );
		return NULL;
	}
	return p->m_pNext;
}

void InsertFront( ListItem* pHead, LISTINFO* pInfo )
{
	Insert( pHead, pInfo ); //nie powielamy kodu
}

void Insert( ListItem* pAfter, LISTINFO* pInfo )
{
	if( pAfter == NULL )
	{
		perror( "pointer is NULL, propably unable to find element to insert after (Insert)" );
		return;
	}
	ListItem* pTemp = (ListItem*)malloc( sizeof( ListItem ) ); //alokacja pamieci na nowy element
	if( pTemp == NULL )
	{
		perror( "Unable to allocate memory for temporary pointer (Insert)" );
		return;
	}
	
	pTemp->m_pInfo = pInfo; //przewiazanie wskaznikow
	pTemp->m_pNext = pAfter->m_pNext;
	pAfter->m_pNext = pTemp;
}

void Remove( ListItem* pAfter )
{
	if( pAfter == NULL )
	{
		perror( "element doesn't exist (Remove)" );
		return;
	}

	ListItem* temp = pAfter->m_pNext; //musimy zachowaæ tymczasowy wskaznik na usuwany element
	if( temp == NULL )
	{
		perror( "Unable to allocate memory for temporary pointer (Remove)" );
		return;
	}
	//if( pAfter->m_pNext != NULL ) //je¿eli jest to ostatni element listy, nie ma kolejnego elementu ktory bysmy usuneli
	{
		pAfter->m_pNext = temp->m_pNext; //przeiwazanie wskaznikow
		free( temp->m_pInfo );//zwaleniam pamiec z informacja
		free( temp ); //zwolnienie pamieci
	}
}

void RemoveFront( ListItem* pHead )
{
	Remove( pHead ); //nie powielamy kodu
}

void PrintList( ListItem* pElement)
{
	if( (pElement == NULL) || isEmpty( pElement ) )
	{
		perror( "List is empty, or pointer is null, can't print (PrintList)" );
		return;
	}
	pElement = Front( pElement );
	while(pElement!=NULL)
	{
		printf( "%d ", pElement->m_pInfo->nKey);
		if( pElement->m_pNext == NULL ) break;
		pElement = pElement->m_pNext;		
	}
	printf( "\n" );

}

ListItem* Find( ListItem *pElement, const void* value, ListItem** previous, pointer_to_compare compare ) //zwraca wskaznik na szukany element ,i ustawia previous na poprzedni
{
	if( isEmpty( pElement ) )
		return NULL;

	while( pElement != NULL)//jezeli pElement = null, to znaczy ze przeszukalismy cala liste
	{
		*previous = pElement; //ustawiam na head (jezeli szukany element jest pierwszy, previious bedzie wskazywal head)
		pElement = pElement->m_pNext; //ustawiam na pierwszy wlasciwy element listy
		
		if( !compare( pElement->m_pInfo, value ) )//wysylam wskaznik na obecny element list i na szukany
			return pElement; //zwracam wskaznik na znaleziony element, prev		 
	}
	// jezeli nie znaleziono, wskaznik previous nie powinien na nic wskazywac
	return *previous = NULL; //jezeli nie znaleziono
}

void FreeList( ListItem* p )
{
	while( !isEmpty(p) ) //usuwam wszystkie elementy, dopoki lista nie jest pusta
		RemoveFront( p );
}

void DelList( ListItem** p )
{
	FreeList( *p );
	free( *p ); //usuwam te¿ header listy
	*p = NULL;
}

void SortList( ListItem* pList, pointer_to_compare compare )
{
	//if( p==NULL )
		//return; //jezeli lista jest pusta, nie wchodzimy w algorytm


	ListItem* p = pList;
	while( p->m_pNext != NULL ) //jezeli p wskazuje na nulla to tablica jest posortowana
	{
		ListItem* min = p;//ustaiwam iterator na pierwszy element
		ListItem* iterator = p->m_pNext; //ustawiam minimum na pierwszy element sprawdzanego zakresu

		while( iterator->m_pNext != NULL ) //jezeli it=null to skonczylismy sprawdzac zakres
		{
			if( compare( min->m_pNext->m_pInfo, iterator->m_pNext->m_pInfo ) == 1 )
			{
				min = iterator; //min bedzie wskazywal na element poprzedzaj¹cy najmnieszy element
			}
			iterator = iterator->m_pNext;
		}
		if( min != p)
		{
			iterator = min->m_pNext->m_pNext; //zamiast tworzyc wskaznik temp mozna uzyc iteratora
			min->m_pNext->m_pNext = p->m_pNext; //przewi¹zuje najmniejszy element na poczatek
			p->m_pNext = min->m_pNext; //przewi¹zuje p aby wskazywalo na najmniejszy element (ktory ma byc na poczatku)
			min->m_pNext = iterator;	//doczepiam koncowke listy
		}
		p = p->m_pNext; //zmniejszam sprwadzany zakres z kazd¹ iteracja
		//iterator = p; //ustawiam iterator na poczatek sprawdzanego zakresu
	}
}




#include <stdio.h>
#include <stdlib.h>

// vytvorenie uzla
typedef struct node 
{
    int data;
    struct node *next;
}NODE;

typedef struct list 
{
    NODE* head;
}LIST;

/*******************************************************************/
//
// POPIS: 
//      Funkcia, ktora prida uzol na zaciatok zoznamu
// PARAMETRE:
//      list - adresa zretazeneho zoznamu
//      value - hodnota uzla, ktory pridame na zaciatok zoznamu
// NAVRATOVA HODNOTA:
//      void
//
/*******************************************************************/
void prependNode(LIST* list, int value) 
{
    if (list == NULL) 
 	{
 		return; // ak zoznam neexistuje	
	}
    
    NODE* s = (NODE*)malloc(sizeof(NODE)); // alokujeme novy uzol
    
    s->data = value;
    s->next = list->head; // novy uzol ukazuje na aktualny zaciatok zoznamu
    list->head = s; // aktualizacia zaciatku
}

/*******************************************************************/
//
// POPIS: 
//      Funkcia, ktora prida uzol na koniec zoznamu
// PARAMETRE:
//      list - adresa zretazeneho zoznamu
//      value - hodnota uzla, ktory pridame na koniec zoznamu
// NAVRATOVA HODNOTA:
//      void
//
/*******************************************************************/
void appendNode(LIST* list, int value) 
{
    if (list == NULL) 
 	{
 		return; // ak zoznam neexistuje	
	}
    
    NODE* s = (NODE*)malloc(sizeof(NODE)); // alokujeme novy uzol
    
    s->data = value;
    s->next = NULL; // nastavime nasledovnika na NULL
    
    if (list->head == NULL) // ak je zoznam prazdny
    {
        list->head = s; // novy uzol sa stane zaciatkom
        return;
    }
    
    NODE* tmp = list->head;
    
    while (tmp->next != NULL) // prechod zoznamom az nakoniec
	{ 
        tmp = tmp->next;
    }
    tmp->next = s; // pripojenie noveho uzla na koniec
}

/*******************************************************************/
//
// POPIS: 
//      Funkcia, ktora vypise cely zretazeny zoznam
// PARAMETRE:
//      list - adresa zretazeneho zoznamu
// NAVRATOVA HODNOTA:
//      void
//
/*******************************************************************/
void printList(LIST* list) 
{
    if (list == NULL) 
 	{
 		return; // ak zoznam neexistuje	
	}
    
    NODE* tmp = list->head;
    
    while (tmp != NULL) // prechod zoznamom
	{ 
        printf("%i --> ", tmp->data); // vypis datovej casti kazdeho uzla
        tmp = tmp->next;
    }
    
    printf("NULL\n");
}

/*******************************************************************/
//
// POPIS: 
//      Funkcia, ktora vyhlada uzol s hodnotou val (Pozor: funkcia vrati prvy vyskyt uzla s hodnotou val)
// PARAMETRE:
//      list - adresa zretazeneho zoznamu
//      val - hodnota uzla, ktory hladame
// NAVRATOVA HODNOTA:
//      adresa hladaneho uzla, v pripade chyba sa vrati NULL
//
/*******************************************************************/
NODE* findNode(LIST* list, int val) 
{
 	if (list == NULL) 
 	{
 		return NULL; // ak zoznam neexistuje	
	}
    
    NODE* tmp = list->head;
    
    while (tmp != NULL) // prechod zoznamom
	{ 
        if (tmp->data == val) // nasli sme hladany uzol
		{
			return tmp; // vraciame najdeny uzol	
		} 
            
        tmp = tmp->next;
    }
    
    return NULL; // ak sme nic nenasli, vratime NULL
}

/*******************************************************************/
//
// POPIS: 
//      Funkcia, ktora najde predchodcu uzla n
// PARAMETRE:
//      list - adresa zretazeneho zoznamu
//      n - adresa uzla, ktoreho predchodcu hladame
// NAVRATOVA HODNOTA:
//      Adresa predchodcu uzla n, v pripade chyby sa vrati NULL
//
/*******************************************************************/

NODE* findPred(LIST* list, NODE* n) 
{
    if (list == NULL) 
	{
		return NULL; // ak zoznam neexistuje	
	}

    if (list->head == NULL || list->head->next == NULL) 
	{
		return NULL; // ak je zoznam prazdny alebo obsahuje len 1 uzol, vtedy neexistuje predchodca	
	}
	
    NODE* tmp = list->head;
    
    while (tmp->next != NULL) // prechod zoznamom a hladanie predchodcu uzla n
	{ 
        if (tmp->next == n) 
		{
            return tmp; // nasli sme predchodcu uzla n a vratime ho
        }
        tmp = tmp->next;
    }
    
    return NULL; // v zozname sme nenasli uzol n
}

/*******************************************************************/
//
// POPIS: 
//      Funkcia, ktora vymaze uzol s hodnotou val
// PARAMETRE:
//      list - adresa zretazeneho zoznamu
//      val - hodnota uzla, ktory sa chystame vymazat
// NAVRATOVA HODNOTA:
//      void
//
/*******************************************************************/

void deleteNode(LIST* list, int val) 
{
    if (list == NULL) 
	{
		return; // ak zoznam neexistuje	
	}
	
    if (list->head == NULL) 
	{
		return; // ak je zoznam prazdny	
	}
	
    if (list->head->next == NULL && list->head->data == val) // ak zoznam obsahuje len 1 uzol
	{ 
        free(list->head); // de-alokacia uzla
        list->head = NULL; // nastavenie na NULL, aby sa zo smerniku nestal tzv. dangling pointer
        return;
    }
    
    NODE* tmp = list->head;
    NODE* pred = NULL;
    
    while (tmp != NULL) //prechod zoznamom
	{ 
        if (tmp->data == val) // hladanie uzla, ktory chceme vymazat
		{ 
            if (tmp == list->head) // ak je hladany uzol zaciatkom zoznamu
			{ 
                list->head = list->head->next;
                free(tmp);
                return;
            }
            
            // ak je hladany uzol niekde v strede alebo na konci zoznamu
            pred = findPred(list, tmp); // musime najst predchodcu a prepojit ho s nasledovnikom uzla, ktory sa chystame vymazat
            
            if (pred != NULL) 
			{
                pred->next = tmp->next;
                free(tmp);
                return;
            }
        }
        
        tmp = tmp->next;
    }
}

/*******************************************************************/
//
// POPIS: 
//      Funkcia, ktora vymiena dva uzly v zretazenom zozname
// PARAMETRE:
//      list - adresa zretazeneho zoznamu
//      a - adresa uzla A
//      b - adresa uzla B
// NAVRATOVA HODNOTA:
//      void
//
/*******************************************************************/

void swapNodes(LIST* list, NODE *a, NODE *b) 
{
    if (list == NULL) 
	{
		return; // ak je zoznam prazdny	
	}
	
    if (list->head == NULL || a == NULL || b == NULL) // ak je zoznam prazdny alebo nexxistuje jeden z uzlov a,b
	{ 
        printf("\n Nieco nie je v poriadku \n");
        return;
    }
    
    NODE * pre_a = NULL, *pre_b = NULL; // adresy predchodcov uzlov a,b
    NODE * tmp = list->head;

    // trivialne vyhladanie predchodcov uzlov a,b
    while (tmp != NULL) 
	{
        if ((tmp)->next == a) // nasli sme predchodcu uzla a
        {
        	pre_a = tmp;	
		}
            
        if ((tmp)->next == b) // nasli sme predchodcu uzla b
        {
        	pre_b = tmp;
		}
            
        if (pre_a && pre_b) // ak sme nasli obidvoch predchodcov, nemusime uz dalej hladat
    	{
    		break;	
		}
            
        tmp = tmp->next;
    }

    // 1. krok - vymena predchodcov uzlov a,b
    if (pre_a)
    {
    	pre_a->next = b;	
	}
        
    if (pre_b)
    {
    	pre_b->next = a;
	}    

    // 2. krok - vymena nasledovnikov uzlov a,b
    NODE* temp = NULL;
    temp = a->next;
    a->next = b->next;
    b->next = temp;

    // zmena zaciatku zoznamu, ak niektory z vymienanych uzlov bol zaciatkom
    if (list->head == a) 
	{
        list->head = b;
        return;
    }
    
    if (list->head == b) 
	{
        list->head = a;
        return;
    }
}

/*******************************************************************/
//
// POPIS: 
//      Funkcia, ktora vymaze (de-alokuje) cely zretazeny zoznam
// PARAMETRE:
//      list - adresa zretazeneho zoznamu
// NAVRATOVA HODNOTA:
//      void
//
/*******************************************************************/

void deleteList(LIST* list) 
{
    if (list == NULL) 
    {
    	return; // ak zoznam neexistuje	
	}
	
    NODE* tmp = list->head;
    NODE* toDelete = NULL;
    while (tmp != NULL) // prechod zoznamom
    {
        toDelete = tmp; // odkladame smernik na aktualny uzol, ktory sa chystame de-alokovat
        tmp = tmp->next; // posun o uzol dopredu
        free(toDelete); // samotna dealokacia aktualneho uzla
    }
    
    list->head = NULL; // po de-alokacii nastavime zaciatok zoznamu na NULL
}

// Bouble sort
void bubbleSortList(LIST* list)
{
    if (list == NULL) return;
    if (list->head == NULL) return;

    NODE* tmp = list->head;     // odkladam zaciatok
    NODE* pokial = NULL;        // pomocny uzol, sluzi na zapamatanie si uzlu, po ktory sme presli v predchadzajucej iteracii ...
                                // ... meni sa nasledovne NULL, POSLEDNY, POSLEDNY - 1, POSLEDNY - 2, POSLEDNY - 3,......atd.
    NODE* tmp2 = NULL;          // pomocny uzol pri swapovani

    while (list->head->next != pokial)           	// osetrenie, aby som neisiel zbytocne posledny krat cez cely zoznam, nakolko uz je utriedeny po N-1 prechodoch
    {
        while (tmp->next != pokial)            		// v kazdej iteracii prechadzame vzdy o 1 uzol menej krat, mame uz istotu ze na konci zoznamu sa hromadia usporiadane prvky: to je myslienka bubbleSort-u
        { 
            if (tmp->data > tmp->next->data)   		// ak je LEFT < RIGHT vtedy urobim swap(), triedime zostupne
            {
                tmp2 = tmp->next;                	// odlozim nasledovnika uzla LEFT
                swapNodes(list, tmp, tmp->next);	// urobim swap()
                tmp = tmp2;                     	// po swape sa musim dostat na tu istu poziciu ako pred swapom
            }
            
            tmp = tmp->next;                 		// posuniem sa o jeden uzol dopredu
        }
        
        pokial = tmp;                           	// po jednom prechode zoznamom aktualizujem uzol POKIAL (ten sa posuva stale z konca zoznamu dopredu)
        tmp = list->head;                        	// nastavim sa znova na zaciatok zoznamu
    }
}

// Insertsort + pridavna funkcia
void insertNodeBefore(LIST* list, NODE* _insert, NODE* _target) 
{
    if (list == NULL) // ak je zoznam prazdny
	{
		return; 	
	}
	
    if (list->head == NULL || _insert == NULL || _target == NULL) // ak je zoznam prazdny alebo niektory zo vstupnych uzlov neexistuje
    {
    	return;	
	}
        
    if (_target == list->head) // ak ideme vkladat pred prvy uzol zoznamu
	{ 
        _insert->next = list->head;
        list->head = _insert;
        return;
    }
    
    NODE* predchodca = findPred(list, _target); // najdeme predchodcu uzla _target
    
    if (predchodca != NULL) 
	{
        predchodca->next = _insert;
        _insert->next = _target;
    }
}

void insertionSortList(LIST* list) 
{
    if (list == NULL) 
    {
    	return; // ak zoznam neexistuje	
	}
	
    if (list->head == NULL)
    {
    	return; // ak je zoznam prazdny
	}
	
    if (list->head->next == NULL)
    {
    	return; // ak je v zoznam len 1 uzol
	}
	
    NODE* firstUnsorted = list->head->next;
    NODE* lastSorted = list->head;
    NODE* tmp = NULL;

    while (firstUnsorted) // pokial existuju uzly v nezotriedenej casti zoznamu 
	{ 
        tmp = list->head;
        
        while (tmp != firstUnsorted) // pridame aktualny uzol na spravnu poziciu do zotriedenej casti zoznamu
		{ 
            if (tmp->data > firstUnsorted->data) 
			{
                lastSorted->next = firstUnsorted->next;
                insertNodeBefore(list, firstUnsorted, tmp);
                break;
            }
            
            tmp = tmp->next;
        }
        
        if (tmp == firstUnsorted) // ak sa nevykonal ani jeden swap
		{ 
            lastSorted = firstUnsorted; // posuniem hranice zotriedenej casti zoznamu
            firstUnsorted = firstUnsorted->next; // posuniem sa na dalsi nezotriedeny uzol
        }
    }
}

int main()
{
	int i = 0;
    srand((unsigned int)time(NULL));

    printf("BubbleSort: Zretazeny zoznam\n-----------------------------\n");
    LIST list;
    list.head = NULL;

    // pridanie 10 uzlov do zoznamu
    for (i; i < 10; i++) 
	{
        prependNode(&list, rand() % 100);
    }

    // vypis neusporiadaneho zoznamu
    printf("Neusporiadany zoznam:\t");
    printList(&list);
	
	/******* TYP SORT. ALG. ********/
    bubbleSortList(&list);
    //insertionSortList(&list);
    /*******************************/

    // vypis usporiadaneho zoznamu
    printf("Usporiadany zoznam:\t");
    printList(&list);

    deleteList(&list);

    return 0;
}

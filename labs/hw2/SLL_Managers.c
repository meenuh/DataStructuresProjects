/********************************************************************************
** CIS 15C
***************
**
**  SLL_Managers.c
**
*************************************************

****************************************
**
**  Written By: Mina Yi
**  Date: Oct. 25, 2011
**
********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#include "SLL.h"

/*================buildManager=================================
buildManager opens a file and reads it into a doubly linked
list. It creates the header node and the two dummy nodes.
It returns the list (pList).
*/
LIST *buildManager(void)
{
	FILE* fptr;
	LIST *pList;
	NODE *pCur;
	COUNTRY temp;

	int found;
	char input[81];

	fptr = fopen("countries.txt","r");

    pList = (LIST *)malloc(sizeof(LIST));
    if(pList == NULL)
        exit(1);

    pList->count = 0;

    pList->head = (NODE *)malloc(sizeof(NODE));
    pList->tail = (NODE *)malloc(sizeof(NODE));
    pList->head->data = NULL;
    pList->tail->data = NULL;

    if(pList->head == NULL || pList->tail == NULL)
        exit(1);

    pList->head->forw = pList->tail;
    pList->tail->back = pList->head;
    pList->head->back = NULL;
    pList->tail->forw = NULL;


	while((fgets(input,sizeof(input), fptr)))
	{
		strncpy(temp.ID, input,2);
		found = searchList(pList, &pCur, temp.ID);
		if (!found)
		{
			temp = stringToCountry(input);
			insertNode(pList, pCur, temp);
		} 
	}

	fclose(fptr);

	return pList;
}

/* ============================== processListManager ====================
	Process user's option by calling appropriate functions.
*/

void processListManager (LIST *pList)
{
	char option;
	do
	{  
		printMenu();	
		option = getOption();
		switch(option)
		{
            case 'L' : searchByLetter (pList);
                       break;
		    case 'P' : printList (pList);
				       break;
            case 'B' : printBack (pList);
                       break;
		    case 'S' : searchManager (pList);
				       break;
		    case 'I' : insertManager (pList);
				       break;
		    case 'D' : deleteManager (pList);
				       break;
		    case 'M' : printMenu ();
				       break;
		    case 'E' : printf("End of processing!\n");
                       break;
            default  : break;
		} 
	} while (option != 'E');
} 

/*
 * searchByLetter takes in the list called pList. It searches the
 * doubly linked list for countries beginning with the same letter
 * that the user enters. It then prints out the list of countries 
 * that meet the criteria. It does not return anything.
 */
void searchByLetter(LIST *pList)
{
    char letter;
    int found = 0;
    NODE *pCur = pList->head->forw;

    printf("Enter the first letter for the capital you'd like to search for.\n");
    scanf(" %c", &letter);
    FLUSH;
    letter = toupper(letter);

    printf("========================================================================\n");
    printf("%-5s %-20s %-25s %-25s\n", "ID", "Country", "Capital", "Population");
    printf("========================================================================\n");

    while(pCur->data)
    {
        if(*pCur->data->cap == letter)
        {
            found = 1;
            printf("%-5s %-20s %-25s", 
                pCur->data->ID, pCur->data->country, pCur->data->cap);
            formatPop(pCur->data->pop);
            putchar('\n');
        }
        pCur = pCur->forw;
    }

    if(!found)
        printf("No capital with that letter exists.\n");

    printf("========================================================================\n");
}

/*===========searchManager======================
  Manager to search data. It does not return 
  anything. It prints whether it was found or not.
  If it was found it calls printCountry to print
  the appropriate information.
*/

void  searchManager(LIST *pList)
{
	NODE *pCur;
	char target[3];
	int  found;

    getCountryID(target);
	found = searchList(pList, &pCur, target);
	if (found)
	{    
		printf("%s was found!\n", target);
		printCountry(pCur);
	}	
	else 
		printf("%s was not found!\n", target);
    
	return;
}//searchManager

/*===========deleteManager======================
  Manager to delete data
  deleteManager takes in the list pList and 
  it deletes the node specified by the user.
  It does not return anything.
*/
void deleteManager(LIST *pList)
{
	NODE *pCur;
	int found;
	char target[3];

    getCountryID(target);
	found = searchList(pList, &pCur, target);
	if(found)
	{
		printf("%s was found and it will be deleted\n", target);
		printCountry(pCur);
		deleteNode(pList, pCur);
		printf("Done deleting!\n");
	}
	else 
	{
		printf("%s was not found\n", target);
	} 

}

/*===========insertManager=================================
  Manager to insert the data
  takes in the list pList. It inserts data into the 
  appropriate position in the doubly linked list. This does
  not return anything.
*/
void insertManager(LIST *pList)
{
	COUNTRY temp;
	NODE *pCur;
	int found;
	char id[3];
	char input[200];

    getCountryID(id);
	found = searchList(pList, &pCur, id);
	if(!found)
	{
		printf("%s not found. You can insert new data.\n", id);
        sprintf( input, "%s", id );
		getCountry(input);
		temp = stringToCountry(input);
	    insertNode(pList, pCur, temp);
		printf("Done inserting!\n");
	}
	else 
		printf("%s is already in the list: no duplicates!\n", id);   

}


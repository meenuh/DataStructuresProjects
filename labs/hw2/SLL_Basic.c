/********************************************************************************
** CIS 15C
***************
**
** SLL_Basic.c 
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

/*==============insertNode===============================
  This function inserts a single node into a doubly linked
  list. It takes in pList, the current position and the 
  item to be inserted. It does not return anything.
*/
void insertNode(LIST* pList, NODE* pCur, COUNTRY item)
{
	NODE* pNew;

    pNew = (NODE *)malloc(sizeof(NODE));
    if(pNew == NULL)
        exit(1);
    
    pNew->data = (COUNTRY *)malloc(sizeof(COUNTRY));
    if(pNew->data == NULL)
        exit(1);

	memcpy(pNew->data, &item, sizeof(COUNTRY));

    pNew->forw = pCur;
    pNew->back = pCur->back;
    pCur->back->forw = pNew;
    pCur->back = pNew;

    pList->count++;
}

/*=============deleteNode================================
  This function deletes a single node from the doubly
  linked list. It takes the list, pList, and a pointer
  to the current node. It frees all memory for the node
  and decrements the count.
*/
void deleteNode(LIST *pList, NODE* pCur)
{
    pCur->back->forw = pCur->forw;
    pCur->forw->back = pCur->back;;
	
	free(pCur->data->country);
	free(pCur->data->cap);
    free(pCur->data);
	free(pCur);

    pList->count--;
}

/*================searchList=================================
  Given key value, finds the location of a node
    Pre  
		 pCur points to variable for current node
		 target is key being sought
	Post pCur points to first node with >= key
	     -or- null if target > key of last node
		 function returns 1 if found
		                  0 if not found

*/
int searchList(LIST *pList, NODE **pCur, char target[])
{
	int found = 0;

	*pCur = pList->head->forw;
	while ((*pCur)->data  && strcmp(target,(*pCur)->data->ID) > 0)
		*pCur = (*pCur)->forw;
	
    if ((*pCur)->data != NULL && strcmp(target,(*pCur)->data->ID) == 0)
		found = 1;
	return found;
}

/*=========================printList=====================
  Traverse and print a doubly linked list forwards.
    Pre  pList is a valid doubly linked list.
	Post List has been printed
*/
void  printList(LIST *pList)
{
	NODE *pCur = pList->head->forw;

	printf("===================================================================== \n");
	printf("%-5s %-20s %-25s %-25s\n", "ID", "Country", "Capital", "Population");
	printf("===================================================================== \n");

	while(pCur->data)
	{
		printf("%-5s%-20s %-25s", pCur->data->ID, pCur->data->country, 
            pCur->data->cap);
        formatPop(pCur->data->pop);
        putchar('\n');

		pCur = pCur->forw;  	    
	} 
	return;
}

/*
 * printBack takes in the list pList. It prints the doubly
 * linked list backwards.
 */
void  printBack(LIST *pList)
{
	NODE *pCur = pList->tail->back;

	printf("===================================================================== \n");
	printf("%-5s %-20s %-25s %-25s\n", "ID", "Country", "Capital", "Population");
	printf("===================================================================== \n");


	while(pCur->data)
	{
		printf("%-5s%-20s %-25s", pCur->data->ID, pCur->data->country, 
            pCur->data->cap);
        formatPop(pCur->data->pop);
        putchar('\n');

		pCur = pCur->back;
    }
	return;
}



/*===========destroyList======================
  Frees the entire doubly linked list including
  all other allocated memory.
*/
LIST *destroyList (LIST *pList)
{
	NODE* pCur;

	pCur = pList->head->forw;

	while (pCur->data)
	{

	    free(pCur->data->country);
	    free(pCur->data->cap);
        free(pCur->data);
		pCur = pCur->forw;
	    free(pCur->back);
	}

    free(pList->head);
    free(pList->tail);

	free(pList);
	pList = NULL;

	return pList;
}


/*
 *Basic functions for a doubly linked list
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "perry.h"
#include "dLL.h"

LIST *createList()
{
    LIST *list;

    list = (LIST *)malloc(sizeof(LIST));
    if(list)
    {
        list->head = (NODE *)Malloc(sizeof(NODE));
        list->tail = (NODE *)Malloc(sizeof(NODE));
        
        list->head->forw = list->tail;
        list->head->back = NULL;

        list->tail->back = list->head;
        list->tail->forw = NULL;
        
        list->count = 0;
    }
    return list;
}

NODE *searchList(LIST *list, char *toFind)
{
    NODE *mover = list->head->forw;

    while(strcmp(toFind, mover->pcountry->id) > 0)
        mover = mover->forw;

    return mover;
}

NODE *insertList(LIST *list, char *dataPtr)
{
    NODE *new, *current;
    
    current = searchList(list, dataPtr);
    if(strcmp(dataPtr, current->pcountry->id) == 0)
        new = current;
    else
    {
        new = (NODE *)Malloc(sizeof(NODE));
        new->pcountry = (COUNTRY *)Malloc(size(COUNTRY));

        new->forw = current;
        new->back = current->back;
        current->back->forw = new;
        current->back = new;
    }
    return new;
}

int deleteNode(LIST *list, char *toDelete)
{
    int success = 0;
    NODE *current = list->head->forw;

    current = searchList(list, toDelete);
    if(strcmp(toDelete, current->dataPtr) == 0)
    {
        success = 1;
        current->back->forw = current->forw;
        current->forw->back = current->back;
        free(current->dataPtr);
        free(current);
    }
    return success;
}



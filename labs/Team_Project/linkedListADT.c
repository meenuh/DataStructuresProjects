/*	
    This file contains the definitons of the functions to maintain
	and process a linked list:

    Public Functions:
        createList
        addNode
        removeNode
        searchList
        retrieveNode
        emptyList
        fullList
        listCount
        traverse
        destroyList

    Private Functions:
        _insert
        _delete
        _search
*/

#include <stdlib.h>
#include "linkListADT.h"   /* <== public functions */
#include "ADT_hash.h"

#include <stdio.h> //TODO remove

/* private functions */
static int  _insert  (LIST*  pList, void* dataInPtr);
static void _delete  (LIST*  pList, NODE*  pPre, NODE*  pLoc, void** dataOutPtr);
static int  _search  (LIST*  pList, NODE** pPre, NODE** pLoc, void*  pArgu);


/* 
    =================================================
    ============== Public Functions =================
    =================================================
*/

/*	=============== createList ==============
	Allocates dynamic memory for a list head
	node and returns its address to caller
	   Pre    compare is address of compare function 
	          used to compare two nodes.
	   Post   head has allocated or error returned
	   Return head node pointer or null if overflow 
*/
LIST* createList (int (*compare) (void* argu1, void* argu2))
{
//	Local Definitions 
	LIST* list;

//	Statements 
	list = (LIST*) malloc (sizeof (LIST));
	if (list)
	{
	    list->head    = NULL;
	    list->pos     = NULL;
	    list->rear    = NULL;
	    list->count   = 0;
	    list->compare = compare;
	 } // if 

	return list;
}	// createList 

/*	================== addNode =================
	Inserts data into list.
	   Pre    pList is pointer to valid list
	          dataInPtr pointer to insertion data
	   Post   data inserted or error
	   Return -1 if overflow
	           0 if successful
	           1 if dupe key
*/
int addNode (LIST* pList, void* dataInPtr)
{
//	Local Definitions 
	int  found;
	int  success;
	
	NODE* pPre;
	NODE* pLoc;
	
//	Statements 
	found = _search (pList, &pPre, &pLoc, dataInPtr);

	// Duplicate keys not allowed 
    if (found)
	   return 1;

	success = _insert (pList, dataInPtr);

	// Overflow 
	if (!success)
	   return -1;

	return 0;
}	// addNode 

/*================== adjustList =================
 * adjusts the linked list to be called whenever
 * there is a search in the linked list.
 *
 * Pre:  pList pointer to a valid list
 *       key pointer to key that was searched for.
 * Post: pointers adjusted and searched moved to
 *       front of list or return without modifying
 *       (means searched was already in front)
 */
void adjustList(LIST *pList, void *key)
{
    NODE *found, *pPre;

    _search(pList, &pPre, &found, key);

    if (found == pList->head)
        return;
    
    found->link = pList->head;
    pList->head = found;

    if (found == pList->rear)
    {
        pList->rear = pPre;
        pPre->link = NULL;
    } 
}
/*	================= removeNode ================ 
	Removes data from list. 
	   Pre    pList pointer to a valid list
	          keyPtr pointer to key to be deleted
	          dataOutPtr pointer to data pointer
	   Post   Node deleted or error returned.
	   Return false not found; true deleted
*/
int removeNode  (LIST*  pList, void*  keyPtr, void** dataOutPtr)
{
//	Local Definitions 
	int  found;
	
	NODE* pPre;
	NODE* pLoc;
	
//	Statements 
	   _delete (pList, NULL, pList->head, dataOutPtr);
	
	return found;
}	// removeNode 


/*	================== searchList ================= 
	Interface to search function. 
	   Pre    pList pointer to initialized list.
	          pArgu pointer to key being sought
	   Post   pDataOut contains pointer to found data
	     -or- NULL if not found
	   Return boolean true successful; false not found 
*/
void *searchList (LIST*  pList, void* pArgu)
{
//	Local Definitions 
	NODE* found;	
	NODE* pPre;
	NODE* pLoc;

//	Statements 
	_search (pList, &pPre, &pLoc, pArgu);
	if (pLoc)
	    pLoc = pLoc->dataPtr;
	else
	    pLoc = NULL;
	return pLoc;
}	// searchList 


/*	================== retrieveNode ================ 
	This algorithm retrieves data in the list without
	changing the list contents. 
	   Pre    pList pointer to initialized list.
	          pArgu pointer to key to be retrieved
	   Post   Data (pointer) passed back to caller
	   Return boolean true success; false underflow
*/
int  retrieveNode (LIST*  pList, void*  pArgu, void** dataOutPtr)
{
//	Local Definitions 
	int  found;
	
	NODE* pPre;
	NODE* pLoc;
	
//	Statements 
	found = _search (pList, &pPre, &pLoc, pArgu);
	if (found)
	{
	    *dataOutPtr = pLoc->dataPtr;
	    return 1;
	} // if 

	*dataOutPtr = NULL;
	return 0;
}	// retrieveNode 

/*	================= emptyList ================
	Returns boolean indicating whether or not the
	list is empty
	   Pre    pList is a pointer to a valid list 
	   Return boolean true empty; false list has data 
*/
int emptyList (LIST* pList) 
{
//	Statements 
	return (pList->count == 0);
}	// emptyList 

/*	================== fullList =================
	Returns boolean indicating no room for more data.
	This list is full if memory cannot be allocated for
	another node. 
	   Pre    pList pointer to valid list 
	   Return boolean true if full
	                  false if room for node 
*/
int fullList (LIST* pList) 
{
//	Local Definitions 
NODE* temp;

//	Statements 
	if ((temp = (NODE*)malloc(sizeof(*(pList->head)))))
	   {
	    free (temp);
	    return 0;
	   } // if 

	// Dynamic memory full 
	return 1;

}	// fullList 

/*	================== listCount ==================
	Returns number of nodes in list.
	   Pre    pList is a pointer to a valid list
	   Return count for number of nodes in list
*/
int listCount(LIST* pList) 
{
//	Statements 

	return pList->count; 
	
}	// listCount 

/*	================== traverse =================
	Traverses a list. Each call either starts at the
	beginning of list or returns the location of the 
	next element in the list.
	   Pre    pList       pointer to a valid list
	          fromWhere   0 to start at first element
	          dataPtrOut  address of pointer to data
	   Post   if more data, address of next node 
	   Return true node located; false if end of list
*/
int traverse (LIST*  pList,
              int    fromWhere,
              void** dataPtrOut)
{
//	Statements 
	if (pList->count == 0)
	    return 0;

	if (fromWhere == 0)
	   {
		 //Start from first node 
	    pList->pos  = pList->head;
	    *dataPtrOut = pList->pos->dataPtr;
	    return 1;
	   } // if fromwhere 
	else
	   {
	    // Start from current position 
	    if (pList->pos->link == NULL)
	        return 0;
	    else
	       {
	        pList->pos  = pList->pos->link;
	        *dataPtrOut = pList->pos->dataPtr;
	        return 1;
	       } // if else 
	   } // if fromwhere else 
}	// traverse 

/*	================== destroyList =================
	Deletes all data in list and recycles memory
	   Pre    List is a pointer to a valid list.
	   Post   All data and head structure deleted
	   Return null head pointer
*/
LIST* destroyList (LIST* pList) 
{
//	Local Definitions 
	NODE* deletePtr;

//	Statements 
	if (pList)
	   {
	    while (pList->head) 
       {
            // Now delete node 
            deletePtr    = pList->head;
            pList->head  = pList->head->link; 
            pList->count--;
            free (deletePtr); 
       } // while 
	    free (pList);
	   } // if 
	return NULL;
}	// destroyList 

/* 
    =================================================
    ============== Private Functions ================
    =================================================
*/
/*	================== _search =================
	Searches list and passes back address of node 
	containing target and its logical predecessor.
	   Pre    pList pointer to initialized list 
	          pPre  pointer variable to predecessor
	          pLoc  pointer variable to receive node
	          pArgu pointer to key being sought
	   Post   pLoc points to first equal/greater key 
	     -or- null if target > key of last node
	          pPre points to largest node < key
	     -or- null if target < key of first node
	   Return boolean true found; false not found 

*/
static int _search (LIST*  pList, NODE** pPre, NODE** pLoc,  void*  pArgu)
{
//	Macro Definition 
#define COMPARE      ( ((* pList->compare) (pArgu, (*pLoc)->dataPtr)) )

//	Local Definitions 
	int result;
	
//	Statements 
	*pPre  = NULL;
	*pLoc  = pList->head;

    // Empty Linked List
	if (pList->count == 0)
	    return 0;

	while ( *pLoc && (result = COMPARE) != 0 )
	{
	    // Have not found search argument location 
	    *pPre = *pLoc;
	    *pLoc = (*pLoc)->link;
	} // while 
	
	// argument found--success 
	if (result == 0)
	   return 1;
	else
	   return 0;
}	// _search 

/*	================= _delete ================ 
	Deletes data from a list and returns 
	pointer to data to calling module.
	   Pre    pList pointer to valid list.
	          pPre  pointer to predecessor node
	          pLoc  pointer to target node
	          dataOutPtr pointer to data pointer
	   Post   Data have been deleted and returned 
	          Data memory has been freed
*/
void _delete (LIST* pList, NODE*  pPre,
              NODE* pLoc,  void** dataOutPtr)
{
//	Statements 
	*dataOutPtr = pLoc->dataPtr;
	if (pPre == NULL)
	   pList->head = pLoc->link;

	(pList->count)--;
	free (pLoc);

	return;
}	// _delete 

/*	=================== _insert ================== 
	Inserts data pointer into a new node.
	   Pre    pList pointer to a valid list 
	          pPre  pointer to data's predecessor 
	          dataInPtr data pointer to be inserted 
	   Post   data have been inserted in sequence 
	   Return boolean, true  if successful, 
	                   false if memory overflow 
*/
static int _insert (LIST* pList, void* dataInPtr)
{
//	Local Definitions 
	NODE* pNew;

//	Statements 
	if (!(pNew = (NODE*) malloc(sizeof(NODE))))
	   return 0;

	pNew->dataPtr   = dataInPtr; 
	pNew->link      = NULL; 
 
    pNew->link       = pList->head;
    pList->head      = pNew;
    if (pList->count == 0)
       pList->rear = pNew;
	(pList->count)++;
	return 1;
}	// _insert 

#include <stdlib.h>
#include <stdio.h>
#include "linkListADT.h"
#include "ADT_hash.h"


/*================ hash_create ===================
 * Allocates memory for the hash table 
 * header
 * Pre:  - hashFunction is address of hashing
 *         function to be used to insert/search
 *         the hash table. 
 *       - size is the size of the table to be 
 *         allocated.
 *       - compare is a pointer to a compare 
 *         funcion used for search and delete.
 *         (to check if what is found is valid)
 * Post: head and table allocated and initialized
 *       appropriately. Returns NULL if malloc 
 *       fails
 */

HASH *hash_create(int size, int (*hashFunction)(void *key), 
                    int (*compare)(void *data, void *searchKey))
{
    HASH *hash;
    int i;

    hash = (HASH *)malloc(sizeof(HASH));
    if(!hash) return NULL;
    
    hash->size = size;
    
    hash->table = (HASH_ITEM *)calloc(size, sizeof(HASH_ITEM));
    if(!(hash->table)) return NULL;

    hash->hashFunction = hashFunction;
    hash->compare = compare;
    hash->maxLinkedList = 0;
    hash->fillCount = 0;

    for(i = 0; i < size; i++)
    {
        hash->table[i].list = NULL;
        hash->table[i].dataPtr = NULL;
        //hash->table[i].count = 0;
    }
    return hash;
}

/*================ hash_insert ===================
 * inserts data into the hash table 
 * Pre:  hash, key and dataPtr are passed.
 * Post: data from user is placed into the table
 *       or into a linked list if there is a 
 *       collision
 */

void hash_insert(HASH *hash, void *key, void *dataPtr)
{
    int addr;

    addr = hash->hashFunction(key);
    h_insert(hash, addr, dataPtr);
}
/*================ h_insert ===================
 * inserts data into hash table or linked list
 * if collision.
 * Pre:  hash, addr and dataPtr are passed. addr
 *       was is the index the hashing function
 *       defined by the user generates.
 * Post: data from user is inserted into table or
 *       into a linked list if there is a 
 *       collision
 */
static void h_insert(HASH *hash, int addr, void *dataPtr)
{
   
   if(hash->table[addr].dataPtr == NULL)
    {
        hash->table[addr].dataPtr = dataPtr;
        hash->fillCount++;
    }else{
        if(hash->table[addr].list == NULL)
            hash->table[addr].list = createList(hash->compare);
        addNode(hash->table[addr].list, dataPtr);
    }
    
    //hash->table[addr].count++;

  //  if((hash->table[addr].count -1) > hash->maxLinkedList)
    //    hash->maxLinkedList = hash->table[addr].count;
}
/*================ hash_search ===================
 * searches for item in hash table.
 * Pre:  takes in hash and key.
 * Post: returns pointer to data if found or NULL
 *       if it does not exist.
 */
void *hash_search(HASH *hash, void *key)
{
    int addr;
    HASH_ITEM *found;
    void *llFind;

    addr = hash->hashFunction(key);
    found = h_search(hash, addr, key);

    if(!found)
        return NULL;

    if(hash->compare(found->dataPtr, key) == 0)
        return found->dataPtr;
    
    adjustList(found->list, key);
    llFind = searchList(hash->table[addr].list, key);
    return llFind;
}

/*================== h_search =====================
 * private function used by hash_search.
 * Pre:  receives hash table, address and key.
 * Post: returns address of element where data was 
 *       found or NULL if the list is empty and if
 *       the item that is being searched for does 
 *       not exist.
 */
static void *h_search(HASH *hash, int addr, void *key)
{

    if(hash->table[addr].dataPtr == NULL)
        return NULL;

    if(hash->compare(hash->table[addr].dataPtr, key) == 0) 
        return &hash->table[addr];

    if(searchList(hash->table[addr].list, key))
        return &hash->table[addr];

    return NULL;
}

/*================== hash_traverse ================
 * traverses the entire hash table.
 * Pre:  receives hash table and a pointer to a 
 *       function.
 * Post: hash table has been traversed and 
 *       processed using a user defined function.
 */
void hash_traverse(HASH *hash, void (*process)(void *dataPtr))
{
    int i, LLcount;
    void *data;

    for(i = 0; i < hash->size; i++)
    {
        if(hash->table[i].dataPtr)
            process(hash->table[i].dataPtr);
        LLcount = 0;
        if(hash->table[i].list)
            while(traverse(hash->table[i].list, LLcount, (void **)&data))
            {
                process(data);
                LLcount++;
            }
    }
}

/*================== hash_delete ===================
 * deletes an item from the hash table
 * Pre:  receives hash table and key.
 * Post: item has been deleted
 */
int hash_delete(HASH *hash, void *key)
{
    int addr;
    
    addr = hash->hashFunction(key);

    return h_delete(hash, addr, key);
}

/*================== h_delete =======================
 * private function used by hash_delete. Deletes data
 * and updates information.
 * Pre:  receives hash table, address and key.
 * Post: data has been appropriately moved. Count 
 *       decremented appropriatly.
 *       return 1 : data removed
 *       return 0 : does not exist, cannot remove
 */
static int h_delete(HASH *hash, int addr, void *key)
{
    HASH_ITEM *hFound;
    void *llFound;

    hFound = h_search(hash, addr, key);
    
    if(!hFound) return 0;
    
    if(hash->compare(hFound->dataPtr, key) == 0)
    {
        if(hFound->list)
        {
            removeNode(hFound->list, key, (void **)&llFound);
            hFound->dataPtr = llFound;
        }else{
            hFound->dataPtr = NULL;
            hash->fillCount--;
        }
    }else{
        adjustList(hFound->list, key);
        removeNode(hFound->list, key, (void **)&llFound);
        free(llFound);
    }
    
    //hFound->count--;
    if(hFound->list && emptyList(hFound->list))
    {
        hFound->list = destroyList(hFound->list);
        hFound->list = NULL;
    }
    return 1;
}

/*================= maxList ===================
 * returns maxLinkedList which is the largest 
 * chain of collisions.
 */
int maxList(HASH *hash)
{
    int i, largest = 0, lcount;

    for(i = 0; i < hash->size; i++)
    {
        if(hash->table[i].list)
        {
            if((lcount = listCount(hash->table[i].list)) > largest)
                largest = lcount;
        }
    }
    return (hash->maxLinkedList = largest);
}

/*================= fill_Count =================
 *  returns the number of elements in the hash
 *  table that have valid data in them.
 *
 */
int fill_Count(HASH *hash)
{   
    return hash->fillCount;
}

/*=============== nodeCount ==================
 * counts total number of nodes in linked list
 * in the table. returns sum. 
 */
int nodeCount(HASH *hash)
{
    int i, nodeCount = 0;

    for(i = 0; i < hash->size; i++)
    {
        if(hash->table[i].list)
            nodeCount += (listCount(hash->table[i].list));
    }
    return nodeCount;
}

/*================ hash_destroy ===============
 * destroys the hash table
 * Pre:  receives hash a pointer to hash table
 * Post: the hash table, header and linked list
 *       have all been freed. 
 *       NULL is returned.
 */
HASH *hash_destroy(HASH *hash)
{
    int i;

    for(i = 0; i < hash->size; i++)
    {
        if(hash->table[i].list)
            hash->table[i].list =  destroyList(hash->table[i].list);
    }

    free(hash->table);
    free(hash);
    
    return NULL;
}

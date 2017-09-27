/*
 * ADT hash function prototypes and declarations.
 *      
 *      Public functions to be used by the user
 *          hash_create
 *          hash_insert
 *          hash_search
 *          hash_delete
 *          hash_traverse
 *          hash_maxList
 *          hash_fill_Count
 *          hash_nodeCount
 *          hash_destroy
 *      Private functions accessed only by ADT
 *          _search
 *          _insert
 *          _delete
 */


typedef struct{
    void *list;
    void *dataPtr;
//    int count;
}HASH_ITEM;

typedef struct{
    int (*hashFunction)(void *key);
    int (*compare)(void *data, void *searchKey);
    int size;
    int maxLinkedList;
    int fillCount;
    HASH_ITEM *table;
}HASH;

//Public functions
HASH *hash_create(int size, int (*hashFunction)(void *key), 
                    int (*compare)(void *data, void *searchKey));
void hash_insert(HASH *hash, void *key, void *dataPtr);
void *hash_search(HASH *hash, void *key);
void hash_traverse(HASH *hash, void (*process)(void *dataPtr));
int hash_delete(HASH *hash, void *key);
int maxList(HASH *hash);
int fill_Count(HASH *hash);
int nodeCount(HASH *hash);
HASH *hash_destroy(HASH *hash);

//Private functions
static void h_insert(HASH *hash, int addr, void *dataPtr);
static void *h_search(HASH *hash, int addr, void *key);
static int h_delete(HASH *hash, int addr, void *key);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ADT_hash.h"
#include "linkListADT.h"

#define SIZE 10


HASH *hash;

typedef struct{
    char key[10];
}STUDENT;

int hashFun(void *key)
{
    char *addr = (char *)key;
    char *mover;
    int sum = 0;

    for(mover = key; *mover; mover++)
        sum += *mover;

    return sum % SIZE;
}

int compare(void *arg1, void *arg2)
{
    char *key = (char *)arg2;
    STUDENT *stu = (STUDENT *)arg1;

    return strcmp(key, stu->key);
}

void print(void *data)
{
    STUDENT* stu = ((STUDENT *)data);

    printf("key in hash: %s\n", stu->key);
}

void lSearch(char *string) 
{
    STUDENT *found = NULL;
    printf("Searching for %s, ", string);
    found = hash_search(hash, string);

    if(found)
        printf("Found: %s\n", found->key);
    else printf("nope.\n");

    return;
}

void lInsert(char *string)
{
    STUDENT *new = NULL;

    new = (STUDENT *)malloc(sizeof(STUDENT));
    strcpy(new->key, string);
    printf("Inserting: %s\n", string);
    hash_insert(hash, new->key, new);
    return;
}

int main()
{
    char search[10];
    
    hash = hash_create(SIZE, hashFun, compare);

    lInsert("4321"); 
    lInsert("1342"); 
    lInsert("1234"); 
    lInsert("1432"); 
    lInsert("5544");
    lInsert("5454");
    // searches
    lSearch("4321"); 
    lSearch("1342");
    lSearch("1234"); 
    lSearch("1234"); 
    lSearch("4321"); 
    lSearch("1432");
    lSearch("4321"); 
    
    strcpy(search, "4321");
    if(hash_delete(hash, search))
        printf("Deleted.\n");
    else printf("No can do.\n");
    
    strcpy(search, "5454");
    if(hash_delete(hash, search))
        printf("Deleted.\n");
    else printf("No can do.\n");

    
    strcpy(search, "5544");
    if(hash_delete(hash, search))
        printf("Deleted.\n");
    else printf("No can do.\n");


    int max, count, node;
    max = maxList(hash);
    count = fill_Count(hash);
    node = nodeCount(hash);
    hash_traverse(hash, print);

    printf("fill: %d max: %d node: %d\n", count, max, node);
    hash = hash_destroy(hash);
    if(!hash)
        printf("destroyd.\n");
    return 0;
}



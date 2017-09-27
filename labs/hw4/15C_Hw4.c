/*****************************************************************************************
** CIS 15C 
** Fall, 2010
******************************************************************************************
**
** Homework 4   		    Hashed Tables and Linked Lists 	                     25 Points
**	
******************************************************************************************

  A variation of Project 19, page 640 - 641 (different input file: BST.TXT)
  
  Hash Size: 10, then 29
  Unique Key: id, a string
  Hash Functions: 1. sum of the characters in the key and modulo-division
                  2. digit extractions and  and modulo-division

  Collision Resolution Method: linked list (sorted by key)
  Hash table: is to be dynamically allocated
 
****************************************************************************
**
** Written by: Mina Yi
**
** Date: Dec 1, 2011
** 
****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <crtdbg.h> // do not remove
#include "linkListADT.h"  

//#define SIZE 10
#define SIZE 29
#define MAXLINE 100

#define FLUSH while(getchar() != '\n')

typedef struct{
	char id[7];
	char *name;
	float gpa;	
} STU;

typedef struct{
	STU   stu;
    int   count;
	LIST  *list;        
} HASH_ITEM; // an element in the hash table

typedef struct{
	int size;          // size of the hash table
	int noStu;         // number of students
	int maxLinkedList; // longest linked list
	HASH_ITEM *table;        
} HASH; 

// Prototype Declarations 
HASH *createHashTable(int size);
void readAndInsert(HASH *hash);
int compare(void *key1, void *key2);
int hashKeySum(char *key);
int digitExtKey(char *key);
char getOption();
void printTable(HASH *hash);
void search(HASH *hash);
void printMenu();
void printEfficiency(HASH *hash);
HASH *destroyHash(HASH *hash);

int main (void)
{
//  Local Definitions 
    HASH *hash;
    char option;

//  Statements 
	printf("\n\n\t\tHomework 4:Hashed Tables and Linked Lists\n\n");
	printf("\t\tThis program reads a list words from a text file\n"
		   "\t\tand inserts them into a hash table \n" );

    hash = createHashTable(SIZE);
    readAndInsert(hash);

    printMenu();
    while((option = getOption()) != 'Q')
    {
        switch(option)
        {
            case 'P': printTable(hash);
                      break;
            case 'S': search(hash);
                      break;
            case 'E': printEfficiency(hash);
                      break;
            case 'M': printMenu();    
                      break;
        }
    }
	printf("\n\t\tEnd of the program!\n" );
    hash = destroyHash(hash);
    //printf( _CrtDumpMemoryLeaks() ? "Memory Leak\n" : "No Leak\n"); // do not remove
	return 0;
} // main 

/*
 * This function takes in a hash. It opens the file and gets the data
 * and inserts into the hash table accordingly.
 */
void readAndInsert(HASH *hash)
{
    FILE *fpin;
    char buffer[MAXLINE];
    char *pID, *pName, *pGpa;
    int addr, count;
    STU *new;

    fpin = fopen("gpa.txt", "r");
    while(fgets(buffer, MAXLINE, fpin))
    {
        (hash->noStu)++;

        pID = strtok(buffer, " ");
        pName = strtok(NULL, ";");
        pGpa = strtok(NULL, "\n");

        addr = hashKeySum(pID);
        //addr = digitExtKey(pID);
        if(hash->table[addr].count == 0)
        {
            hash->table[addr].stu.name = (char *)malloc(strlen(pName) + 1);
            if(!hash->table[addr].stu.name)
                printf("Error with malloc.\n"), exit(101);
            strcpy(hash->table[addr].stu.name, pName);
            strcpy(hash->table[addr].stu.id, pID);
            sscanf(pGpa, "%f", &hash->table[addr].stu.gpa);
            (hash->table)[addr].count++;
        }else{
            new = (STU *)malloc(sizeof(STU));
            if(!new)
                printf("Error with malloc.\n"), exit(101);
            new->name = (char *)malloc(strlen(pName) + 1);
            if(!new->name)
                printf("Error with malloc.\n"), exit(101);
            strcpy(new->id, pID);
            strcpy(new->name, pName);
            sscanf(pGpa, "%f", &new->gpa);
            if(!(hash->table)[addr].list)
            {
                (hash->table)[addr].list = createList(compare);
                addNode((hash->table)[addr].list, new);
                ((hash->table)[addr].count)++;
            }else{
                addNode((hash->table)[addr].list, new);
                ((hash->table)[addr].count)++;
            }
            count = listCount((hash->table)[addr].list);
            if(hash->maxLinkedList < count)
                hash->maxLinkedList = count;
        }
    }
    fclose(fpin);
}

/*
 * The comprare function that will interface with the linked list ADT. 
 */
int compare(void *key1, void *key2)
{
    char *k1 = (char *)key1;
    char *k2 = (char *)key2;

    return strcmp(k1, k2);
}

/*
 * hashKeySum sums up the ASCII values of the key and returns an 
 * address.
 */
int hashKeySum(char *key)
{
    int sum = 0;
    char *mover;
    for(mover = key; *mover; mover++)
        sum += *mover;
    return sum % SIZE;
}

/*
 * digitExtKey extracts the specific digits from the key and uses their
 * ascii values. It adds them together and returns an address.
 */
int digitExtKey(char *key)
{
    int digit, digit2, len;
    char buffer[7];
    char half1[5], half2[5];

    len = strlen(key);
    sprintf(half1, "%d%d", key[0], key[1]);
    sprintf(half2, "%d%d", key[len - 2], key[len-1]);
    sscanf(half1, "%d", &digit);
    sscanf(half2, "%d", &digit2);

    return (digit + digit2) % SIZE;
}

/* ================================================== */
/* This function creates the header of a hash table
   PRE: size
   POST: pointer to the header of the hash table
*/
HASH *createHashTable(int size)
{
	HASH *hash;
    int i;

	hash = (HASH *) malloc(sizeof(HASH));
	if( !hash )
		printf( "Not enough memory\n"), exit(101);
	hash->size = size;
	hash->table = (HASH_ITEM *) calloc(size, sizeof(HASH_ITEM));
	if( !(hash->table ) )
		printf( "Not enough memory\n"), exit(102);

	// write a loop to initialize the hash table: numbers to 0, pointers to NULL, etc.
    for(i = 0; i < size; i++)
        memset(&(hash->table[i]), 0, sizeof(HASH_ITEM));       
	return hash;
}

/*
 * printMenu prints the menu.
 */
void printMenu()
{
    printf("\n=============== MENU ===============\n");
    printf("P   Print hash table\n");
    printf("S   Search\n");
    printf("E   Print efficiency stats\n");
    printf("M   Print menu\n");
    printf("Q   Quit\n");
}

/*
 * getOption gets the option from the user. It returns the option.
 */
char getOption()
{
    char option;

    do{
        printf("\nEnter option: \n");
        scanf("%c", &option);
        FLUSH;
        option = toupper(option);
    }while(strchr("PSEMQ", option) == NULL);
    return option;
}

/*
 * printTable takes in the hash table hash and prints all data in the table
 * and linked lists.
 */
void printTable(HASH *hash)
{
    int i;
    int count, LLcount;
    STU *temp;

    printf("%4s %5s %3s %20s", " Cnt ", " Index ", " Gpa ", " Name        ");
    printf("\n%4s %5s %3s %20s\n", "=====", "=======", "=====", "=====================");
    for(i = 0, count = 0; i < hash->size; i++)
    {
        if(hash->table[i].count)
        {
            count++;
            printf("%4d. %5d %6.1f %20s\n", count, i, (hash->table)[i].stu.gpa,
                                           (hash->table)[i].stu.name);
        }
        LLcount = 0;
        if(hash->table[i].list)
            while(traverse(hash->table[i].list, LLcount,(void **)&temp))
            {
                count++;
                printf("%4d. %5d %6.1f %20s\n", count, i, temp->gpa, temp->name);
                LLcount++;
            }
    }
}

/*
 * search takes in the hash table hash and allows the user to search by key.
 */
void search(HASH *hash)
{
    char buffer[MAXLINE];
    char *mover;
    int addr, LLcount;
    STU *found;

    printf("Enter ID to search for: \n");
    scanf("%s", buffer);
    FLUSH;

    for(mover = buffer; *mover; mover++)
    {
        if(isalpha(*mover))
            *mover = toupper(*mover);
    }

    addr = hashKeySum(buffer);
    //addr = digitExtKey(buffer);
    if(hash->table[addr].count)
    {
        if(strcmp(hash->table[addr].stu.id, buffer) == 0)
        {
                printf("\n%s found in hash table.\n", hash->table[addr].stu.id);
                printf("%20s %15s %5s", "      Name    ", "    Index   ", " Gpa ");
                printf("\n%25s %5s %3s\n", "===========================", "======", "======");

                printf("%25s %6d %8.1f\n", hash->table[addr].stu.name, addr, 
                                            hash->table[addr].stu.gpa);

        }
        else if(hash->table[addr].list)
        {
            if(searchList(hash->table[addr].list, buffer, (void **)&found))
            {
                printf("\n%s found in linked list.\n", found->id);
                printf("%20s %15s %5s", "     Name   ", "  Index  ", " Gpa ");
                printf("\n%25s %5s %3s\n", "==========================", "=======", "======");

                printf("%25s %5d %8.1f\n", found->name, addr, found->gpa);

            }else printf("%s does not exist!\n", buffer);
        }
    }else printf("%s does not exist!\n", buffer);
}

/*
 * printEfficiency takes in the hash table hash and it prints the 
 * efficiency statistics.
 */
void printEfficiency(HASH *hash)
{
    int i, count, sum, areaCount;

    for(i = 0, count = 0, areaCount = 0, sum = 0; i < SIZE; i++)
    {
        if(hash->table[i].count)
            areaCount++;

        if(hash->table[i].list)
        {
            count++;
            sum += (hash->table[i].count - 1);
        }
    }

    printf("\nEfficiency Statistics             \n");
    printf("====================================\n");
    printf("Size of hash table is %d.\n", hash->size);
    printf("%.1f%% of prime area filled.\n", (areaCount / (float)SIZE) * 100);
    printf("%.1f average nodes in linked-lists.\n",(float)sum/count);
    printf("Longest linked list is %d.\n", hash->maxLinkedList);
}

/*
 * destroyHash takes in the hash table called hash and it frees 
 * all memory.
 */
HASH *destroyHash(HASH *hash)
{
    int i, LLcount;
    STU *mover;

    for(i = 0; i < SIZE; i++)
    {
        LLcount = 0;
        if(hash->table[i].count != 0)
        {
            free(hash->table[i].stu.name);
            if(hash->table[i].list)
            {
                while(traverse(hash->table[i].list, LLcount,(void **)&mover))
                {
                    free(mover->name);
                    LLcount++;
                }
                hash->table[i].list = destroyList(hash->table[i].list);
            }
        }
    }
    free(hash->table);
    free(hash);
    return hash;
}

/********************************************************************************
** CIS 15C
***************
**
** Review: Singly Linked Lists: header file of the application 
**
*************************************************

   type definitions and prototype declarations 

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

#define FLUSH while (getchar () != '\n')

typedef struct
{
   char ID[3];           
   char* country;      
   char* cap;      
   long int pop;          
} COUNTRY;

typedef struct nodetag
{
	COUNTRY *data;
    struct nodetag *forw;
    struct nodetag *back;
}NODE;

typedef struct
{
    int count;
    NODE *head;
    NODE *tail;
}LIST;

// Type Definitions 


// Prototype Declarations 
char getOption	  (void);
void printMenu    (void);
void searchByLetter (LIST *pList);
void printCountry (NODE *pList);
void getCountry(char input[]);
void getCountryID(char target[]);
int  checkString(char *s);
void getString(char s[], char msg[]);
void formatString( char *s );
char *allocateString( char *tempString );
COUNTRY stringToCountry(char input[]);
void formatPop(long int pop);

int   searchList  (LIST *pList, NODE **pCur, char target[]);
void insertNode  (LIST *pList, NODE *pCur, COUNTRY  item);
void deleteNode  (LIST *pList, NODE *pCur);
void  printList   (LIST *pList);
void printBack (LIST *pList);
LIST *destroyList (LIST *pList);

LIST *buildManager(void);
void processListManager (LIST *pList);
void  searchManager      (LIST *pList);
void insertManager	     (LIST *pList);
void deleteManager      (LIST *pList);


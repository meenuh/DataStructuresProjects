/********************************************************************************
** CIS 15C
***************
**
** SLL_main.c
**
*************************************************
This program creates a doubly linked list that has a pointer to a structure COUNTRY.
It allows the user to search, insert and delete from the list. 
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

int main ( void )
{
    LIST *pList;    

    printf("\t\t Singly Linked Lists\n\n");
	pList = buildManager();
    processListManager(pList);
	pList = destroyList(pList);    
    
	printf("\n\t\tEnd of program - LINKED LISTS"
		   "\n\t\tHave a great day!\n");    

    return 0;

}

/*	==================== getOption ====================
	Gets and validates the user's option.
*/
char getOption	(void)
{
	char option;

	printf ("\n\nPlease enter the option: ");
	scanf  (" %c", &option);
    FLUSH;
	option = toupper (option);
    while(strchr("PLBSIDME", option) == NULL)
    {
        printf("\a*** Invalid option! ***\n");
        printf("Enter one of the following letters: P, L, B, S, I, D, M, E: " );
        scanf  ("%c", &option);
        FLUSH;
	    option = toupper (option);
    }

	return option;

} 

/* ============================== printMenu ==============================
	Prints the menu to the screen.
*/
void printMenu (void)
{

	printf("\n\t\t***********************"
           "\n\t\t*                     *"
           "\n\t\t*   L - Search Letter *"
	       "\n\t\t*   P - Print Forward *"
           "\n\t\t*   B - List Backwards*"
           "\n\t\t*   S - Search        *"
	       "\n\t\t*   I - Insert        *"
	       "\n\t\t*   D - Delete        *"
	       "\n\t\t*   M - Print Menu    *"
	       "\n\t\t*   E - Exit          *"
	       "\n\t\t*                     *"
	       "\n\t\t***********************");

} 

/* ======================== allocateString ========================
    Uses a statically allocated string to create a 
    dynamically allocated string with the same contents.
*/
char *allocateString( char *tempString )
{        
    char *string;
    int   stringSize;

    stringSize = strlen( tempString ) + 1;
    string = (char *) calloc (stringSize, sizeof (char));
    if ( string == NULL)
	{
        printf ("ERROR, not enough memory!!!\a\n"); 
		exit (103);
	}
    strcpy (string, tempString);
    return string;
}

/*================getCountry=================================
  Store the information in structure COUNTRY
*/
COUNTRY stringToCountry(char input[])
{  
	COUNTRY temp;
	char tcountry[50];
	char tcap[50];
		
	sscanf(input,"%3s %20[^;]%*c %15[^;]%*c %d", temp.ID, tcountry, tcap, &temp.pop);
	temp.country = allocateString(tcountry);
    temp.cap = allocateString(tcap);

	return temp;
}

/*===========getCountryID======================
  Prompt the user to enter a country ID
  Pre  target[] - empty
  Post target[] - contains two uppercase letters
*/

void getCountryID( char target[] )
{
	
	printf("Please enter the country ID: ");
	scanf("%2s", target);
	FLUSH;
	while (!(isalpha(target[0]) && isalpha(target[1])))
	{
		printf("Wrong input: letters only!\n");
		printf("Please enter the country ID: ");
	    scanf("%2s", target);
	    FLUSH;
	}
	target[0] = toupper(target[0]);
	target[1] = toupper(target[1]);
	
	return;
}

/*==================printCountry======================
  Print information about one country in label format
  Pre  pList points to a node in the list
  Post print result
*/
void printCountry(NODE *pCur)
{
	printf("        ID: %s\n" , pCur->data->ID);
	printf("   Country: %s\n" , pCur->data->country);
	printf("   Capital: %s\n" , pCur->data->cap);
	printf("Population: ");
    formatPop(pCur->data->pop);
    putchar('\n');
}//printCountry

/*===========getInput======================
  Get input from the user
  Pre  NULL
  Post input is stored
*/
void getCountry( char input[] )
{
	char country[50];
	char capital[50];
	long population;

	getString( country, "Please enter the Country: " );
	getString( capital, "Please enter the Capital: " );
	
	printf("Please enter the population: ");
	while(scanf("%ld", &population) != 1) 
	{
		FLUSH;
		printf("The input is incorrect\n");
		printf("Please enter the population: ");
	}
	sprintf( input + 2, " %s; %s; %ld", country, capital, population );
	
	return;
}

/*===========checkString=================================
  Checks if a strings contains letters, spaces and commas
  Pre  string
  Post 1 - if valid, 0 otherwise
*/
int checkString( char *s )
{

	while( *s != '\0' )
	{
		if( !isalpha(*s) && *s != ' ' && *s != ',' )
			return 0;
		s++;
	}

	return 1;
}

/*===========getString==================================
  Gets a string that contains letters, spaces and commas
  Pre  string
  Post 1 - if valid, 0 otherwise
*/
void getString( char s[], char msg[] )
{

	printf("%s", msg);
	gets(s);
	while(!checkString(s))
	{
		printf("The input is incorrect: letters, spaces and commas only!\n");
	    printf("%s", msg);
	    gets(s);		
	}

    formatString(s);

	return;
}

/*===========formatString==============================
  All letters in the string are converted to lower case,
  except for the first letter in a word.
  Pre  string
  Post string formatted
*/
void formatString( char *s )
{

    if( *s != '\0' )
	{
        *s = toupper(*s);
		s++;
		while( *s != '\0' )
		{
			*s = tolower(*s);
			if( isalpha(*s) && *(s - 1) == ' ' )
				*s = toupper(*s);
			s++;
		}
    }
	return;
}

/*
 * formatPop takes in the population and it prints it out
 * with commas. It does not return anything.
 */
void formatPop(long int pop)
{
    int numDig[4];
    int i = 0;
    while(pop > 1000)
    {
       numDig[i] = pop % 1000;
       pop = pop / 1000;
       i++;
    }

    printf("%d", pop);
    if(i > 0)
        printf(",");
    i--;
    while(i >= 0)
    {
        printf("%03d", numDig[i]);
        if(i != 0)
            printf(",");
        i--;
    }
}

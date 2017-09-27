/****************************************************************************
** CIS 15C 
** Fall  2011
*************
**
** Homework 1-Stocks    
**                          STACKS and          
**              MULTIPLE SOURCE FILES PROGRAMS           25 Points
******************************************************************

  
  
****************************************
**
**  Written By: Mina Yi
**
**  Date: October 9, 2011
**
********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "perry.h"
#include "stackADT.h"

void checkAndGetArgs(int argc, char **argv, FILE **fin, FILE **fout);
void readFromFile(FILE *fpin, STACK *stkStock);

typedef struct stock STOCK;

struct stock{
    char date[11];
    char buySell;
    int qty;
    double price;
};

int main (int argc, char **argv)
{
    FILE *fpin, *fpout;

    STACK *stkStock;

	printf("\n\n\t\tHomework 1: STACK ADT\n\n");
	printf("\tThis program ...\n");

    checkAndGetArgs(argc, argv, &fpin, &fpout);
    stkStock = createStack();
    readFromFile(fpin, stkStock); 
    
    
    
    
    
	printf("\n\t\tThank you for using the program,"
		   "\n\t\tHave a great day!\n");

	return 0;
} 

void checkAndGetArgs(int argc, char **argv, FILE **fin, FILE **fout)
{
    if (argc != 3)
    {
        printf("Wrong number of command line arguments!\n");
        exit(1);
    }

    *fin = Fopen(argv[1], "r");
    *fout = Fopen(argv[2], "w");
}

void readFromFile(FILE *fpin, STACK *stkStock)
{
    STOCK *new;

    char date[11], letter;
    int shares;
    double price;

    while(fscanf(fpin, "%s %c %d %lf", date, &letter, &shares, &price))
    {
        if(!fullStack(stkStock))
        {
            new = (STOCK *)Malloc(sizeof(STOCK));

            strcpy(new->date, date);
            new->buySell = letter;
            new->qty = shares;
            new->price = price;
        }
    }
}

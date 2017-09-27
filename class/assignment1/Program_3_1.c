/*	This program is a test driver to demonstrate the 
	basic operation of the queue functions. 
	   Written by: Mina Yi 
	   Date: October 13, 2011       
*/

#include <stdio.h>
#include <stdlib.h>

#include "perry.h"
#include "queueADT.h"

void insertData(QUEUE *queue);
void printData(QUEUE *queue);

int main (void)
{
    QUEUE *queue;

	printf("Beginning Queue Program\n\n");
	
	queue = createQueue();
	insertData(queue);
	printData(queue);
	free(queue);

	printf("\n\nEnd Simple Queue Program\n");
	return 0;
}

/*
	================== insertData ==================
	This program creates random character data and 
	inserts them into a linked list stack.
	   Pre  pStackTop is a pointer to first node 
	   Post Stack has been created 
*/
void insertData (QUEUE* queue)
{
	float* numIn;
	int   success;
	int   nodeCount;

	printf("Insert data into a stack\n\n");
	for (nodeCount = 0; nodeCount < 5; nodeCount++)
	{
	     printf( "Enter a number: " );
         numIn = (float *)Malloc(sizeof(float));
	     scanf( "%f", numIn );
	     success = enqueue(queue, numIn);
	     if (!success)
	     {
	         printf("Error 100: Out of Memory\n");
	         exit (100);
	     } 
    }  
	printf("\n");
	return;
} 

/*	===================== printData ==================== 
	This function prints a singly linked stack.
	   Pre     pStackTop is pointer to valid stack
	   Post    data in stack printed
*/
void printData (QUEUE* queue)
{
	float* numOut;

	printf("Queue contained: \n");
	while (dequeue(queue, (void **)&numOut))
	    printf("%6.2f\n", *numOut);

	return;
} 

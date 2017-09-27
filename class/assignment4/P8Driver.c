/*	This program tests AVL Trees as implemented in Gilberg & Forouzan
	Written by: G & F
	Date:       2/98
	
    Brooks/Cole Publishing Company
	An International Thomson Publishing Company
	Copyright 1998. All Rights Reserved
*/
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "AVLtreeADT.h"

//  Prototype Functions  
void insert       (AVL_TREE *tree);
void delete       (AVL_TREE *tree);
void retrieve     (AVL_TREE *tree);
void testUtilties (AVL_TREE *tree);

char   doMenu (void);

int    compare (void *newDataPtr, void *rootDataPtr);

void   process (void *dataPtr);
	
int main ( void )
{
	char      option;
	AVL_TREE *tree;


	printf(	"Start AVL Tree\n" );
	tree = AVL_Create (compare);
	if (!tree)
		printf("\aERROR: Cannot create tree\a\n"), exit (100);

	while ( (option = doMenu () ) != 'q' )
	{
		switch ( option )
	 	{
		 	 case 'i' :  insert (tree);
		 	 			 break;
		 	 case 'd' :  delete (tree);
		 	 			 break;
		 	 case 'f' :  
		 	             retrieve(tree);
		 	             break;
		 	 case 'p' :  AVL_Print (tree);
		 				 break;
		 	 case 't' :  printf("\nBegin Traversal\n");
		 	             AVL_Traverse (tree, process);
						 printf("\nEnd Traversal\n");
						 break;
		 	 case 'x'  : testUtilties (tree);
		 	             break;
		 	 case 'z'  : printf("\nDone!\n");
                         tree = AVL_Destroy(tree);
                         if(!tree)
                            printf("Tree is null therefore it is empty so destroy was successful.\n");
                         else printf("Destroy unsuccessful!\n");
		 	             exit (0);
		 	             break;
		 	 default  :  printf( "\nInvalid option. Please try again.\n" );
		} // switch
	} // while 

	printf("\nTree Destroyed\n");
	tree = AVL_Destroy (tree);
	printf( "End AVL Tree\n" );
	return 0;
	
} // main 

/* ============================= doMenu ============================= */
/*	This function prints a menu and reads the user selection.
	Pre		Nothing.
	Post	option returned.
*/
char	doMenu ( void ) 
{
	char	option;
 
 	printf( "\n============ Menu =============\n" );
 	printf( " i :     Insert new item.      \n" );
 	printf( " d :     Delete a node.        \n" );
 	printf( " f :     Retrieve data.        \n" );
 	printf( " p :     Print tree.           \n" );
 	printf( " t :     Traverse tree.        \n");
 	printf( " x :     Test ADT utilities.   \n");
 	printf( " z :     Destroy Tree and Quit.\n");
 	printf( " q :     Quit.                \n\n" );
 	printf( "===============================\n" );
 	printf( "Please enter your choice:  " );
 		 
 	scanf( " %c", &option );
 	option = tolower ( option );
 	
 	return option;
} // doMenu 

/* ============================= retrieve ============================= */
/*	This function locates a node in the tree.
	Pre	 AVL tree exists.
	Post Node retrieved and printed.
*/
void retrieve (AVL_TREE *tree)
{
	int key;
	int *addr;

	printf("Please enter key to be found: ");
	scanf ("%d", &key);
	
	addr = AVL_Retrieve (tree, &key);
	if (addr)
	    printf("\nKey found. Contains %d\n", *addr);
	else
	    printf("\n\aKey %d not found\n", key);
	
	return;
}// retrieve 

/* ============================= insert ============================= */
/*	This function gets input from the user and passes it to the AVL insert
 	function.
	Pre	 AVL tree exists.
	Post Node has been inserted.
*/
void insert (AVL_TREE *tree) 
{
	int *newPtr;
    int success;

	newPtr = (int *) malloc (sizeof(int));
	if (!newPtr )
		printf( "\aERROR: Cannot allocate data.\n" ), exit (101);
 
	printf("\nPlease enter interger to be inserted: ");
	scanf ("%d", newPtr);
    
    success = AVL_Insert(tree, newPtr);
	if (success)
	       printf("%3d inserted\n", *newPtr);
	else
	   printf("ERROR inserting %d\n\tduplicate value or \n\tmemory overflow\n", *newPtr);
   
	return;
} // insert 

/* ============================= delete ============================= */
/*	This function deletes a node from the tree. It asks the user for the
	key of the node to be deleted and then removes it from the tree.
	Pre	 Tree must be initialized. Null tree is OK.
	Post The node is deleted and its space recylced
		-or- An error message is printed.
*/
void delete ( AVL_TREE *tree ) 
{
 	int	dltKey;
 	int success;
 	 
 
	printf( "\nPlease enter integer to be deleted: " );
	scanf(  "%d", &dltKey );
 
	success = AVL_Delete (tree, &dltKey);
	if (success)
		printf("%3d deleted\n", dltKey);
	else
		printf("\aERROR: %d not in list.\a\n", dltKey);
 
	return;
}// delete 

/*	=================== compare ================== */
/*	This function compares two integers identified
	by pointers to integers.
	Pre		arguPtr and listPtr are pointers to integers
	Return	-1: arguPtr value <  listPtr value
			-0: arguPtr value == listPtr value
			+1: arguPtr value > listPtr value
*/
int compare (void *arguPtr, void *listPtr)
{
	int arguValue;
	int listValue;
	
	arguValue = *(int *)arguPtr;
	listValue = *(int *)listPtr;
	
	if (arguValue < listValue)
		return -1;
	else if (arguValue == listValue)
		return 0;
	else
		return +1;
}// compare 

/*	=================== process ================== */
/*	This function "processes" a node by printing a
	sequential number and the node data.
	Pre     dataPtr is pointer to user data structure
	Post	Data (integer) printed.
*/
void process (void *dataPtr)
{
	static int count = 0;

	printf("Process #%2.1d: %5d\n", ++count, *(int *)dataPtr);
	return;
}// process

/*	=================== testUtilties ================== 
	This function tests the ADT utilities by calling
	each in turn and printing their results.
	Pre     tree has been created.
	Post	Results printed.
*/
void testUtilties (AVL_TREE *tree)
{
	printf("Tree contains %3d nodes: \n", AVL_Count(tree));
	if (AVL_Empty(tree))
	    printf("The tree IS empty\n");
	else
	    printf("The tree IS NOT empty\n");
	if (AVL_Full(tree))
	    printf("The tree IS full\a\n");
	else
	    printf("The tree IS NOT full\n");
	return;
} // testUtilities 


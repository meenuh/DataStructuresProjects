/*	AVL Tree Library: header file
	Written by: G & F
	Date:       2/98
	
    Brooks/Cole Publishing Company
	An International Thomson Publishing Company
	Copyright 1998. All Rights Reserved
*/
#include <stdio.h>
#include <stdlib.h>

#define LH +1				// Left High
#define EH  0				// Even High 
#define RH -1				// Right High 

#ifndef TRUE
	#define TRUE  (1)
	#define FALSE (0)
#endif

typedef struct node
{
	 void        *dataPtr;
	 struct node *left;
	 int          bal;
	 struct node *right;
} NODE;

typedef struct
{
	 int    count;
	 int   (*compare) (void *argu1, void *argu2);
	 NODE   *root;
} AVL_TREE;
	
// Public Functions
AVL_TREE *AVL_Create (int  (*compare) (void *argu1, void *argu2));
int  AVL_Insert (AVL_TREE *tree, void *dataInPtr);
int  AVL_Delete (AVL_TREE *tree, void *dltKey);
void *AVL_Retrieve  (AVL_TREE *tree, void *keyPtr);
void AVL_Traverse (AVL_TREE *tree, void (*process) (void *dataPtr) );
int  AVL_Empty (AVL_TREE *tree);
int  AVL_Full (AVL_TREE *tree);
int  AVL_Count (AVL_TREE *tree);
AVL_TREE *AVL_Destroy (AVL_TREE *tree);
void AVL_Print (AVL_TREE *tree);

// Private Functions
NODE *_insert (AVL_TREE *tree, NODE *root, NODE *newPtr, int *taller, int *duplicate);
NODE *leftBalance (NODE *root, int  *taller);
NODE *rotateLeft (NODE *root);
NODE * rightBalance (NODE *root, int  *taller);
NODE *rotateRight (NODE *root);
NODE *_delete (AVL_TREE *tree, NODE *root, void *dltKey, int *shorter, int *success );
NODE * dltLeftBalance  ( NODE *root, int  *smaller );
NODE *dltRightBalance (NODE *root, int  *shorter);
void * _retrieve (AVL_TREE *tree, void      *keyPtr, NODE      *root);
void _traversal (NODE *root, void (*process) (void *dataPtr) );
void _destroyAVL (NODE *root);
void _print (NODE *root, int level);

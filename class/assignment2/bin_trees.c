/****************************************************************************
** CIS 15C
**********
**
** CHAPTER 6: TREES    BUILDING A RANDOM BINARY TREE
**
********************************************************
 
  The main goal of this example is build a binary tree that could be used to
  test the traversal functions and also for the homework problems, such as
  counting/printing the leaves, counting the inner nodes in a binary tree, 
  printing the indented tree, etc.

****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "queueADT.h"

#define MAX 100

typedef struct nodeTag{
   int data;
   struct nodeTag *left;
   struct nodeTag *right;
} NODE;


NODE *buildBinaryTree( int n );
void printTreeInorder( NODE *root );
void printPreOrder(NODE *root);
void printPostOrder(NODE *root);
void printLeafNodes(NODE *root);
int countIntNodes(NODE *root);
void deleteLeaves(NODE *root);
void breadthFirstTrav(NODE *root);

int main( void )

{
   NODE *root;
   int   n;   

   srand(time(NULL));

   n = rand() % 7 + 4;
   root = buildBinaryTree( n );

   printf( "\nInorder:\n");
   printTreeInorder( root );

   printf( "\nPreorder:\n");
   printPreOrder(root);
   
   printf( "\nPostorder:\n");
   printPostOrder(root);

   printf( "\nPrint leaf nodes:\n" );
   printLeafNodes(root);

   printf( "\nCount internal nodes:\n");
   printf("%3d ", countIntNodes(root) - 1);   // - 1 for root
   
   printf("\nDelete Leaves:\n");
   deleteLeaves(root);
   printTreeInorder(root);

   printf("\nBreadth first traversal: \n");
   breadthFirstTrav(root);

   printf( "\n\n" );

   return 0;
}

/* ====================== printTreeInorder ====================== */
/* 
   Traverse / print a binary tee in Left-Root-Right sequence.
      PRE:    root is the entry node of a tree or subtree 
      POST:   tree printed in inorder
*/
void printTreeInorder( NODE *root )
{
    if( root ){
      printTreeInorder( root->left);
      printf( "%3d ",  root->data );
	  printTreeInorder( root->right);
      
   }
   return;
}

/*
 * prints the tree in preorder
 */
void printPreOrder(NODE *root)
{
    if(root)
    {
        printf("%3d ", root->data);
        printPreOrder(root->left);
        printPreOrder(root->right);
    }
}

/*
 * printPostOrder prints the tree in post order.
 */
void printPostOrder(NODE *root)
{
    if(root)
    {
        printPostOrder(root->left);
        printPostOrder(root->right);
        printf("%3d ", root->data);
    }   
}

/*
 * printLeafNodes takes in a NODE * and prints data from the leaves in the
 * tree. It does not return anything.
 */
void printLeafNodes(NODE *root)
{
    if(root->right)
        printLeafNodes(root->right);
    if(root->left)
        printLeafNodes(root->left);
    if(!(root->right) && !(root->left))
        printf("%3d ", root->data);
}

/*
 * countIntNodes counts internal nodes (has predecessor and successor). It
 * takes in a NODE * and uses a static int in order to retain the value.
 */
int countIntNodes(NODE *root)
{
    static int count = 0;

    if(root->right)
        countIntNodes(root->right);
    if(root->left)
        countIntNodes(root->left);
    if((root->right) || (root->left))
        count++;

}

/*
 * deleteLeaves takes in a NODE * and it deletes all leaves in the
 * BST. It does not return anything.
 */
void deleteLeaves(NODE *root)
{
    if(root)
    {
        if(root->left)
        {
            if(!(root->left->left) && !(root->left->right)) 
            {
                free(root->left);
                root->left = NULL;
            }else deleteLeaves(root->left);
        }

        if(root->right)
        {
            if(!(root->right->left) && !(root->right->right)) 
            {
                free(root->right);
                root->right = NULL;
            }else deleteLeaves(root->right);
        }
    }
}

/*
 * breadthFirstTrav takes a NODE * and it creates a queue in order 
 * to implement the breadth first traversal. It does not return anything.
 */
void breadthFirstTrav(NODE *root)
{
    NODE *current = root;
    QUEUE *que;

    que = createQueue();

    while(current)
    {
        printf("%3d", current->data);
        if(current->left)
            enqueue(que, current->left);
            
        if(current->right)
            enqueue(que, current->right);

        if(!emptyQueue(que))
            dequeue(que, (void**)&current);
        else current = NULL;
    }

    que = destroyQueue(que);
}
/* ====================== buildBinaryTree ====================== */
/* 
   Build a random binary tree of integer numbers within the range
   [0, 99]; root is always 50.
      PRE:    n - number of nodes
      POST:   root - the root of the random tree
*/
NODE *buildBinaryTree( int n )
{
   NODE *buildNode ( int   data );
   NODE *findParent( NODE *root );
   void  insert    ( NODE *parent, NODE *pNew );

   NODE *root = NULL;
   NODE *pNew;
   NODE *parent;
   int   i;
   int   data;
   
   root = buildNode (50 );

   srand( time( NULL ) );
   for( i = 1; i < n; i++ ){
        data   = rand( ) % 100;
        pNew   = buildNode( data );
        parent = findParent( root );
        insert( parent, pNew );
   }
   return root;
}

/* ====================== buildNode ====================== */
/* 
   Allocate memory for a tree node.
      PRE:    data 
      POST:   newNode
*/
NODE *buildNode( int data )
{
   NODE *newNode;

   newNode = (NODE *) malloc (sizeof(NODE));
   if( !newNode )
      printf( "Overflow!\n" ), exit(100);
   newNode->data  = data;
   newNode->left  = NULL;
   newNode->right = NULL;

   return newNode;
}

/* ====================== findParent ====================== */
/* 
   Find a leaf or a leaf-like node (outdegree is 1) in a binary tree. 
   Starting point: root. Then generate a random number: if it is odd 
   continue with the left subtree otherwise continue with the right 
   subtree.
      PRE:    root
      POST:   parent 
*/
NODE *findParent( NODE *root )
{

   NODE *pWalk;
   NODE *parent;
   int  rand_num;

   pWalk = root;
   while( pWalk ){
      parent   = pWalk;
      rand_num = rand( ) % 100;
      if( rand_num % 2 ) /* if odd - take left */
         pWalk = pWalk->left;
      else
         pWalk = pWalk->right;
   }
   return parent;
}

/* ====================== insert ====================== */
/* 
   Insert a node in a binary tree. Generate a random number:
   if it is odd  - insert left,  if not taken, otherwise insert right;
   if it is even - insert right, if not taken, otherwise insert left. 
      PRE:    parent - the parent of the new node - outdegree is 0 or 1
              pNew   - the new node
      POST:   new node inserted
*/
void insert( NODE *parent, NODE *pNew )
{
   int  rand_num;

   rand_num = rand( ) % 100;
   if( rand_num % 2  )
      if( !parent->left )
         parent->left  = pNew;
      else
         parent->right = pNew;
   else               
      if( !parent->right )
         parent->right = pNew;     
      else
         parent->left  = pNew;     
        
   return;
}


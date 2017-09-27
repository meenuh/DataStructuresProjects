/****************************************************************************
** CIS 15C
**********
**
** CHAPTER 6: TREES    BINARY TREE TRAVERSALS
**
********************************************************

  Given: Inorder, Postorder, Preorder - Recursive
         Postorder - Iterative (using a stack)

  Extra Credit: Iteratice Inorder  (2Points)
                Iterative Preorder (2Points)

  NAME: Mina Yi
  DATE: 11/29/2011

****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "stackADT.h"

#define MAX 100

typedef struct nodeTag{
   int data;
   struct nodeTag *left;
   struct nodeTag *right;
} NODE;

NODE *buildBinaryTree( int n );

void inorder( NODE *root );
void preorder( NODE *root );
void postorder( NODE *root );

void preorderI( NODE *root );
void postorderI(NODE *root);
void inorderI(NODE *root);

int main( void )
{
   NODE *root;
   int   n = 6;

   root = buildBinaryTree( n );

   printf("\n\n==========\nPREORDER\n");
   printf("Recursive: ");
   preorder(root);
   printf("\nIterative: ");
   preorderI(root);

   printf("\n\n==========\nINORDER\n");
   printf("Recursive: ");
   inorder( root );
   printf("\nIterative: ");
   inorderI(root);
   //

   printf("\n\n==========\nPOSTORDER\n");
   printf("Recursive: ");
   postorder( root );
   printf("\nIterative: ");
   postorderI(root);
   //

   printf( "\n\n" );
   return 0;
}

/* ====================================================== */
/* ================== ITERATIVE TRAVERSALS ============== */
/* ====================================================== */

/* ====================== preorderI ====================== */
/*
   Traverse / print a binary tee in Left-Right-Root sequence
   using a stack
      PRE:    root is the entry node of a tree or subtree
      POST:   tree printed in inorder
*/
void preorderI( NODE *root )
{
   STACK *s;
   NODE  *ptr;

   s = createStack();
   pushStack(s, root);
   while( !emptyStack(s) ){
      ptr = popStack(s);
      if( ptr ){
         printf( "%3d",  ptr->data );
         pushStack(s, ptr->right);
         pushStack(s, ptr->left);
      }
   }
   free(s);
   return;
}

void postorderI(NODE *root)
{
    STACK *s, *output;
    NODE *ptr;

    s = createStack();
    output = createStack();

    pushStack(s, root);          
    
    while(!emptyStack(s))
    {
        ptr = stackTop(s);
        pushStack(output, ptr);
        popStack(s);
        if(ptr->left)
            pushStack(s, ptr->left);
        if(ptr->right)
            pushStack(s, ptr->right);
    }

    while(!emptyStack(output))
    {
        ptr = popStack(output);
        printf("%3d", ptr->data);
    }

    free(s);
    free(output);
}

void inorderI(NODE *root)
{
   STACK *s;
   NODE *ptr;

   s = createStack();
   pushStack(s, root);
   ptr = root->left;
   while(!emptyStack(s) || ptr)
   {
        if(ptr)
        {
            pushStack(s, ptr);
            ptr = ptr->left;
        }else{
            ptr = popStack(s);
            printf("%3d", ptr->data);
            ptr = ptr->right;
        }
   }

   free(s);
}

/* ====================================================== */
/* ================== RECURSIVE TRAVERSALS ============== */
/* ====================================================== */

/* ====================== postorder ====================== */
/*
   Traverse / print a binary tee in Left-Right-Root sequence.
      PRE:    root is the entry node of a tree or subtree
      POST:   tree printed in inorder
*/
void postorder( NODE *root )
{
   if( root ){
      postorder( root->left);
	  postorder( root->right);
      printf( "%3d",  root->data );
   }
   return;
}

/* ====================== preorder ====================== */
/*
   Traverse / print a binary tee in Root-Left-Right sequence.
      PRE:    root is the entry node of a tree or subtree
      POST:   tree printed in inorder
*/
void preorder( NODE *root )
{
   if( root ){
      printf( "%3d",  root->data );
      preorder( root->left);
	  preorder( root->right);
   }
   return;
}

/* ====================== inorder ====================== */
/*
   Traverse / print a binary tee in Left-Root-Right sequence.
      PRE:    root is the entry node of a tree or subtree
      POST:   tree printed in inorder
*/
void inorder( NODE *root )
{
   if( root ){
      inorder( root->left);
      printf( "%3d",  root->data );
	  inorder( root->right);
   }
   return;
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



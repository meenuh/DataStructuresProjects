/****************************************************************************
 ** CIS 15C 
 ** Fall    2011
 ***************
 **
 ** Homework 1   STACK APPLICATIONS - backtracking
 **              MULTIPLE SOURCE FILES PROGRAMS                      25 Points
 **
 *****************************************************************************

 The functions that make up a C program need not all be compiled at the same time; 
 the source text of the program may be kept in several files. 

 Use stackADT.c and stackADT.h  to implement a solution for a variation of 
 Project 23, page 143. (check the input files)

 For this assignment do NOT turn in the given files: stackADT.c and stackADT.h

 ****************************************
 **
 **  Written By: Mina Yi
 **
 **  Date: October 10, 2011
 **
 ********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "perry.h"
#include "stackADT.h"

#define MAXLINE 100

typedef struct{
    int checked;
    int row;
    int col;
    char x;
}OBJECT;

void checkAndGetArgs(int argc, char **argv, FILE **fpin);
OBJECT **getData(FILE *fpin, int *rows, int *cols);
void findObjects(OBJECT **matrix, int rows, int cols, STACK *stack);

int main (int argc, char **argv)
{

    FILE *fpin;
    int rows, cols;
    STACK *stack;
    OBJECT **matrix;

    printf("\n\n\t\tHomework 1: STACK ADT and Backtracking\n\n");
    printf("\tThis program finds objects and returns the area of the objects in a file.\n" ); 

    stack = createStack();
    checkAndGetArgs(argc, argv, &fpin);
    matrix = getData(fpin, &rows, &cols);    
    findObjects(matrix, rows, cols, stack); 

    printf("\n\t\tThank you for using the program,"
            "\n\t\tHave a great day!\n");

    return 0;
} 

void checkAndGetArgs(int argc, char **argv, FILE **fpin)
{

    if(argc != 2)
    {
        printf("Wrong number of command line arguments!\n");
        exit(101);
    }

    *fpin = Fopen(argv[1], "r");
}

OBJECT **getData(FILE *fpin, int *rows, int *cols)
{
    int i, j;
    char obj;
    OBJECT **matrix;

    fscanf(fpin, "%d %d", rows, cols);
    matrix = (OBJECT **)Malloc((*rows) * sizeof(OBJECT *));

    for(i = 0; i < *rows; i++)
    {
        matrix[i] = (OBJECT *)Malloc(*cols * sizeof(OBJECT));
        for(j = 0; j < *cols; j++)
        {
            fscanf(fpin, "%c", &obj);
            //if(obj == '\n')
              //  fscanf(fpin, "%c", &obj);

            matrix[i][j].x = obj;
            matrix[i][j].row = i;
            matrix[i][j].col = j;
            matrix[i][j].checked = 0;

        }
    }
    return matrix;
}

void findObjects(OBJECT **matrix, int rows, int cols, STACK *stack)
{
    int r, c, objCount = 0, objArea = 0;
    OBJECT *temp;

    for(r = 0; r < rows; r++)
    {
        for(c = 0; c < cols; c++)
        {
            //check current
            if(matrix[r][c].x != '0' && 
                    matrix[r][c].checked == 0)
            {
                matrix[r][c].checked = 1;
                pushStack(stack, &matrix[r][c]);
                objArea++;
                objCount++;
                while(!emptyStack(stack))
                {
                    temp = (OBJECT *)popStack(stack);   
                    //check below
                    if((!matrix[temp->row + 1][temp->col].checked) && 
                            matrix[temp->row + 1][temp->col].x != '0')
                    {
                        matrix[temp->row + 1][temp->col].checked = 1;
                        pushStack(stack, &matrix[temp->row + 1][temp->col]);
                        objArea++;
                    }

                    //check left
                    if((!matrix[temp->row][temp->col - 1].checked)&&
                            (matrix[temp->row][temp->col - 1].x != '0'))
                    {
                        matrix[temp->row][temp->col - 1].checked = 1;
                        pushStack(stack, &matrix[temp->row][temp->col - 1]);
                        objArea++;
                    }

                    //check right
                    if((!matrix[temp->row][temp->col + 1].checked) && 
                            matrix[temp->row][temp->col + 1].x != '0')
                    {
                        matrix[temp->row][temp->col + 1].checked = 1;
                        pushStack(stack, &matrix[temp->row][temp->col + 1]);
                        objArea++;
                    }

                    //check above
                    if((!matrix[temp->row - 1][temp->col].checked) && 
                            (matrix[temp->row - 1][temp->col].x != '0'))
                    {
                        matrix[temp->row - 1][temp->col].checked = 1;
                        pushStack(stack, &matrix[temp->row - 1][temp->col]);
                        objArea++;
                    }
                }
            }
            if(objArea != 0)
            {
                printf("Object: %d Area: %d\n", objCount, objArea);
                objArea = 0;
            }
        }
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "bstADT.h"

#define FLUSH while(getchar() != '\n')

typedef struct
{
    char* name;
    int ID;
    float GPA;
}STU;

//Manager
BST_TREE* buildTreeManager();
void processManager(BST_TREE* tree);




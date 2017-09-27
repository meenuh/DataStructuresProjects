#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "bstADT.h"

#define MAXLINE 100
#define FLUSH while(getchar() != '\n')

void buildTreeManager(BST_TREE** idTree, BST_TREE** nameTree);
int compID(void* stu1, void* stu2);
int compName(void* stu1, void* stu2);
void printByID(BST_TREE* idTree);
void printID(void *data);
void printByName(BST_TREE* nameTree);
void printStudent(void *data);
void searchID(BST_TREE* idTree);
void searchName(BST_TREE* nameTree);
void addStudent(BST_TREE* idTree, BST_TREE* nameTree);
void breadthTrav(BST_TREE* idTree);
void printMenu();
char getOption();
void destroyStudent(BST_TREE* tree);
void freeStudent(void* dataPtr);

typedef struct
{
    int id;
    char* name;
    float gpa;
}STU;

int main()
{
    char option;
    BST_TREE* idTree, *nameTree;

    buildTreeManager(&idTree, &nameTree);

    while((option = getOption()) != 'Q')
    {
        switch(option)
        {
            case 'A': printByID(idTree);
                      break;
            case 'B': printByName(nameTree);
                      break;
            case 'C': searchID(idTree);
                      break;
            case 'D': searchName(nameTree);
                      break;
            case 'E': addStudent(idTree, nameTree);
                      break;
            case 'F': breadthTrav(idTree);
                      break;
            case 'M': printMenu();
                      break;
        }
    }

    destroyStudent(idTree);
    idTree = BST_Destroy(idTree);
    nameTree = BST_Destroy(nameTree);
    return 0;
}

/*
 * printStudent takes in a void pointer to data
 * to be printed.
 */
void printStudent(void *data)
{
    STU student = *((STU*)data);

    printf("PIN:  %d\n", student.id);
    printf("Name: %s\n", student.name);
    printf("Gpa:  %.1f\n\n", student.gpa);
}

/*
 * printByID takes in the idTree. It prints all
 * data in the tree by ID.
 */
void printByID(BST_TREE* idTree)
{
    BST_Traverse(idTree, printStudent);    
}

/*
 * printByName takes in the nameTree. It prints 
 * all data in the tree by name.
 */
void printByName(BST_TREE* nameTree)
{
    BST_Traverse(nameTree, printStudent);
}

/*
 * searchID takes in the idTree. It searches the
 * tree for an ID that is requested by the user.
 */
void searchID(BST_TREE* idTree)
{
    STU student;
    STU* studentPtr;

    printf("Enter ID to be searched: \n");
    scanf("%d", &student.id);
    FLUSH;

    studentPtr = BST_Retrieve(idTree, &student);
    if(studentPtr)
    {
        printf("ID:   %d\n", studentPtr->id);
        printf("Name: %s\n", studentPtr->name);
        printf("Gpa:  %.1f\n", studentPtr->gpa);
    }else printf("ID not found.\n");

}

/*
 * searchName takes in the nameTree. It searches
 * for all names in the tree requested by the user.
 */
void searchName(BST_TREE* nameTree)
{
    char buffer[MAXLINE];
    char first[MAXLINE];
    char last[MAXLINE];
    STU student;

    printf("Enter name to be searched.");

    printf("\nFirst name: ");
    scanf("%s", first);

    printf("Last name: ");
    scanf("%s", last);
    FLUSH;

    sprintf(buffer, "%s, %s", last, first);
    if((student.name = (char *)malloc(strlen(buffer) + 1)) == NULL)
        printf("\nError with malloc.\n"), exit(1);
    strcpy(student.name, buffer);

    if(!(BST_RetrieveAll(nameTree, &student, printStudent)))
        printf("No such student with that name.\n");
    free(student.name);
}

/*
 * addStudent takes in the idTree as well as the nameTree.
 * It gets the information to be added from the user and 
 * inserts them into their corresponding trees.
 */
void addStudent(BST_TREE* idTree, BST_TREE* nameTree)
{
    STU* new;
    char buffer[MAXLINE];
    char first[MAXLINE];
    char last[MAXLINE];

    if((new = (STU *)malloc(sizeof(STU))) == NULL)
        printf("Error creating new node.\n"), exit(1);

    while(printf("ID: "), scanf("%d", &new->id), BST_Retrieve(idTree, new) != NULL)
    {
        FLUSH;
        printf("ID already exists.\n");
    }

    printf("\nFirst name: ");
    scanf("%s", first);
    printf("\nLast name: ");
    scanf("%s", last);

    sprintf(buffer, "%s, %s", last, first);

    if((new->name = (char *)malloc(strlen(buffer) + 1)) == NULL)
        printf("Error creating space for name.\n"), exit(1);

    strcpy(new->name, buffer);

    printf("\nGpa: ");
    scanf("%f", &new->gpa);
    FLUSH;

    BST_Insert(idTree, new);
    BST_Insert(nameTree, new);
}   

/*
 * breadthTrav takes in the idTree. It does a breadth first
 * traversal and prints all data in the idTree bst.
 */
void breadthTrav(BST_TREE* idTree)
{
    BFTraversal(idTree, printStudent);
}

/*
 * buildTreeManager takes in the address of idTree and the 
 * address of nameTree. It reads from the file and fills
 * the tree with data from the file.
 */
void buildTreeManager(BST_TREE** idTree, BST_TREE** nameTree)
{
    FILE *fptr;
    char buffer[MAXLINE];
    STU* new;
    char* id, *name, *gpa;

    *idTree = BST_Create(compID);
    *nameTree = BST_Create(compName);

    fptr = fopen("gpa.txt", "r");

    while(fgets(buffer, MAXLINE, fptr))
    {

        if((new = (STU*)malloc(sizeof(STU))) == NULL)
            printf("Memory overflow in insert.\n"), exit(1);

        id = strtok(buffer, " ");
        name = strtok(NULL, ";");
        gpa = strtok(NULL, "\n");

        if((new->name = (char *)malloc(strlen(name) + 1)) == NULL)
            printf("Error.\n");

        sscanf(id, "%d", &new->id);
        strcpy(new->name, name);
        sscanf(gpa, "%f", &new->gpa);

        BST_Insert(*idTree, new);
        BST_Insert(*nameTree, new);
    }
    fclose(fptr);
}

/*
 * getOption gets the option from the user. It does not take 
 * in anything. It returns the user's desired option.
 */
char getOption()
{
    char option;

    printMenu();

    do{
        printf("Enter option: \n");
        scanf("%c", &option);
        FLUSH; 
        option = toupper(option);
    }while(strchr("ABCDEFMQ", option) == NULL);
    return option;
}

/*
 * printMenu prints the menu.
 */
void printMenu()
{
    printf("\n=============== MENU ===============\n");
    printf(" A   Print by ID\n");
    printf(" B   Print by name\n");
    printf(" C   Search by ID\n");
    printf(" D   Search by name\n");
    printf(" E   Add student\n");
    printf(" F   Breadth first traversal\n");
    printf(" M   Print menu\n");
    printf(" Q   Quit\n");
}

/*
 * compID takes in stu1 and stu2 to be compared. It
 * is the compare function used to compare IDs. It
 * returns -1 if less than, 0 if equal and 1 if 
 * greater.
 */
int compID(void* stu1, void* stu2)
{
    STU s1 = *((STU*)stu1);
    STU s2 = *((STU*)stu2);

    if(s1.id < s2.id)
        return -1;
    if(s1.id == s2.id)
        return 0;
    return 1;
}

/*
 * compName takes in stu1 and stu2 of data to be
 * compared. It returns less than 1, greater than
 * 1 or 0 depending on the comparison.
 */
int compName(void* stu1, void* stu2)
{
    STU s1 = *((STU*)stu1);
    STU s2 = *((STU*)stu2);

    return strcmp(s1.name, s2.name);       
}

/*
 * destroyStudent takes in the tree. It
 * frees the STU struct that is being pointed
 * to by the nodes in the BST.
 */
void destroyStudent(BST_TREE* tree)
{
    BST_Traverse(tree, freeStudent); 
}

/*
 * freeStudent is a function to be used to free
 * data in the BST. It frees the name that was
 * allocated and then then the node itself.
 */
void freeStudent(void* dataPtr)
{
    STU* student = (STU*)dataPtr;
    free(student->name);
    free(student);
}

/*
 * Basic doubly linked list prototype declarations and type definitions.
 */

typedef struct listNode NODE;

typedef struct
{
    char id[3];
    char *country;
    char *name;
}COUNTRY;

typedef struct listNode
{
    COUNTRY *pcountry;
    NODE *forw;
    NODE *back;
};

typedef struct
{
    int count;
    NODE *head;
    NODE *tail;
} LIST;

LIST *createList();
int insertList(LIST *list, char *dataPtr);
int deleteNode(LIST *list, char *toDelete);
NODE *searchList(LIST *list, char *toFind);
void printForw(LIST *list);
void printBack(LIST *list);
int listCount(LIST *list);
LIST *destroyList(LIST *list);



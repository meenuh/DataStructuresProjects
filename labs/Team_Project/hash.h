typedef struct{
    
}ANIMAL;

typedef struct{
    ANIMAL ani;

}HASH_ITEM;

typedef struct{
    int count;
    int maxChain;
    HASH_ITEM *table;
}HASH;

unsigned int generateKey(char* id, unsigned int size);

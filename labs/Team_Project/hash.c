#define RATIO 2654435761            //golden ratio

unsigned int generateAddr(char* id, unsigned int size)
{
    unsigned int key;

    sscanf(id, "%d", &key);

    return (key * RATIO) % size;
}



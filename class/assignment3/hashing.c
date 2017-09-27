/*********************************************************

   Hashing - 10 Points

   Given Hash function:
      -> key - year
	  -> hash method: modulo division
      -> collisions: not solved, just counted!

   REQUIREMENTS

   I. (2Points)
   Run the program with three different sizes: 10, 13, and 17,
   Save each output. What did you notice? There are much fewer collisions
   when using 13 and 17 as the size.

   II.(2 Points)
   Use an overflow array to store all synonyms (just the years).
   Print the collision list.

   III.(4 Points)
   Change the hash function:
      -> key - title
	  -> suggested hash method:
	      add ASCII values of all characters except spaces
		  followed by modulo-division
	  -> save all collisions to an overflow array
	  Then run the program once, size 10, and save its output.

   IV.(2 Points) Use a parallel array to store the number of
   collisions for each home address.
   Run the program with three different sizes: 10, 13, and 17,
   Save each output. What did you notice?
    I actually didn't notice much of a difference after but it
    there were slightly fewer collisions.

  Name: Mina Yi
  Date: Nov 10, 2011

*********************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hash( int key, int size );
int altHash(char *key, int size);
//#define SIZE 10
//#define SIZE 13
#define SIZE 17




int main (void)
{
	FILE *fpIn;
	int hashTable[SIZE] = {0};
    int yearCol[SIZE] = {0};
    int paraCol[SIZE] = {0};
	int i, c = 0;
	char line[100];
	int year;
	int index;

	// create the hash table
	fpIn = fopen( "pictures.txt", "r" );
	if( !fpIn )
		printf("Error opening the input file!\n"), exit(101);

	while ( fgets( line, sizeof(line), fpIn) )
	{
		printf( "%s", line );
		sscanf( line, "%d", &year );
		index = hash(year, SIZE);
        //index = altHash(line, SIZE);
		if( hashTable[index] == 0 )
		{
			printf("\t %d inserted at index %d\n", year, index);
			hashTable[index] = year;
		}
		else
		{
			printf( "\tCollision!\n" );
            yearCol[c] = year;
			c++;
            paraCol[index]++;
		}
	}

	printf( "\n\n %d collisions\n", c );

	fclose(fpIn);

	// print the hash table
	for( i = 0; i < SIZE; i++ )
	{
		printf( "%2d %4d\n", i, hashTable[i] );
	}

    //print number of collisions
    printf("\n%s\n", "Collision Data");
    printf("%5s %5s\n", "Index", "Count");
    for(i = 0; i < SIZE; i++)
    {
        if(paraCol[i])
            printf("%5d %5d\n", i, paraCol[i]);
    }

    printf("\nYears: \n");
    for(i = 0; i < c; i++)
        printf("%d\n", yearCol[i]);

    return 0;
} 

/* =========================== */
int hash( int key, int size )
{
	return key % size;
}

int altHash(char *key, int size)
{
    char *mover;
    int total = 0;

    for(mover = key; *mover; mover++)
    {
        if(*mover != ' ')
            total += *mover;
    }
    return total % size;
}


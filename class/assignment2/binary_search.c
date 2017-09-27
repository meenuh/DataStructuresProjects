/*
    Given the iterative binary search function, 
    write a recursive binary search function

*/
#include <stdio.h>

#define MAX_ARY_SIZE 100

int binarySearch (int  list[], int size, int first, int last, int target, int *locn);

int main (void) 
{
	int i;
	int locn;
	int target;
    int length = 12;
	int	ary[MAX_ARY_SIZE] = 
        {  4,  7,  8, 10, 14, 21, 22, 36, 62, 77, 81, 91 };
	              
	printf("Data: ");
	for (i = 0; i < length; i++)
		printf("%3d", ary[i]);
	
	printf("\n\nEnter a key for search     : ");
	scanf("%d", &target);	
	do
	  {
	   if (binarySearch (ary, length, 0, length - 1, target, &locn))
	       printf("%3d found at location:       %2d\n", target, locn);
	   else
	       printf("%3d NOT found:       \n", target);
	   printf("Enter next key <-1> to quit: ");
	   scanf("%d", &target);	
	  } while (target != -1);

	printf("End of search.\n");
	return 0;
}// main 

/*	==================== binarySearch ====================
	Search an ordered list using Binary Search 
	   Pre   list must contain at least one element
	         size is the actual number of elements in the list
	         target is the value of element being sought
	   Post  FOUND: locn assigned index to target element 
	                return 1 (found)
	         NOT FOUND: locn = element below or above target 
	                    return 0 (not found)
*/
int binarySearch (int  list[], int  size, int first, int last, int  target, int *locn)
{
	int mid = (first + last)/2;

    if(first <= last)
    {
        if (target > list[mid])       // look in upper half 
            return binarySearch(list, size, mid + 1, last, target, locn);
        else if (target < list[mid])  // look in lower half 
            return binarySearch(list, size, first, mid - 1, target, locn);
    }
    *locn = mid;
    return target == list[mid];
}// binarySearch	

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *join_arrays(unsigned int size1, int *a1, unsigned int size2, int *a2, unsigned int size3, int *a3)
{
	unsigned int comb_size = size1 + size2 + size3;
	int *joined = malloc(comb_size * sizeof(int));
	
		
	int *ptr = joined;

	int i;

	for (i = 0; i< size1; i++)
	{
		*ptr = *a1;
		ptr++;
		a1++;
	}
	for (i = 0; i< size2; i++)
	{
		*ptr = *a2;
		ptr++;
		a2++;
	}	
	for (i = 0; i< size3; i++)
	{
		*ptr = *a3;
		ptr++;
		a3++;
	}	
	return joined;
}
int main(void)
{
    /* testing exercise. Feel free to modify */
    int a1[] = { 1, 2, 3, 4, 5 };
    int a2[] = { 10, 11, 12, 13, 14, 15, 16, 17 };
    int a3[] = { 20, 21, 22 };

    int *joined = join_arrays(5, a1, 8, a2, 3, a3);

    for (int i = 0; i < 5 + 8 + 3; i++) {
        printf("%d  ", joined[i]);
    }
    printf("\n");
    
    free(joined);

    return 0;
}
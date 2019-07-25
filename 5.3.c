#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int *create_dyn_array(unsigned int n)
{
	int buffer;
	int *dyn_array = malloc(n * sizeof(int));
	int readsucc;
	for(int i = 0; i<n;i++)
	{
		readsucc = 0;
		while (readsucc == 0)
		{
			printf("Enter next value: ");
			readsucc = scanf("%d", &buffer);
		}
		dyn_array[i] = buffer;
	}
	return dyn_array;
}	
	
int *add_dyn_array(int *arr, unsigned int num, int newval)
{
	int *new_arr = realloc(arr, (num + 1)*sizeof(int));
	new_arr[num] = newval;
	return new_arr;
}



//don't include this part in the final version!!!!

//int main()
//{
//	unsigned int dynsize = 6;
//	int *dyn_array = create_dyn_array(dynsize);	
//	int *new_dyn = add_dyn_array(dyn_array, dynsize, 420);
//	free(new_dyn);
//	system("pause");
//	return 0;
//}
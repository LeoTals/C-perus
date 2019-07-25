#include <stdio.h>

int array_sum(int *array, int count)
{
	int sum = 0;
	for (int i = 0; i < count; i++)
	{
		sum += array[i];
	}
	return sum;
}

int array_reader(int *vals, int n)
{
	int readstat = 0;
	int num = 0;
	do 
	{
		readstat = scanf("%d", vals);
		if (readstat != 0) { num++; vals++; }
	} while (readstat != 0);
	return num;
}
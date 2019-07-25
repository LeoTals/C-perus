#include <stdio.h>

void sort(int *start, int size)
{
	unsigned int operations;
	do
	{
		operations = 0;
		for (int i = 0; i < (size-1); i++) 
		{
			int item = start[i];
			int next_item = start[i + 1];
			if (next_item < item)
			{
				start[i] = next_item;
				start[i + 1] = item;
				operations++;
			}
		}
	} while (operations > 0);

}
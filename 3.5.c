#include <stdio.h>

unsigned int arraylen(const char *array)
{
	unsigned int charcount = 0;
	while (array[charcount] != 0)
	{
		charcount++;
	}
	return charcount;
}

void countchars(const char *array, unsigned int *counts)
{
	unsigned int charcount = 0;
	unsigned int asciinum;
	while (array[charcount] != 0)
	{
		asciinum = array[charcount];
		counts[asciinum]++;
		charcount++;
	}
}




//void printcounts(int min, int max, const unsigned int *counts) {
//	for (int i = min; i <= max; i++) {
//		printf("%c: %u  ---  ", i, counts[i]);
//		if ((i - min + 1) % 6 == 0)
//			printf("\n");
//	}
//}

//void printarray(const char *array) {
//	printf("{ ");
//	while (*array) {
//		printf("'%c',", *array);
//		array++;
//	}
//	printf("0 }");
//}

//int main()
//{
//	unsigned int counts[256] = { 0 };
//
//	char sample[] = { 'a','b','r','a','c','a','d','a','b','r','a',0 };
//
//	printf("%s, length: %u\n", sample, arraylen(sample));
//	countchars(sample, counts);
//	printcounts('a', 'z', counts);
//	system("pause");
//	return 0;
//}
#include <stdio.h>
#include <string.h>


int num_substr(const char *str, char *sub)
{
	int count = 0;
	char *ptr = strstr(str, sub);
	while (ptr != NULL)
	{
		count++;
		ptr++;
		ptr = strstr(ptr, sub);
	}
	return count;
}



//int main()
//{
//	printf("Giving function num_substr strings \"one two one twotwo three\", \"two\"\n");
//	int count = num_substr("one two one twotwo three", "two");
//	printf("%d\n", count);
//	system("pause");
//}
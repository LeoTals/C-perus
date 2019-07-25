#include <stdio.h>
#include <string.h>
#include <ctype.h>


char *my_toupper(char *dest, const char *src)
{
	int c = 0;
	for (int i = 0; src[i] != '\0'; i++)
	{
		if (isalpha(src[i]) != 0)
		{
			dest[c] = toupper(src[i]);
		}
		else if (src[i] == '?')
		{
			dest[c] = '!';
		}
		else if (src[i] == '.')
		{
			dest[c] = '!';
			c++;
			dest[c] = '!';
			c++;
			dest[c] = '!';
		}
		else { dest[c] = src[i]; }

	//	printf("c on %d --- i on %d", c, i);
	//	printf("     %c\n", dest[c]);

		c++;

	}
	dest[c] = '\0';
	return dest;
}



//#include <stdio.h>  // for printf
//#include <string.h>  // for memset
//#include <ctype.h>  // for toupper

//int main(void)
//{
//	char dest[200];
//
//	/* The following helps detecting string errors, e.g. missing final nil */	
//	memset(dest, '#', 199);
//	dest[199] = 0;
//
//	printf("%s",
//		my_toupper(dest,
//			"Would you like to have a sausage? It will be two euros. Here you are.\n"));
//	printf("\n");
//	printf("%s",
//		my_toupper(dest,
//			"Madam, where are you going? The health care center is over there.\n"));
//	printf("\n");
//	system("pause");
//	return 0;
//}
#include <stdio.h>
#include <ctype.h>

int count_isalpha(const char *str)
{
	int alpha = 0;
	while (*str != '\0')
	{
		if (isalpha(*str) != 0)
		{
			alpha++;
		}
		str++;
	}
	return alpha;
}

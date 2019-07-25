#include <stdio.h>
#include <ctype.h>


void qstr_print(const char *s)
{
	while (*s != '?')
	{
		printf("%c", *s);
		s++;
	}
}

unsigned int qstr_length(const char *s)
{
	int len = 0;
	while (*s != '?')
	{
		len++;
		s++;
	}
	return len;
}

int qstr_cat(char *dst, char *src)
{
	int end_dst = 0;
	while (dst[end_dst] != '?')
	{
		end_dst++;
	}
	int ch_cpyd = 0; 

	while (src[ch_cpyd] != '?')
	{
		dst[end_dst] = src[ch_cpyd];
		end_dst++;
		ch_cpyd++;

	}
	dst[end_dst] = '?';

	return qstr_length(dst);
}

const char *qstr_strstr(const char *str1, const char *str2)
{
	int k = 0;
	int j = 0;
	const char *nl = NULL;
	for (int i = 0; str1[i] != '?'; i++)
	{
		k = 0;
		for (j = 0; str2[j] != '?'; j++)
		{
			if (str2[j] == str1[i + j])
			{
				k++;
			}
		}
		if (k == j)
		{
			const char *ptr = str1 + i;
			return ptr;
		}
	}
	return nl;
}
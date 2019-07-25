#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *delete_comments(char *input)
{
	unsigned int alloc_size = strlen(input)*sizeof(char);
	char *output = calloc(strlen(input)+1,sizeof(char));
	char *ptr = output;
	unsigned int rem_char = 0; //removed characters
	char *original_input = input;
	while (*input != '\0')
	{
		char buffer = *input;
		char next = *(input+1);
		if (buffer =='/')
		{
			switch(next)
			{
			case('/'):
				do {
					input++;
					rem_char++;
				} while(*input !='\n');
				input++;
				rem_char++;
				break;
			case('*'):
				do {
					input++;
					rem_char++;
				} while(!((*input == '*')&&(*(input+1)=='/')));
				input++;
				input++;
				rem_char++;
				rem_char++;
				break;
			default: //redundant code, but decided to add so that 'switch' can't break.
				*ptr = buffer;
				input++;
				ptr++;
			}
		}
		else
		{
			*ptr = buffer;
			input++;
			ptr++;
		}
	}
		ptr++;
		*ptr = '\0';
	unsigned int newsize = 1+alloc_size - rem_char;
	char *n_output = realloc(output,newsize);
	free(original_input);
	return n_output;
}
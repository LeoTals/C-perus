#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *mystrcat(char *dest, const char *src)
{
	int strsize = strlen(dest) + strlen(src) + 1; //added 1 for the 'End of String' character
	dest = realloc(dest, strsize * sizeof(char));
    char *origdest = dest;
    while(*dest) {
        dest++;
    }

    while (*src) {
        *dest = *src; 
		dest++;
		src++; 	// Kopioi merkin ja sitten kasvattaa osoittimia
    }
    *dest = 0;

    return origdest;
}

int main(void)
{
    char *str = malloc(7);
    strcpy(str, "Aatami");

    str = mystrcat(str, "Beetami");
    printf("%s\n", str);
    free(str);
}
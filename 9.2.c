#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "filebasics.h"


int print_file_and_count(const char *filename)
{
	FILE *f = fopen(filename,"r");
	if(!f){
		return -1;
	}
	int printedchar = 0;
	char *ptr = NULL;
	char s[100];
	do{
		ptr = fgets(s, 100, f);
		if(ptr){
			printedchar += strlen(s);
			printf("%s",ptr);
		}
	}while(ptr);
	fclose(f);
	return printedchar;
}

char *difference(const char* file1, const char* file2)
{
	FILE *f1 = fopen(file1,"r");
	if(!f1){
		printf("Error opening file 1.\n");
		return NULL;
	}
	FILE *f2 = fopen(file2,"r");
	if(!f2){
		printf("Error opening file 2.\n");
		fclose(f1);
		return NULL;
	}
	char *ptr1 = NULL;
	char *ptr2 = NULL;
	char s1[100];
	char s2[100];
	char *result = NULL;
	ptr1 = fgets(s1,100,f1);
	ptr2 = fgets(s2,100,f2);
	while(ptr1 && ptr2){
		printf("%s\n%s",s1,s2);
		printf("\t%d\n",strcmp(s1,s2));
		if (strcmp(s1,s2)!=0){
			int comb_len = strlen(s1) + strlen(s2);
			result = calloc(comb_len+9,sizeof(char));
			strcpy(result,s1);
			strcat(result,"----\n");
			strcat(result,s2);
			fclose(f1);
			fclose(f2);
			return result;
		}
		ptr1 = fgets(s1,100,f1);
		ptr2 = fgets(s2,100,f2);
	}
	fclose(f1);
	fclose(f2);
	return NULL;
}

int main(void)
{
    printf("--- Printing file:\n");
    int t = print_file_and_count("testifile.c");
    if(t<0)
        printf("Opening failed!\n");

    printf("--- Printed %d characters\n", t);

    char* diff = difference("testifile.c", "testifile2.c");
    printf("\n--- Difference:\n");
    printf("%s", diff);

    free(diff);

    return 0;
}
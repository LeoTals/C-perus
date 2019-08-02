#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "filestats.h"

int line_count(const char *filename)
{
	int linecount=0;
	int lastchar = 99999;
	FILE *f = fopen(filename,"r");
	if(!f){
		return -1;
	}
	char a = fgetc(f);
	while (a!= EOF){
		if (a=='\n'){
			linecount++;
		}
		lastchar = a;
		a = fgetc(f);
	}
	if((lastchar != 99999)&&(lastchar !='\n')){
		linecount++;
	}
	fclose(f);
	return linecount;
}

int word_count(const char *filename)
{
	FILE *f = fopen(filename,"r");
	if(!f){
		return -1;
	}
	int alpha_w = 0;
	int word_c = 0;
	int check_this = 0;
	check_this = fgetc(f);
	//printf("%c",check_this);
	while (check_this != -1){
		if (ferror(f) !=0){
			printf("An error has occurred.\n");
			return -1;
		}
		if (isalpha(check_this) != 0){
			alpha_w++;
			//printf("Found alphabet - %d\n",alpha_w);
		}
		else if(isspace(check_this)!=0){
			//printf("Found a whitespace.\n");
			if(alpha_w >0){
				word_c++;
				//printf("Registered as a word - %d\n",word_c);
			}
			alpha_w = 0;
		}
		check_this = fgetc(f);
		//printf("%c",check_this);
	}
	if (alpha_w >0){
		word_c++;
	}
	fclose(f);
	return word_c;
}

int main(int argc, char *argv[])
{
    /* You can modify this file as needed, for example to test different
     * files. If you run on command line, this function optionally reads
     * the filename from command line, if one is included. */
    char *filename = "testi.txt";
    if (argc > 1) {
        filename = argv[1];
    }
    
    printf("Line count: %d\n", line_count(filename));
    
    printf("Word count: %d\n", word_count(filename));

    return 0;
}
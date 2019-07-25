#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void print_split_string(char** split_string)
{
	unsigned int i = 0;
	while(split_string[i]){
		printf("%s\n",split_string[i]);
		i++;
	}
}

/*int check_split(char* string, const char* split)
{
	int i = 0;
	int j = 0;
	int s = 0;
	while(string[i] != '\0')
	{
		j = 0;
		while(split[j] != '\0')
		{
			if(string[i+j] != split[j]){
				break;
				}
			else{
				j++;
			}
			
		}
		if(j == strlen(split)){
			return i;
		}
		i++;
	}
	return NULL;
		
}*/


char** split_string(const char* str, const char* split)
{
	int i = 0;
	int stringsize = strlen(str)+1;
	char *string_ = calloc(stringsize,sizeof(char));
	char *string = string_;
	strcpy(string,str);
	/*printf("String is:%s\n",string); //test*/
	char** split_string = calloc(1,sizeof(char*));
	char** new_array;
	unsigned int size = 0;
	split_string[0] = NULL;
	char *scanpoint = strtok(string,split);
/*	printf("String is:%s\n",string); //test
	printf("Scan  is:%s\n",scanpoint); //test*/
	while(scanpoint){
		i++;
		size = strlen(scanpoint)+1;
		new_array = realloc(split_string,(i+1)*sizeof(char*));
		new_array[i-1]= calloc(size,sizeof(char));
		new_array[i]=NULL;
		strcpy(new_array[i-1],scanpoint);
/*		printf("String is:%s\n",string); //test
		printf("Scan  is:%s\n",scanpoint); //test*/
		split_string = new_array;
		scanpoint = strtok(NULL,split);
		
	}
	free(string_);
	return split_string;
}



void free_split_string(char** split_string)
{
	unsigned int i = 0;
	while(split_string[i]){
		free(split_string[i]);
		i++;
	}
	free(split_string[i]);
	free(split_string);
}


int main()
{
	const char str[26] = "Merkkijono joka pilkotaan";
	const char split[2] = " ";
	char **string = split_string(str,split);
	print_split_string(string);
	free_split_string(string);
	
	const char str2[] = "One. .more. .test. .for. .string. .splitting.";
	const char split2[] = ". .";
		char **string2 = split_string(str2,split2);
	print_split_string(string2);
	free_split_string(string2);
	return 1;
}

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "aaltoshop.h"

int output_binary(const char* filename, Product* shop) // TOIMII
{
	FILE *f;
	f = fopen(filename,"wb");
	if(!f){
		return 1;
	}
	int i=0;
	while(shop[i].name[0]!='\0'){
		fwrite(shop+i,1,sizeof(Product),f);
		i++;
	}
	fclose(f);
	return 0;
}



Product* read_binary(const char* filename){
	FILE *f;
	f = fopen(filename,"rb");
	if(!f){
		return NULL;
	}
	int i=0;
	Product* array = calloc(1,sizeof(Product));
	Product* ptr = array;
	do{
		fread(ptr+i+1,1,sizeof(Product),f);
		i++;
		Product* newarray = realloc(array,(i+1)*sizeof(Product));
		array = newarray;
	}while(!feof(f));
	Product* finalarray = realloc(array,(i+1)*sizeof(Product));
	finalarray[i+1].name[0] = '\0';
	
	fclose(f);
	return finalarray;
}

int output_plaintext(const char* filename, Product* shop) // TOIMII
{
	FILE *f;
	f = fopen(filename,"w");
	if(!f){
		return 1;
	}
	int i=0;
	while((shop[i].name != NULL) && (shop[i].name[0] != '\0')){
	fprintf(f,"%s %f %d\n", shop[i].name,shop[i].price,shop[i].in_stock);
	i++;
	}
	fclose(f);
	return 0;
}

Product* read_plaintext(const char* filename) // TOIMII
{
	FILE *f;
	f = fopen(filename,"r");
	if(!f){
		return NULL;
	}
	Product* array = calloc(1,sizeof(Product));
	int i=0;
	int gotvalues = 0;
	do{
		gotvalues = fscanf(f,"%s %f %d\n",array[i].name,&array[i].price,&array[i].in_stock);
		i++;
		Product* newarray = realloc(array, (i+1)*sizeof(Product));
		array = newarray;
	}while (gotvalues ==3);
	array[i].name[0] = '\0';
	return array;
}


int main()
{
	Product* arr = calloc(3,  sizeof(Product));
	strcpy(arr[0].name, "peanut_butter");
	arr[0].price = 5.2;
	arr[0].in_stock = 4;
	strcpy(arr[1].name, "milk");
	arr[1].price = 1.1;
	arr[1].in_stock = 42;
	arr[2].name[0] = 0;
	
	output_binary("testi", arr);
	
	Product* arr2;
	arr2 = read_binary("testi");
	output_plaintext("testi.txt", arr2);

	Product* arr3 = NULL;

	arr3 = read_plaintext("testi.txt");

	for(int i = 0; i < 3; i++)
	{
		printf("%s %f %d\n", arr3[i].name, arr3[i].price, arr3[i].in_stock);
	}
	free(arr);
	free(arr2);
	free(arr3);

	return 0;
}
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "shopfunctions.h"

int compareAlpha(const void* a, const void* b)
{
	const Product *pa = a;
	const Product *pb = b;
	int cmp = strcmp(pa->name,pb->name);
	return cmp;
}
int compareNum(const void* a, const void* b)
{
	const Product *pa = a;
	const Product *pb = b;
	int cmp = 0;
	if(pa->in_stock == pb->in_stock){
		cmp = compareAlpha(a,b);
	}
	else if(pa->in_stock > pb->in_stock){
		cmp = -1;
	}
	else{
		cmp = 1;}
	return cmp;
}
Product* findProduct(Product* p_array, const char* searchkey, int (*cmp)(const void*, const void*))
{
	for(int i = 0;p_array[i].name[0] != '\0';i++){
		if(cmp(searchkey,(p_array[i].name)) == 0){
			return &p_array[i];
		}
	}
	return NULL;
}

void printProducts(Product* array)
{
	int i = 0;
	while(array[i].name[0] != 0)
	{
		printf("product: %s price: %f in stock: %d\n", array[i].name, array[i].price, array[i].in_stock);
		i++;
	}
}

int main()
{
	Product array[6] = {
	{"peanut butter", 1.2, 	5},
	{"cookies", 	 12.3, 23},
	{"cereals", 	  3.2, 12},
	{"bread",	  2.7, 12},
	{"butter", 	  4.2,  5},
	{"\0",		0.0, 0}
	};

	qsort(array, 5, sizeof(Product), compareAlpha);
	printf("sorted lexically:\n");
	printProducts(array);
	
	Product* search = findProduct(array, "cookies", compareAlpha);
	if(search)
	{
		printf("Found product:\n");
		printf("%s\n", search->name);
	}
	search = findProduct(array, "nonexistent", compareAlpha);
	if(search)
	{
		printf("Found product:\n");
		printf("%s\n", search->name);
	}
	else printf("Product not found!\n");

	qsort(array, 5, sizeof(Product), compareNum);
	printf("sorted by in stock:\n");
	printProducts(array);

	return 0;
}
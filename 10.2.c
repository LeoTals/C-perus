#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


int myprint(const char *str, ...)
{
	char muotoilum = '&';
	va_list numbers;
	int num_of_mm = 0;
	va_start(numbers, str);
	for(int i=0;str[i]!='\0';i++){
		if(str[i]==muotoilum)
		{
			int replace = va_arg(numbers, int);
			printf("%d",replace);
			num_of_mm ++;
		}
		else{
			printf("%c",str[i]);
		}
	}
	va_end(numbers);
	return num_of_mm; 
	}
	

int main(void)
{
	myprint("&&&&&&&&&&\n",1,2,3,4,5,6,7,8,9,0);
   /* myprint("Hello!\n");
    myprint("Number: &\n", 5);
    myprint("Number one: &, number two: &\n", 120, 1345);
    int ret = myprint("Three numbers: & & &\n", 12, 444, 5555);
    myprint("I just printed & integers\n", ret);*/

    return 0;
}
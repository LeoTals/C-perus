#include <stdio.h>

int draw_triangle(unsigned int size)
{
	unsigned int lines = 0;
	unsigned int rows = 0;
	for (lines = 1; lines <= size; lines++) {
		for (rows = 1; rows <= size; rows++) {
			if (rows > (size - lines)) {
				printf("#");
			}
			else {
				printf(".");
			}
		}
		printf("\n");
	}
	return 0;
}

//int main()
//{
	//	printf("Enter a positive integer.\n");
		//unsigned int size = 0;
		//int result = scanf("%u", &size);
		//if (result == 1) {
		//	draw_triangle(size);
		//}
		//else {
		//	printf("ERROR: Invalid input.\n");
		//}
	//system("pause");
//}
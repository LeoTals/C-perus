#include <stdio.h>


int simple_multiply() 
{
	int var1 = 0, var2 = 0; //define variables
	scanf("%d", &var1);
	scanf("%d", &var2);
	int res = var1 * var2; //multiply
	printf("%d * %d = %d\n", var1, var2, res);
	return 0;
}
float simple_math()
{
	float var1 = 0, var2 = 0;
	char op = 'N';
	float res;
	int err = 1;
	scanf("%f", &var1);
	scanf("%s", &op);
	scanf("%f", &var2);
	switch (op) {
	case '+':
		res = var1 + var2;
		err = 0;
		break;
	case '-':
		res = var1 - var2;
		err = 0;
		break;
	case '*':
		res = var1 * var2;
		err = 0;
		break;
	case '/':
		if (var2 == 0) {
			res = 0;
		}
		else {
			res = var1 / var2;
		}
		err = 0;
		break;
	}
	if (err == 1) 
	{
		printf("ERR");
	}
	else
	{
		printf("%.1f\n", res);
	}
	return 0;
}

//int main()
//{
//	printf("Running simple_multiply;");
//	simple_multiply();
//	printf("simple_multiply done. Running simple_math");
//	simple_math();
//	printf("Press ENTER key to Continue\n");
//	getchar();
//}
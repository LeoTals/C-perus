#include <stdio.h>
#include <ctype.h>

void ascii_chart(char min, char max)
{
	int cycle;
	int linel=0;
	
	int isprintable;
	for (cycle = min; cycle <= max; cycle++) {
		char character = cycle;
		
		printf("%3d ",cycle);
		printf("0x");
		if (cycle < 16) { printf("0"); }
		printf("%x ", cycle);
		
		isprintable = isprint(cycle); 
		if (isprintable == 0) { printf("?"); }
		else { printf("%c", character); }
		linel++;
		if (linel == 4) {
			printf("\n");
			linel = 0;
		}
		else { printf("\t"); }

	}
}
//int main()
//{
//	int min, max;
//	char minc, maxc;
//	int succ;
//	printf("Enter a min and a max.");
//	succ = scanf("%d %d", &min, &max);
//	if (succ = !2) { printf("ERROR: Invalid input"); }
//	else
//	{
//		minc = min;
//		maxc = max;
//		ascii_chart(minc, maxc);
//	}
//	printf("\n");
//	system("pause");
//	
//}
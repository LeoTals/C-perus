#include <stdlib.h>
#include "fraction.h"
#include <stdio.h>

/* Algorithm for determining greatest common divisor, needed in (d) */
/* The function returns gcd between the two parameters, u and v */
/* Taken from http://en.wikipedia.org/wiki/Binary_GCD_algorithm */
unsigned int gcd(unsigned int u, unsigned int v)
{
    // simple cases (termination)
    if (u == v)
        return u;
 
    if (u == 0)
        return v;
 
    if (v == 0)
        return u;
 
    // look for factors of 2
    if (~u & 1) // u is even
    {
        if (v & 1) // v is odd
            return gcd(u >> 1, v);
        else // both u and v are even
            return gcd(u >> 1, v >> 1) << 1;
    }
 
    if (~v & 1) // u is odd, v is even
        return gcd(u, v >> 1);
 
    // reduce larger argument
    if (u > v)
        return gcd((u - v) >> 1, v);
 
    return gcd((v - u) >> 1, u);
}

/* Allocates a new Fraction from heap */
Fraction* setFraction(unsigned int numerator, unsigned int denominator)
{
//	unsigned int *n = malloc(sizeof(unsigned int));
//	unsigned int *d = malloc(sizeof(unsigned int));
//	*n = numerator;
//	*d = denominator;
	Fraction *newfrac = malloc(sizeof(Fraction));
	newfrac->num=numerator;
	newfrac->den=denominator;
	//*newfrac = {numerator,denominator};
	return newfrac;
	
}

/* Returns the numerator of the given fraction */
unsigned int getNum(const Fraction *f)
{
	return f->num;
}
/* Returns the denominator of the given fraction */
unsigned int getDenom(const Fraction *f)
{
	return f->den;
}

/* Releases the Fraction from heap */
void freeFraction(Fraction *f)
{
//	free(f->num);
//	free(f->den);
	free(f);
}
/* Compares two fractions */
int compFraction(const Fraction *a, const Fraction *b)
{
	unsigned int num_A = getNum(a) * getDenom(b);
	unsigned int num_B = getNum(b) * getDenom(a);
	if (num_A < num_B){return -1;}
	if (num_A > num_B){return 1;}
	else { return 0;}
}

/* Adds the given fractions and creates new object for the result */
Fraction* addFraction(const Fraction *a, const Fraction *b)
{
	unsigned int new_num = (getNum(a) * getDenom(b)) + (getNum(b) * getDenom(a));
	unsigned int new_Denom = getDenom(a) * getDenom(b);
	Fraction *newfraction = setFraction(new_num,new_Denom);
	return newfraction;
	
}

/* Reduce fraction */
void reduceFraction(Fraction *val)
{
	unsigned int n = getNum(val);
	unsigned int m = getDenom(val);
	unsigned int x;
	while(gcd(n,m)!=1)
	{
		x = gcd(n,m);
		n = n/x;
		m = m/x;
		//printf("n = %u   m = %u   x = %u\n",n,m,x);
	}
	val->num = n;
	val->den = m;
}

/* Print fraction (optional, does not give points) */
void printFraction(const Fraction *val)
{
	unsigned int n = getNum(val);
	unsigned int m = getDenom(val);
	printf("%u/%u\n",n,m);
}


//test

int main()
{
    /* Hint: if you have implemented only part of the functions,
       add comments around those that you didn't yet implement.
       Feel free to modify this function as you wish. It is not checked
       by the tester.*/
    
    /* The below code uses function printFraction. Implementing it will not
     * gain you points, but will be useful for testing */
    
    Fraction *a = setFraction(2,3);
    Fraction *b = setFraction(3,4);
    
    Fraction *sum = addFraction(a, b);
    printFraction(sum);
    printf("\n");
    
    printf("Result of comparison: %d\n", compFraction(a,b));
    
    Fraction *mul = setFraction(6,12);    
    reduceFraction(mul);
    printFraction(mul);
    
    freeFraction(a);
    freeFraction(b);
    freeFraction(sum);
    freeFraction(mul);

    return 0;
}
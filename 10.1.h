#ifndef TESTI_MAKROT
#define TESTI_MAKROT
#define EQ3(a,b,c) ((a==b)&&(b==c)) ? 1 : 0
#define MIN3(a,b,c) ((a<b)&&(a<c)) ? a : ((b<c)&&(b<a)) ? b : c
#endif
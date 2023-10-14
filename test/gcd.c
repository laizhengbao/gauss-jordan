#include "../include/group.h"

#include <stdio.h>

int main( void ){
	long a;
	unsigned long b;
	register unsigned long c;
	while( scanf( "%ld %lu", &a, &b ) == 2 ){
		c = gcd( a, b );
		printf( "%lu\n", c );
	}
}

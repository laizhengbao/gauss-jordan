#include "../include/group.h"

#include <stdio.h>

int main( void ){
	long a;
	unsigned long b;
	long c;
	unsigned long d;
	register Q qa, qb, qc;

	while( scanf( "%ld/%lu %ld/%lu", &a, &b, &c, &d ) == 4 ){
		qa.n = a;
		qa.d = b;
		qb.n = c;
		qb.d = d;
		qc = Q_div( qa, qb );
		printf( "%4ld/%4lu\n", qc.n, qc.d );
	}
}

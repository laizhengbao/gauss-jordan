#include "../include/group.h"

#include <stdio.h>

int main( void ){
	long a;
	unsigned long b;
	register Q qa, qc;

	while( scanf( "%ld/%lu", &a, &b ) == 2 ){
		qa.n = a;
		qa.d = b;
		qc = Q_inv( qa );
		printf( "%4ld/%4lu\n", qc.n, qc.d );
	}
}


#include "../../include/group.h"

#include <stdio.h>

void print ( const M A, void *F ){
	register size_t i;
	register size_t ii;
	register size_t n;
	n = A.shape[0] * A.shape[1];
	for ( i = 0; i < n; i += A.shape[1] ){
		for ( ii = 0; ii < A.shape[1]; ii++ ){
			fprintf( F, "%Lf ", *( A.A + i + ii ) );
		}
		fputc( 10, F );
	}
}

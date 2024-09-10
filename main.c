
#include "include/gauss_jordan.h"

#include <stdio.h>
#include <stdlib.h>

signed main ( void ){
	register size_t *shape;
	register M A;
	register M ret;
	register size_t i, ii;

	shape = malloc( sizeof( *shape ) * 2 );

	while( scanf( "%ld%ld", shape + 0, shape + 1 ) == 2 ){
		if ( *( shape + 0 ) > *( shape + 1 ) ){
			fprintf( stderr, "Invalid size\n" );
		}
		A.shape[0] = *( shape + 0 );
		A.shape[1] = *( shape + 1 );
		A.A = malloc( sizeof( *A.A ) * A.shape[0] * A.shape[1] );
		for ( i = 0; i < *( shape + 0 ); i++ ){
			for ( ii = 0; ii < *( shape + 1 ); ii++ ){
				scanf( "%Lf", A.A + i * *( shape + 1 ) + ii );
			}
		}
		ret = gauss_jordan( A );
		print( ret, stdout );
		free( A.A );
		free( ret.A );
	}

	free( shape );
	return EXIT_SUCCESS;
}

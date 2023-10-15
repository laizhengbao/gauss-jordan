#include "../../include/gauss_jordan.h"

#include <string.h>

M gauss_jordan( const M a ){
	register M ret = {
		.shape = {
			*( a.shape + 0 ),
			*( a.shape + 1 )
		},
		.A = NULL
	};

	register size_t i;
	register size_t j;
	register M op = {
		.shape = {
			ret.shape[0],
			ret.shape[0]
		},
		.A = NULL
	};
	register M tmp;
	register Q t;

	ret.A = malloc( sizeof( *ret.A ) * *( a.shape + 0 ) * *( a.shape + 1 ) );
	op.A = malloc( sizeof( *op.A ) * op.shape[0] * op.shape[1] );
	memcpy( ret.A, a.A, sizeof( *ret.A ) * *( a.shape + 0 ) * *( a.shape + 1 ) );

	for( i = 0; i < ret.shape[0]; i++ ){
		memset( op.A, 0, sizeof( *op.A ) * op.shape[0] * op.shape[1] );
		t = *( op.A + i * op.shape[1] + i ) = Q_inv( *( ret.A + i * ret.shape[1] + i ) );
		t.n = -t.n;
		for( j = 0; j < op.shape[0]; j++ ){
			if( i - j ){
				*( op.A + i + j * op.shape[1] ) = Q_mul( t, *( ret.A + i + j * ret.shape[1] ) );
				*( op.A + j + j * op.shape[1] ) = Q_imm( 1L, 1L );
			}
		}
#ifdef DBG
		/*
		fprintf( stderr, "Matrix OP:\n" );
		for( register size_t _ = 0; _ < op.shape[0] * op.shape[1]; _++ ){
			( _ && !( _%op.shape[1] ) ) && fputc( 10, stderr );
			Q_print( *( op.A + _ ) );
		}
		fputc( 10, stderr );
		Q_print( *ret );
		*/
#endif
		tmp = M_mul( op, ret );
		free( ret.A );
		ret = tmp;
		tmp.A = NULL;
	}

	free( op.A );

	return ret;
}

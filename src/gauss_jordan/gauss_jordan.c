#include "../../include/gauss_jordan.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int cmp( const void *, const void * );
size_t __N__;

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
	register size_t k;
	register M op = {
		.shape = {
			ret.shape[0],
			ret.shape[0]
		},
		.A = NULL
	};
	register M tmp;

	tmp = a;

	tmp.A = malloc( sizeof( *tmp.A ) * tmp.shape[0] * tmp.shape[1] );
	memcpy( tmp.A, a.A, sizeof( *tmp.A ) * tmp.shape[0] * tmp.shape[1] );
	__N__ = tmp.shape[1];
	qsort( tmp.A, tmp.shape[0], sizeof( *tmp.A ) * tmp.shape[1], cmp );
	ret = tmp;

	op.A = malloc( sizeof( *op.A ) * op.shape[0] * op.shape[1] );
	for ( i = 0; i < a.shape[0]; i++ ){
		memset( op.A, 0, sizeof( *op.A ) * op.shape[0] * op.shape[1] );
		for ( j = 0; j < a.shape[0]; j++ ){
			*( op.A + j * op.shape[1] + j ) = 1;
		}
		for ( j = 0; j < a.shape[1] && !*( ret.A + i * a.shape[1] + j ); j++ ){}
		if ( j >= a.shape[1] ){ continue; }
		*( op.A + i * op.shape[1] + i ) = 1.0L / *( ret.A + i * ret.shape[1] + j );
		for ( k = 0; k < a.shape[0]; k++ ){
			if ( !( i - k ) ){ continue; }
			*( op.A + k * op.shape[1] + i ) = - *( ret.A + k * ret.shape[1] + j ) / *( ret.A + i * ret.shape[1] + j );
#ifdef DBG
			fprintf( stderr, "%Lf %Lf %Lf\n", *( op.A + k * op.shape[1] + i ), *( ret.A + k * ret.shape[1] + j ), *( ret.A + i * ret.shape[1] + j ) );
#endif
		}
#ifdef DBG
		fprintf( stderr, "Row: %ld\n", i );
#endif
		tmp = M_mul( op, ret );
		free( ret.A );
		ret = tmp;
	}

	free( op.A );

	return ret;
}

int cmp( const void *_a, const void *_b ){
	const R* __a = _a;
	const R* __b = _b;
	register R a;
	register R b;

	for ( register size_t i = 0; i < __N__; i++ ){
		a = fabsl( *( __a + i ) );
		b = fabsl( *( __b + i ) );
		if ( a == b ){
			continue;
		}
		if ( a == 0.0L ){
			return 1;
		}
		if ( b == 0.0L ){
			return -1;
		}
		return ( a > b ) - ( a < b );
	}
	return 0;
}

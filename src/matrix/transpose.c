#include "../../include/group.h"

#include <omp.h>

M M_T( const M a ){
	register M b = {
		.shape = {
			*( a.shape + 1 ),
			*( a.shape + 0 )
		},
		NULL
	};

	register size_t i, j;

	b.A = malloc( sizeof( *b.A ) * *( a.shape + 0 ) * *( a.shape + 1 ) );

#pragma omp parallel for
	for( i = 0; i < *( a.shape + 0 ); i++ ){
#pragma omp parallel for
		for( j = 0; j < *( a.shape + 1 ); j++ ){
			*( b.A + j * b.shape[ 1 ] + i ) = *( a.A + i * *( a.shape + 1 ) + j );
		}
	}

	return b;
}

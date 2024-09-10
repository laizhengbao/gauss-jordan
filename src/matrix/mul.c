#include "../../include/group.h"

#include <pthread.h>
#include <omp.h>
#include <string.h>
#include <stdio.h>

struct P{
	size_t x;
	size_t y;
};

void* mul( void* );

M A;
M B;
M C;

M M_mul( const M a, const M b ){
	register M ret = {};

	register size_t thread;
	register pthread_t *threads = NULL;
	register struct P *data = NULL;

	if ( a.shape[1] != b.shape[0] || a.shape[0] * b.shape[1] == 0.0L ){
		goto EXIT;
	}

	thread = a.shape[0] * b.shape[1];
	threads = malloc( sizeof( *threads ) * thread );
	data = malloc( sizeof( *data ) * thread );

	ret.shape[0] = a.shape[0];
	ret.shape[1] = b.shape[1];
	ret.A = malloc( sizeof( *ret.A ) * thread );

	A = a;
	B = b;
	C = ret;

#ifdef DBG
	fprintf( stderr, "OP: \n" );
	print( a, stderr );
	fprintf( stderr, "A: \n" );
	print( b, stderr );
#endif
	for ( register size_t i = 0; i < ret.shape[0]; i++ ){
		for ( register size_t j = 0; j < ret.shape[1]; j++ ){
			( *( data + i * ret.shape[1] + j ) ).x = i;
			( *( data + i * ret.shape[1] + j ) ).y = j;
			pthread_create( threads + i * ret.shape[1] + j, NULL, mul, data + i * ret.shape[1] + j );
		}
	}

	for ( register size_t i = 0; i < thread; i++ ){
		pthread_join( *( threads + i ), NULL );
	}
EXIT:
	free( threads );
	free( data );
	return ret;
}

void *mul ( void *_ ){
	register size_t x = ( *( struct P * )_ ).x;
	register size_t y = ( *( struct P * )_ ).y;
	register R* r = C.A + x *C.shape[1] + y;

	*r = 0.0L;
	for ( register size_t i = 0; i < A.shape[1]; i++ ){
		*r += *( A.A + x * A.shape[1] + i ) * *( B.A + i * B.shape[1] + y );
	}
	return NULL;
}

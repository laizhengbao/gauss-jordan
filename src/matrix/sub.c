#include "../../include/group.h"

#include <pthread.h>
#include <immintrin.h>

struct P{
	R a;
	R b;
};

void* sub( void* );

M M_sub( const M a, const M b ){
	register M ret = {
		.shape = { 0, 0 },
		NULL
	};
	register size_t thread;
	register pthread_t* threads;
	register struct P* data;

	R* res;


	if( *( a.shape + 0) - *( b.shape + 0 ) || *( a.shape + 0 ) - *( b.shape + 1 ) ){
		goto RET;
	}

	thread = *( a.shape + 0 ) * *( a.shape + 1 );
	threads = malloc( sizeof( *threads ) * thread );
	data = malloc( sizeof( *data ) * thread );
	ret = a;
	ret.A = malloc( sizeof( *ret.A ) * thread );

	for( register size_t i = 0; i < thread; i++ ){
		( *( data + i ) ).a = *( a.A + i );
		( *( data + i ) ).b = *( b.A + i );

		pthread_create( threads + i, NULL, sub, data + i );
	}

	for( register size_t i = 0; i < thread; i++ ){
		pthread_join( *( threads + i ), ( void* )&res );
		*( ret.A + i ) = *res;
		free( res );
	}

	free( threads );
	free( data );

RET:
	return ret;
}

void* sub( void* a ){
	register R* ret = malloc( sizeof( *ret ) );
	*ret = ( ( *( struct P* )a ).a - ( *( struct P* )a ).b );
	return ret;
}

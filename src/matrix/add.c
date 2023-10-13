#include "../../include/group.h"

#include <pthread.h>
#include <immintrin.h>

struct P{
	Q a;
	Q b;
};

void* add( void* );

M M_add( const M a, const M b ){
	register M ret = {
		.shape = { 0, 0 },
		NULL
	};
	register size_t thread;
	register pthread_t* threads;
	register struct P* data;

	Q* res;


	if( *( a.shape + 0) - *( b.shape + 0 ) || *( a.shape + 0 ) - *( b.shape + 1 ) ){
		goto RET;
	}

	thread = *( a.shape + 0 ) * *( a.shape + 1 );
	threads = malloc( sizeof( *threads ) * thread );
	data = malloc( sizeof( *data ) * thread );

	for( register size_t i = 0; i < thread; i++ ){
		( *( data + i ) ).a = *( a.A + i );
		( *( data + i ) ).b = *( b.A + i );

		pthread_create( threads + i, NULL, add, data + i );
	}

	for( register size_t i = 0; i < thread; i++ ){
		pthread_join( *( threads + i ), ( void* )&res );
		*( a.A + i ) = *res;
		free( res );
	}

	free( threads );
	free( data );

RET:
	return ret;
}

void* add( void* a ){
	register Q* ret = malloc( sizeof( *ret ) );
	*ret = Q_add( ( *( struct P* )a ).a, ( *( struct P* )a ).b );
	return ret;
}

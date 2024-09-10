#include "../../include/group.h"

#include <pthread.h>

struct P{
	R a;
	R b;
};

void* dot( void* );

M M_dot( const R a, const M b ){
	register M ret = {
		.shape = {
			*( b.shape + 0 ),
			*( b.shape + 1 )
		},
		.A = NULL
	};

	register size_t thread;
	register pthread_t* threads;

	register struct P* data;

	register size_t i;

	R* res;

	thread = *( b.shape + 0 ) * *( b.shape + 1 );

	ret.A = malloc( sizeof( *( ret.A ) ) * thread );
	data = malloc( sizeof( *data ) * thread );
	threads = malloc( sizeof( *threads ) * thread );

	for( i = 0; i < thread; i++ ){
		( *( data + i ) ).a = a;
		( *( data + i ) ).b = *( b.A + i );
		pthread_create( threads + i, NULL, dot, data + i );
	}

	for( i = 0; i < thread; i++ ){
		pthread_join( *( threads + i ), ( void* )&res );
		*( ret.A + i ) = *res;
		free( res );
	}

	free( threads );
	free( data );

	return ret;
}

void* dot( void* _ ){
	register R a = ( *( struct P* )_ ).a;
	register R b = ( *( struct P* )_ ).b;

	register R* ret = malloc( sizeof( *ret ) );

	*ret = a * b;

	return ret;
}

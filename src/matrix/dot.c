#include "../../include/group.h"

#include <pthread.h>

struct P{
	Q a;
	Q b;
};

void* dot( void* );

M M_dot( const Q a, const M b ){
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

	Q* res;

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
	register Q a = ( *( struct P* )_ ).a;
	register Q b = ( *( struct P* )_ ).b;

	register Q* ret = malloc( sizeof( *ret ) );

	*ret = Q_mul( a, b );

	return ret;
}

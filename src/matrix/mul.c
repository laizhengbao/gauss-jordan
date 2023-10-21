#include "../../include/group.h"

#include <pthread.h>
#include <omp.h>
#include <string.h>

struct P{
	size_t n;
	Q* a;
	Q* b;
};

void* mul( void* );

M M_mul( const M a, const M b ){
	register M ret = {
		.shape = { 0, 0 },
		.A = NULL
	};
	
	register size_t thread;
#ifndef DBG
	register pthread_t* threads;
#endif
	register struct P* data;

	Q* res;

	if( *( a.shape + 1 ) != *( b.shape + 0 ) ){
		return ret;
	}

	thread = *( a.shape + 0 ) * *( b.shape + 1 );

#ifndef DBG
	threads = malloc( sizeof( *threads ) * thread );
#endif

	data = malloc( sizeof( *data ) * thread );

	ret.shape[0] = *( a.shape + 0 );
	ret.shape[1] = *( b.shape + 1 );
	ret.A = malloc( sizeof( *ret.A ) * thread );

#ifdef DBG
	fprintf( stderr, "M_mul\n" );

	fprintf( stderr, "a:\n" );
	for( register size_t i = 0; i < a.shape[0] * a.shape[1]; i++ ){
		( i && !( i % a.shape[1] ) ) && fputc( 10, stderr );
		Q_print( *( a.A + i ) );
	}
	fputc( 10, stderr );

	fprintf( stderr, "b:\n" );
	for( register size_t i = 0; i < b.shape[0] * b.shape[1]; i++ ){
		( i && !( i % b.shape[1] ) ) && fputc( 10, stderr );
		Q_print( *( b.A + i ) );
	}
	fputc( 10, stderr );
#endif

	for( register size_t i = 0; i < thread; i++ ){
		( *( data + i ) ).a = malloc( sizeof( *( *( data + i ) ).a ) * *( a.shape + 1 ) );
		( *( data + i ) ).b = malloc( sizeof( *( *( data + i ) ).b ) * *( a.shape + 1 ) );
		( *( data + i ) ).n = *( a.shape + 1 );
		memcpy( ( *( data + i ) ).a, a.A + ( i / *( a.shape + 1 ) ), ( *( data + i ) ).n );
		for( register size_t j = i % ret.shape[1], k = 0; k < b.shape[0]; j += *( b.shape + 1 ), k++ ){
			*( ( *( data + i ) ).b + k ) = *( b.A + j );
		}
#ifdef DBG
		/*
		fprintf( stderr, "data a:\n" );
		for( register size_t j = 0; j < ( *( data +i ) ).n; j++ ){
			Q_print( *( ( *( data + i ) ).a + j ) );
		}
		fputc( 10, stderr );
		fprintf( stderr, "data b:\n" );
		pthread_create( threads + i, NULL, mul, data + i );
		for( register size_t j = 0; j < ( *( data +i ) ).n; j++ ){
			Q_print( *( ( *( data + i ) ).b + j ) );
		}
		fputc( 10, stderr );
		*/
		fprintf( stderr, "#%lx\n", i );
		res = mul( data + i );
		*( ret.A + i ) = *res;
		free( res );
		free( ( *( data + i ) ).a );
		free( ( *( data + i ) ).b );
#else
		pthread_create( threads + i, NULL, mul, data + i );
#endif
	}

#ifndef DBG
	for( register size_t i = 0; i < thread; i++ ){
		pthread_join( *( threads + i ), ( void* )&res );
		*( ret.A + i ) = *res;
		free( res );
		free( ( *( data + i ) ).a );
		free( ( *( data + i ) ).b );
	}
#endif

#ifdef DBG
	fprintf( stderr, "ret:\n" );
	for( register size_t i = 0; i < ret.shape[0] * ret.shape[1]; i++ ){
		( i && !( i % ret.shape[1] ) ) && fputc( 10, stderr );
		Q_print( *( ret.A + i ) );
	}
	fputc( 10, stderr );
#else
	free( threads );
#endif
	free( data );

	return ret;
}

void* mul( void* _ ){
	register Q* a = ( *( struct P* )_ ).a;
	register Q* b = ( *( struct P* )_ ).b;
	register size_t n = ( *( struct P* )_ ).n;
	register Q* ret = malloc( sizeof( *ret ) );

#ifdef DBG
	register Q tmp;
#endif
	
	*ret = Q_imm( 0L, 1L );

	for( register size_t i = 0; i < n; i++ ){
#ifdef DBG
		/*
		fprintf( stderr, "matrix mul " );
		Q_print( *( a + i ) );
		Q_print( *( b + i ) );
		Q_print( Q_mul( *( a + i ), *( b + i ) ) );
		fputc( 10, stderr );
		*/
#endif
#ifndef DBG
		*ret = Q_add( *ret, Q_mul( *( a + i ), *( b + i ) ) );
#else
		tmp = Q_mul( *( a + i ), *( b + i ) );
		fprintf( stderr, "ret, a, b, c: " );
		Q_print( *ret );
		Q_print( *( a + i ) );
		Q_print( *( b + i ) );
		Q_print( tmp );
		fputc( 10, stderr );

		*ret = Q_add( *ret, tmp );
#endif
	}

	return ret;
}

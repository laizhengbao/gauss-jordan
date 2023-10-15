#ifndef __GROUP_H__

#include <stdlib.h>

typedef struct _Q_{
	long n;
	unsigned long d;
} Q;

typedef struct _M_{
	size_t shape[2];
	Q* A;
} M;

Q Q_imm( const long, const unsigned long );
Q Q_add( const Q, const Q );
Q Q_sub( const Q, const Q );
Q Q_mul( const Q, const Q );
Q Q_div( const Q, const Q );
Q Q_inv( const Q );

int Q_eq( const Q, const Q );
int Q_gt( const Q, const Q );
int Q_lt( const Q, const Q );

unsigned long gcd( long, unsigned long );
unsigned long lcm( long, unsigned long );

unsigned long N_gcd( unsigned long, unsigned long );
unsigned long N_lcm( unsigned long, unsigned long );

M M_add( const M, const M );
M M_sub( const M, const M );
M M_mul( const M, const M );
M M_dot( const Q, const M );
M M_T( const M );
/* Q M_det( const M ); */

#ifdef DBG
#include <stdio.h>

#define Q_print( a ) fprintf( stderr, "%ld/%lu ", (a).n, (a).d )

#endif

#endif

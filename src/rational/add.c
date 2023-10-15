#include "../../include/group.h"

#define nonzero( a ) ( (a)?a:1L )

Q Q_add( const Q a, const Q b ){
	register Q c = {
		.n = 0,
		.d = 1L
	};

	register unsigned long tmp = N_lcm( a.d, b.d );

	c.d = tmp;
#ifdef DBG
	/*
	fprintf( stderr, "Q_add " );
	Q_print( a );
	Q_print( b );
	Q_print( c );
	fprintf( stderr, "%lu ", tmp );
	*/
#endif
	c.n = ( c.d / nonzero( a.d ) * a.n ) +
		( c.d / nonzero( b.d ) * b.n );
#ifdef DBG
	/*
	Q_print( c );
	fputc( 10, stderr );
	*/
#endif
	tmp = gcd( c.n, c.d );
	c.d /= tmp;
	c.n /= tmp;

	return c;
}

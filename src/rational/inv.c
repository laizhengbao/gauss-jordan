#include "../../include/group.h"

#include <limits.h>

#define abs( a ) ( ( a & ( 1L << ( sizeof( a ) * CHAR_BIT -1 ) ) ) ?  ~a + 1 : a )
Q Q_inv( const Q a ){
	register Q b;
	if( !a.n ) return a;

	( ( a.n & ( 1L << ( ~1L + 1L + sizeof( a.n ) * CHAR_BIT ) ) ) && ( b.d = ~a.n + 1, b.n = ~a.d + 1 ) ) || ( b.d = a.n, b.n = abs( a.d ) );
	return b;
}

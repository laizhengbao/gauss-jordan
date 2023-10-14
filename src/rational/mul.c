#include "../../include/group.h"

Q Q_mul( const Q a, const Q b ){
	register Q c = {
		.n = 0,
		.d = 1
	};

	register unsigned long gcda, gcdb;
	register unsigned long gcdc, gcdd;

	register unsigned long na, nb;
	register long sgn;

	gcda = gcd( a.n, a.d );
	gcdb = gcd( b.n, b.d );
	gcdc = gcd( a.n, b.d );
	gcdd = gcd( b.n, a.d );

	na = ( a.n < 0 )?-a.n:a.n;
	nb = ( b.n < 0 )?-b.n:b.n;
	sgn = ( ( a.n < 0 ) ^ ( b.n < 0 ) )?-1L:1L;

	c.n = ( na / gcda / gcdc ) * ( nb / gcdb / gcdd ) * sgn;
	c.d = ( a.d / gcda / gcdd ) * ( b.d / gcdb / gcdc );

	return c;
}

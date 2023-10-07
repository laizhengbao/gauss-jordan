#include "../../include/group.h"

#include <limits.h>

Q Q_div( const Q a, const Q b ){
	register Q c = {
		.n = 0,
		.d = 1
	};

	register Q t = Q_inv( b );
	register unsigned long tmp;

	c.n = a.n * t.n;
	c.d = a.d * b.d;

	tmp = gcd( c.n, c.d );

	c.d /= tmp;
	c.n /= tmp;

	return c;
}

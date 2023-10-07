#include "../../include/group.h"

Q Q_mul( const Q a, const Q b ){
	register Q c = {
		.n = 0,
		.d = 1
	};

	register unsigned long tmp;

	c.n = a.n * b.n;
	c.d = a.d * b.d;
	tmp = gcd( c.n, c.d );
	c.d /= tmp;
	c.n /= tmp;

	return c;
}

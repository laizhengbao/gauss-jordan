#include "../../include/group.h"

Q Q_sub( const Q a, const Q b ){
	register Q c = {
		.n = 0,
		.d = 1L
	};

	register unsigned long tmp = N_lcm( a.d, b.d );

	c.d = tmp;
	c.n = ( tmp / a.d * a.n ) - ( tmp / b.d * b.n );
	tmp = gcd( c.n, c.d );
	c.d /= tmp;
	c.n /= tmp;

	return c;
}

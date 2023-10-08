#include "../../include/group.h"

int Q_lt( const Q a, const Q b ){
	register unsigned long t = N_lcm( a.d, b.d );

	return ( t / a.d * a.n ) < ( t / b.d * b.n );
}

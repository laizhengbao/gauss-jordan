#include "../include/group.h"

unsigned long lcm( long a, unsigned long b ){
#ifdef DBG
	/*
	fprintf( stderr, "lcm %ld %lu\n", a, b );
	*/
#endif
	return a * b / gcd( a, b );
}

unsigned long N_lcm( unsigned long a, unsigned long b ){
#ifdef DBG
	/*
	fprintf( stderr, "lcm %lu %lu\n", a, b );
	*/
#endif
	return a * b / N_gcd( a, b );
}

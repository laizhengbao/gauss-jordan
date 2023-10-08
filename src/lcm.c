#include "../include/group.h"

unsigned long lcm( long a, unsigned long b ){
	return a / gcd( a, b ) * b;
}

unsigned long N_lcm( unsigned long a, unsigned long b ){
	return a / N_gcd( a, b ) * b;
}

#include "../include/group.h"

#define swap( a, b ) {\
	a ^= b;\
	b ^= a;\
	a ^= b;\
}
#define nonzero( a ) ( ( a )?a:1L )

unsigned long gcd( long _, unsigned long __ ){

	register unsigned long a, b;

	a = ( _ < 0 ) ? ~_ + 1 : _;
	a = nonzero( a );
	b = nonzero( __ );

	while( a && b ){
		if( a < b ){
			swap( a, b );
		}

		a %= b;
	}
	
	return b;
}

unsigned long N_gcd( unsigned long _, unsigned long __ ){
	register unsigned long a = nonzero( _ ), b = nonzero( __ );

	while( a && b ){
		if( a < b ){
			swap( a, b );
		}

		a %= b;
	}
	
	return b;
}

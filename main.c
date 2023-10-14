#include "include/gauss_jordan.h"

#include <stdio.h>

int main( void ){
	size_t m, n;
	register M A;
	register M R;
	register Q tmp;
	long a;
	unsigned long b;

	while( scanf( "%lu%lu", &m, &n ) == 2 ){
		A.shape[0] = m;
		A.shape[1] = n;
		A.A = malloc( sizeof( *A.A ) * m * n );
		for( register size_t i = 0; i < m; i++ ){
			for( register size_t j = 0; j < n; j++ ){
				scanf( "%ld/%lu", &a, &b );
				tmp.n = a;
				tmp.d = b;
				*( A.A + i * n + j ) = tmp;
			}
		}
		R = gauss_jordan( A );
		for( register size_t i = 0; i < m * n; i++ ){
			( i && ! i % n ) && putchar_unlocked( 10 );
			printf( "%4ld/%4lu ", ( *( R.A + i ) ).n, ( *( R.A + i ) ).d );
		}
		free( A.A );
		free( R.A );
	}
}

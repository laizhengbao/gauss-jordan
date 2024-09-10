#ifndef __GROUP_H__

#include <stdlib.h>
#include <math.h>

typedef long double R;
typedef struct _M_{
	size_t shape[2];
	R* A;
} M;

M M_add( const M, const M );
M M_sub( const M, const M );
M M_mul( const M, const M );
M M_dot( const R, const M );
M M_T( const M );

void print( const M, void * );

#endif

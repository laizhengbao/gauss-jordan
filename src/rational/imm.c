#include "../../include/group.h"

#define max( a, b ) __extension__({\
		__typeof__( a ) _a = a;\
		__typeof__( b ) _b = b;\
		( _a > _b ) ? _a : _b;\
		})

Q Q_imm( const long n, const unsigned long d ){
	register Q ret = {
		.n = n,
		.d = max( 1L, d )
	};
	return ret;
}

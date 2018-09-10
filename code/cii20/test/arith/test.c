#include "tool.h"
#include <stdio.h>

int main( void )
{
    printf("arith_max( 5, 2 ) = %d\n", arith_max( 5, 2 ) );
    printf("arith_min( 5, 2 ) = %d\n", arith_min( 5, 2 ) );
    printf("arith_div( 5, 2 ) = %d\n", arith_div( 5, 2 ) );
    printf("arith_mod( 5, 2 ) = %d\n", arith_mod( 5, 2 ) );
    printf("arith_ceiling( 5, 2 ) = %d\n", arith_ceiling( 5, 2 ) );
    printf("arith_floor( 5, 2 ) = %d\n", arith_floor( 5, 2 ) );

    return 0;
}

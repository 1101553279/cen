#include "arith.h"
#include <stdio.h>
#include <stdlib.h>


/* start entry */
int main( void )
{
    div_t iv;
    printf( "Arith_min( %d, %d ) = %d\n", 30, 20, Arith_min(30,20) );
    printf( "Arith_max( %d, %d ) = %d\n", 30, 20, Arith_max(30,20) );
    printf( "Arith_div( %d, %d ) = %d\n", 30, 20, Arith_div(30,20) );
    printf( "Arith_mod( %d, %d ) = %d\n", 30, 20, Arith_mod(30,20) );

    printf( "-13/5 = %d\n", -13/5 );
    printf( "Arith_div(-13, 5) = %d\n", Arith_div(-13,5) );
    printf( "Arith_mod(-13, 5) = %d\n", Arith_mod(-13,5) );
//    printf( "13/0 = %d\n", 13/0 );    //error
    printf( "0 %% 13 = %d\n", 0%13 );
//    printf( "13 %% 0 = %d\n", 13%0 ); //error

    iv = div(-13, 5);
    printf( "div(13, 5): iv.quot = %d, iv.rem = %d\n", iv.quot, iv.rem );


    return 0;
}



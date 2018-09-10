#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "assert.h"
#include "except.h"
#include "atom.h"

int main( void )
{
    int i = 0;
    char *strings[ 5 ] = { "first", 
                           "second",
                           "third", 
                           "fourth",
                           "fifth",
    };

    const char *anew[ 5 ] = { 0 };
    const char *astr[5] = { 0 };
    const char *aint[6] = { 0 };

    for(i = 0; i < 5; i++ )
        anew[ i ] = Atom_new( strings[i], strlen(strings[i]) );
    
    for(i = 0; i < 5; i++ )
        astr[ i ] = Atom_string( strings[i] );
    
    for(i = 0; i < 5; i++ )
        aint[ i ] = Atom_int( i+10 );

    aint[i] = Atom_int( LONG_MIN );

    printf( ">>. anew dump!\n" );
    for(i = 0; i < 5; i++ )
        printf( "anew[%d] = %s, len = %d,  addr: %#x\n",
                i, anew[i], Atom_length(anew[i]), anew[i] );

    printf( "\n" );
    printf( ">>. astr dump!\n" );
    for(i = 0; i < 5; i++ )
        printf( "astr[%d] = %s, len = %d,  addr: %#x\n",
                i, astr[i], Atom_length(astr[i]), astr[i] );
    
    printf( "\n" );
    printf( ">>. aint dump!\n" );
    for(i = 0; i < 6; i++ )
        printf( "aint[%d] = %s, len = %d,  addr: %#x\n",
                i, aint[i], Atom_length(aint[i]), aint[i] );
#if 1    
    unsigned long lg;
    printf( "LONG_MAX = %u\n", LONG_MAX );
    printf( "LONG_MAX+1= %u\n", LONG_MAX+1 );
    printf( "LONG_MAX+2= %u\n", LONG_MAX+2 );
    lg = LONG_MAX + 1 ;
    printf( "lg = %u\n", lg );
    printf( "lg - 1 = %u\n", lg-1 );
    printf( "lg %% 10 = %u\n", lg%10 );
    lg = LONG_MIN;
    printf( "lg = %u\n", lg );
#endif

    return 0;
}

#include "mm.h"
#include "pool.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_NUM   10
#define BLOCK_SIZE  100
unsigned char blocks[ BLOCK_NUM ][ BLOCK_SIZE ];

int main( int argc, char *argv[] )
{
    int i = 0; 
    struct mm *mm_gets[ MM_TABLE_SIZE ];
    struct mm *mm_bl;

    mm_table_init( );
    

    for( i = 0; i < 3; i++ )
    {
        mm_gets[i] = mm_table_get( );
        if( 0 == mm_gets[i] )
            printf( "## mm get fail!\r\n" );
    }

    mm_table_put( mm_gets[0] );

    mm_bl = pool_init( blocks, BLOCK_NUM, BLOCK_SIZE );
    
    pool_debug( mm_bl );

    mm_table_debug( );

    return 0;
}

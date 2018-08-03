#include <stdio.h>
#include "memp.h"


/* notic num, comma */
int memp_num[ MAX_POOL ] = {
#define LWIP_MEMPOOL( name, num, size, desc )   num,
#include "std.h"
};

int memp_size[ MAX_POOL ] = {
#define LWIP_MEMPOOL( name, num, size, desc )   size,
#include "std.h"
};

char *memp_desc[ MAX_POOL ] = {
#define LWIP_MEMPOOL( name, num, size, desc )   desc"_pool",
#include "std.h"
};

void memp_print( void )
{
    int i = 0;

    printf( "MAX_POOL = %d, MALLOC_FIRST = %d, MALLOC_LAST = %d\r\n", MAX_POOL, MALLOC_FIRST, MALLOC_LAST ); 
   
    printf( "%-10s %-10s %-10s %-10s\r\n", "no", "num", "size", "desc" ); 
    for( i = 0; i < MAX_POOL; i++ )
    {
        printf( "%-10d %-10d %-10d %-10s\r\n", i, memp_num[ i ], memp_size[ i ], memp_desc[ i ] );
    }

    return;
}

/* start entry */
int main( void )
{
    memp_print( );

    return 0;
}

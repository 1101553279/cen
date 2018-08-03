#include <stdio.h>

#define BLOCK_NUM   10
#define BLOCK_SIZE  8

typedef unsigned char u8_t;
typedef unsigned short u16_t;
typedef unsigned int u32_t;

struct memp{
    struct memp *next;
};

u8_t mem_base[ BLOCK_NUM ][ BLOCK_SIZE ];
struct memp *link;

void memp_init( )
{
    u8_t i = 0;
    block_t bb;

    link = 0;
    bb = mem_base;
    for( i = 0; i < BLOCK_NUM; i++ )
    {
       (( struct memp *)bb)->next = link;
       link = (struct memp *)bb;
       bb++;
    }
    
    return;
}

void memp_print( )
{
    int i = 0;
    struct memp *pp;

    pp = link;
    while( 0 != pp )
    {
        i++;
        printf( "%-02d: %#x\r\n", i, pp );
        pp = pp->next;
    }

    return;
}

int main( void )
{
    memp_init( );
    memp_print( );

    return 0;
}

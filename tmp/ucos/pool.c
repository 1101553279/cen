#include "pool.h"
#include <stdio.h>



mm_t *pool_init( u8_t *base, u16_t num, u16_t size )
{
    mm_t *mm = 0;
    void *head;
    void **link;
    u8_t i = 0;

    if( 0 == base || 0 == num || 0 == size )
        return 0;
    
    mm = mm_table_get( );
    if( 0 == mm )
        return 0;

    head = 0;
    link = (void **)base;
    for( i = 0; i < num; i++ )
    {
        *link = head;
        head = ( void *)link;
        link = ( void **)( (u8_t*)link + size );
    }

    mm->free = head; 
    mm->num = num;
    mm->size = size;
    mm->base = base;
    mm->name = "N";

    return mm;
}

void pool_debug( mm_t *mm )
{
    if( 0 == mm )
        return;
   
    printf( "## pool ## base = %#x, num = %u, size = %u, free = %#x, name = %s\r\n",
                        mm->base,       mm->num,  mm->size,  mm->free,   mm->name ); 


    return;
}

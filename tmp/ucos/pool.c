#include "pool.h"
#include <stdio.h>

/*  two level pointer understand
 *  graphic:             __
 *      char ch;        |__|   1 byte
 *                       _______________
 *      void *pch;      |_______________|   4 bytes
 *                       _______________
 *      void **ppch;    |______________ |   4 bytes
 *                      
 *  operator:
 *      bch = ch,   ch = bch;     
 *          &ch
 *      bpch = pch, pch = bpch;
 *          &pch
 *      bppch = ppch, ppch = bppch;
 *          &ppch
 *
 *  complex:
 *      pch = (void *)&ch;
 *          *(char *)pch = 'c';
 *          invalid: *pch   -> type == void 
 *      ppch = &pch;
 *          *ppch = &ch;
 *          valid: *ppch   -> type = void *
 *  anthor:
 *  struct list {
 *      struct list *next;
 *      struct list *prev;
 *      int data[ 12 ];
 *  };
 *
 *  struct list head;       |                               |   18 bytes
 *  struct list *phead;     |               |   4bytes
 *  struct list **pphed;    |               |   4bytes
 *  
 *  phead = &head;
 *      phead->next =  write space where address in phead;    for write
 *      (*phead).next = 
 *
 *      = phead->next  read space where address in phead;
 *      = (*phead).next
 *
 *  pphead = &phead;
 *
 *  1. how operation
 *     pointer self or pointer space
 *     pointer self 
 *                  = ...
 *                  ... = 
 *     pointer space
 *                  *
 *                  ->
 *  2. operation rules
 *     data types & structure   according to (pointer types or structure)
 *
 * */

#if 0
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
#endif

mm_t *pool_init( u8_t *base, u16_t num, u16_t size )
{
    mm_t *mm = 0;
    void *head;
    void *link;
    u8_t i = 0;

    if( 0 == base || 0 == num || 0 == size )
        return 0;
    
    mm = mm_table_get( );
    if( 0 == mm )
        return 0;

    head = 0;
    link = (void *)base;
    for( i = 0; i < num; i++ )
    {
        *( void **)link = head;
        head = link;
        link = (void *)( (u8_t*)link + size );
    }
/* set mm entry information */
    mm->free = head; 
    mm->num = num;
    mm->size = size;
    mm->base = base;
    mm->name = "N";

    return mm;
}


void *pool_alloc( mm_t *mm )
{
    void *ret;

    if( 0 == mm || 0 == mm->free )
        return 0;
    
    ret = mm->free;
    mm->free = *( (void **)ret );

    return ret;
}

void pool_free( mm_t *mm, void *put )
{
    if( 0 == mm || 0 == put )
        return;
    
    *( (void **)put ) = mm->free;
    mm->free = put;

    return;
}

void pool_uninit( mm_t *mm )
{
    if( 0 == mm )
        return ;
    /*
     *  free pool in mm
     * */ 
    mm_table_put( mm );

    return ;
}

void pool_debug( mm_t *mm )
{
    int i = 0;
    void *link = 0;

    if( 0 == mm )
        return;
   
    printf( "## pool ## base = %#x, num = %u, size = %u, free = %#x, name = %s\r\n",
                        mm->base,       mm->num,  mm->size,  mm->free,   mm->name ); 

    link = mm->free;
    while( 0 != link )
    {
        printf("\t## pool list ## %d: %#x\r\n", i, link );
        i++;
        link = *(void **)( link );
    }

    return;
}

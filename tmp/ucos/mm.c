#include "mm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static struct mm mm_table[ MM_TABLE_SIZE ];

/*
 *  init table 
 * */
void mm_table_init( )
{
    int i = 0;
    
    for( i = 0; i < MM_TABLE_SIZE; i++ )
    {
        mm_table[ i ].base = 0;
        mm_table[ i ].use = MM_ENTRY_NOUSE;
        mm_table[ i ].id = i;
        mm_table[ i ].rsv = 0;
        mm_table[ i ].num = 0;
        mm_table[ i ].size = 0;
        mm_table[ i ].free = 0;
        mm_table[ i ].name = 0;
    }

    return;
}

/*
 * alloc one table entry
 * */
struct mm *mm_table_get( )
{
    int i = 0;

    struct mm *get;

    for( i = 0; i < MM_TABLE_SIZE; i++)
    {
        if( MM_ENTRY_NOUSE ==  mm_table[ i ].use )
            break;
    }
    
    if( MM_TABLE_SIZE != i )
    {
        mm_table[ i ].use = MM_ENTRY_INUSE;
        get = &mm_table[ i ];
    }
    else
        get = 0;

    return get;
}

/* 
 * free one table entry
 * */
void mm_table_put( struct mm *en )
{
    if( 0 == en )
        return;

    memset( en, 0, sizeof( struct mm ) );
    en->use = MM_ENTRY_NOUSE;

    return;
}

int mm_table_name_set( struct mm *en, s8_t *name )
{
    if( 0 == en )
        return -1;

    en->name = name;

    return 0;
}

int mm_table_name_clear( struct mm *en )
{
    if( 0 == en )
        return -1;
    
    en->name = 0;

    return 0;
}

/*
 * for debug
 * */
void mm_table_debug( )
{
    int i = 0;

    for( i = 0; i< MM_TABLE_SIZE; i++ )
        printf( "## mm ## id: %d: %s\r\n", mm_table[i].id, 
                            (MM_ENTRY_INUSE == mm_table[i].use) ?"in":"no" );

    return;
}


#ifndef __MM_H__
#define __MM_H__

#include "ty.h"
#define MM_TABLE_SIZE   10
#define MM_ENTRY_INUSE   1
#define MM_ENTRY_NOUSE   0

/* memory pool description */
typedef struct mm{
    u8_t *base;     // pool base address

    u8_t use;       // in use/ not use
    u8_t id;        // pool id
    u16_t rsv;      // reserve

    u16_t num;      // pool's block
    u16_t size;     // each block size

    u8_t *free;     // free block list 

    s8_t *name;     // this pool name
}mm_t;


void mm_table_init( );
//int mm_table_base_set( struct mm*en, u8_t *base );
//int mm_table_num_set( struct mm *en, u16_t num );
//int mm_table_size_set( struct mm *en, u16_t size );
//int mm_table_free_set( struct mm *en, u8_t *free );
struct mm *mm_table_get( );
void mm_table_put( struct mm *en );
int mm_table_name_set( struct mm *en, s8_t *name );
int mm_table_name_clear( struct mm *en );
void mm_table_debug( );

#endif

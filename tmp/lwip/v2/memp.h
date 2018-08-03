#ifndef __MEMP_H__
#define __MEMP_H__

/* notice  name##_POOL, comma */
typedef enum{
#define LWIP_MEMPOOL( name, num, size, desc )   name##_POOL,
#include "std.h"
    MAX_POOL
}memp_t;

typedef enum{
   MALLOC_FIRST = (
#define LWIP_MEMPOOL( name, num, size, desc )
#define LWIP_MALLOC_MEMPOOL( num, size )    * MALLOC_##num##_##size##_POOL + 0
#define LWIP_MALLOC_START   1
#define LWIP_MALLOC_END     
#include "std.h"
        ),
    MALLOC_LAST = ( 
#define LWIP_MEMPOOL( name, num, size, desc )
#define LWIP_MALLOC_MEMPOOL( num, size )    0 + MALLOC_##num##_##size##_POOL *
#define LWIP_MALLOC_START
#define LWIP_MALLOC_END     1    
#include "std.h"
        ),    
}malloc_helper_t;



//declaration
/*
extern int memp_num[ MAX_POOL ];
extern int memp_size[ MAX_POOL ];
extern char *memp_desc[ MAX_POOL ];
*/

#endif

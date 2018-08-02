#ifndef __MEMP_H__
#define __MEMP_H__

/* notice  name##_POOL, comma */
typedef enum{
#define LWIP_MEMPOOL( name, num, size, desc )   name##_POOL,
#include "std.h"
    MAX_POOL
}memp_t;

//declaration
/*
extern int memp_num[ MAX_POOL ];
extern int memp_size[ MAX_POOL ];
extern char *memp_desc[ MAX_POOL ];
*/

#endif

#ifndef __POOL_H__
#define __POOL_H__

#include "mm.h"


mm_t *pool_init( u8_t *base, u16_t num, u16_t size );
void pool_uninit( mm_t *mm );
void *pool_alloc( mm_t *mm );
void pool_free( mm_t *mm, void *put );
void pool_debug( mm_t *mm );





#endif

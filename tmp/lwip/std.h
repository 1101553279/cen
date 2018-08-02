/* *LWIP_MEMPOOL( name, num, size, desc )
 * name: element's
 * num: number of element
 * size: each element size
 * desc: element's description
 * */


//LWIP_MEMPOOL( name, num, size, desc )
/* 
 *  ##      concatenation two token
 *  #       to string
 * */
#ifndef LWIP_MALLOC_MEMPOOL
#define LWIP_MALLOC_MEMPOOL( num, size )    LWIP_MEMPOOL( MALLOC_##num##_##size, num, size, "malloc_"#size"_desc" )
#endif


LWIP_MEMPOOL( TCP, 10, 20, "tcp desc" ) 

LWIP_MEMPOOL( UDP, 20, 20, "udp desc" ) 

LWIP_MEMPOOL( IP, 30, 20, "ip desc" ) 

LWIP_MEMPOOL( IGMP, 40, 20, "igmp desc" ) 

LWIP_MEMPOOL( ICMP, 50, 20, "icmp desc" )

/* malloc */
LWIP_MALLOC_MEMPOOL( 20, 200 )
LWIP_MALLOC_MEMPOOL( 30, 300 )
LWIP_MALLOC_MEMPOOL( 40, 400 )
LWIP_MALLOC_MEMPOOL( 50, 500 )


#undef LWIP_MEMPOOL

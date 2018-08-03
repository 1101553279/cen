#include <stdio.h>
#include "memp.h"
struct memp_link{
    struct memp_link *next;
};

struct memp_desc{
    unsigned char *base;
    int num;
    int size;
    char *desc;
    struct memp_link **tab;
};


#define MEMPOOL_DECLARE( name, num, size, desc )   \
    unsigned char name##_mempbase[ size ];       \
    

#define LWIP_MEMPOOL( name, num, size, desc) MEPOOL_DECLARE( name, num, size, desc )    
#include "std.h"

/* start entry */
int main( void )
{

    return 0;
}

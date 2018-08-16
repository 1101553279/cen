#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*  0 1 2 3 4 5    n-2..n        
 *  | | | | | |... | | | |
 *
 *
 * */
char ch_a[ 10 ];

/*  0   4   8   12  16          n-4 n
 *  |   |   |   |   |   .....   |   |   |
 *
 * */
char *pch_a[ 10 ];

/*  0   4   8   12  16          n-4 n
 *  |   |   |   |   |   .....   |   |   |
 *
 * */
/* in_a : first element address */
/* type : int       */
/* in_a + i */
int in_a[ 10 ];

/* pin_a: first element address */
/* type : int *     */
int *pin_a[ 10 ];
int **ppin_a[ 10 ];

/* vo_a: first element address */
/* type : void *     */
/* vo_a + i */
void *vo_a[ 10 ];

/* pvo_a: first element address */
/* type : void **    */
void **pvo_a[ 10 ];



int main( int argc, char *argv[ ] )
{
    int i = 0;
    
    for( i=0; i < 10; i++ )
    {
        pvo_a[ i ] = &vo_a[ i ];
    }

    printf( "vo_a address!\r\n" );
    for( i = 0; i < 10; i++ )
    {
        printf( "##&vo_a %d: %#x\r\n", i, &vo_a[i] );
        printf( " ##vo_a+i %d: %#x\r\n", i, vo_a+i );
        printf( " ##pvo_a %d: %#x\r\n", i, pvo_a[i] );
        printf( " ---------------------\r\n" );
    }


    return 0;
}

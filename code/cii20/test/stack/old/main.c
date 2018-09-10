#include "stack.h"
#include <stdio.h>

void dout( char *desc, Stack_T stk );

/* start entry */
int main( void )
{
    Stack_T st;
    char *names[ ] = { "first name",
                       "second name",
                       "third name",
                       "fourth name", 
                       "fifth name",
    };
    int i = 0;

    
    st = Stack_new();      // new a stack 
    dout( ">>. stack new", st );
    
    for(i = 0; i < 5; i++ )
        Stack_push( st, names[i] );
    dout( ">>. stack push 5 units", st );
   
    Stack_pop( st ); 
    dout( ">>. stack pop 1 unit", st );

    for( i = 0; i < 3; i++ )
        Stack_pop( st );
    dout( ">>. stack pop 3 units", st );

    Stack_pop( st );
    dout( ">>. stack pop 1 unit", st );

    Stack_free( &st );
    dout( ">>. stack free!", st );

    return 0;
}




// for test output
void dout( char *desc, Stack_T stk )
{
    printf( "\n" );
    if( 0 != desc )
        printf( "%s\n", desc );

    if( 0 != stk )
    {
        printf( "\tstack size: %d, stack empty: %s\n", 
                Stack_size(stk), Stack_empty( stk)? "yes": "no" );

        Stack_literate( stk, dump );        
    }
    else    
    {
        printf( "\tstk is null!\n" );
    }

    return;
}


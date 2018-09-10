/* $Id: stack.h 6 2007-01-22 00:45:22Z drhanson $ */
#ifndef STACK_INCLUDED
#define STACK_INCLUDED

#define T Stack_T
typedef struct T *T;

extern T     Stack_new  (void);
extern int   Stack_empty(T stk);
extern void  Stack_push (T stk, void *x);
extern void *Stack_pop  (T stk);
extern void  Stack_free (T *stk);


//add by myself 
#include <stdio.h>      //for main.c printf
typedef struct elem *elem_t;
typedef void (*call_t)( elem_t e );

extern void dump( elem_t e );

extern int Stack_size( T stk );
extern void Stack_literate( T stk, call_t call );

#undef T
#endif

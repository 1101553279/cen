#ifndef __STACK_H__
#define __STACK_H__
#include "btype.h"

typedef struct elem{        // element type
    void *c;                // element
    struct elem *next;      // for element list
}elem_t;                 

typedef struct stack{
    u32_t count;            // count element 
    struct elem *head;      // head for elements list
}stack_t, *pstack_t;

typedef void (*cb_list_t)(elem_t *e);

// new one stack
stack_t *stack_new(void);

void stack_push(stack_t *t, void *e);

void *stack_pop(stack_t *t);

u8_t stack_empty(stack_t *t);

void stack_free(pstack_t *t);


// for debug
void stack_list(stack_t *t, cb_list_t list);



//questions
/*  1>>. typedef or define T
 *  2>>. stack_new parameter
 *  3>>. push return
 *  4>>. empty return type
 * */



#endif

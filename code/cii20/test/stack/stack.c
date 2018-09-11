#include "stack.h"
#include "mem.h"

/*
typedef struct stack{
    u32_t count;
    struct elem{
        void *c;
        struct elem *next;
    }*head;
}*stack_t;

typedef void (*cb_list_t)(struct elem *e);

// new one stack
stack_t stack_new(void);

void stack_push(stack_t t, void *e);

void *stack_pop(stack_t t);

u8_t stack_empty(stack_t t);

void stack_free(stack_t *t);


// for debug
void stack_list(stack_t t, cb_list_t list);
*/

stack_t *stack_new(void)
{
    stack_t *p;
    
    NEW(p);

    p->count = 0;
    p->head = 0;
   
    return p; 
}

//questions
/*
 * 1>>. stack_new do not forget assign to newp
 *
 * */

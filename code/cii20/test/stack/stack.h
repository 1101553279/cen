#ifndef __STACK_H__
#define __STACK_H__

typedef struct stack{
    int count;
    struct elem{
        void *c;
        struct elem *next;
    }*head;
}*stack_t;


#endif

static char rcsid[] = "$Id: stack.c 6 2007-01-22 00:45:22Z drhanson $";
#include <stddef.h>
#include "assert.h"
#include "mem.h"
#include "stack.h"

#define T Stack_T
struct T {
	int count;                  // element number
	struct elem {               // element
		void *x;                // element context
		struct elem *link;      // for element link list
	} *head;                    // elemnt link list head
};

T Stack_new(void) {
	T stk;
	NEW(stk);
	stk->count = 0;
	stk->head = NULL;
	return stk;
}

int Stack_empty(T stk) {
	assert(stk);
	return stk->count == 0;
}

void Stack_push(T stk, void *x) {
	struct elem *t;
	assert(stk);
	NEW(t);
	t->x = x;
	t->link = stk->head;
	stk->head = t;
	stk->count++;
}

void *Stack_pop(T stk) {
	void *x;
	struct elem *t;
	assert(stk);
	assert(stk->count > 0);
	t = stk->head;
	stk->head = t->link;
	stk->count--;
	x = t->x;
	FREE(t);
	return x;
}

void Stack_free(T *stk) {
	struct elem *t, *u;
	assert(stk && *stk);
	for (t = (*stk)->head; t; t = u) {
		u = t->link;
		FREE(t);
	}
	FREE(*stk);
}

//add by myself 
int Stack_size( T stk )
{
    return stk->count;
}

void dump( elem_t e )
{
    assert( e ); 

    printf( "\t%s\n", (char *)e->x );

    return;
}

void Stack_literate( T stk, call_t call )
{
    struct elem *u;
    struct elem *t;

    assert( stk ); 

    for( t = stk->head; t; t = u )
    {
        call( t );
        u = t->link;
    }

    return;
}

/*
*/

#include <stdlib.h>
#include <stdio.h>
#include "value.h"
#include "linkedlist.h"

static Value *allocated;
bool isMalloc;

/*
 * A malloc-like function that allocates memory, tracking all allocated
 * pointers in the "active list."  (You can choose your implementation of the
 * active list, but whatever it is, your talloc code should NOT call functions
 * in linkedlist.h; instead, implement any list-like behavior directly here.
 * Otherwise you'll end up with circular dependencies, since you're going to
 * modify the linked list to use talloc instead of malloc.)
 */
void *talloc(size_t size) {
	if(isMalloc != true){
		allocated = malloc(sizeof(Value));
		allocated->type = NULL_TYPE;
		isMalloc = true;
	}

	Value *consVal = malloc(sizeof(Value));
  consVal->type = CONS_TYPE;

	Value *val = malloc(sizeof(Value));
	val->type = PTR_TYPE;
	void *pointer = malloc(size);
	val->p = pointer;

  consVal->c.car = val;
  consVal->c.cdr = allocated;
	allocated = consVal;

	display(allocated);

	return pointer;
}

/*
 * Free all pointers allocated by talloc, as well as whatever memory you
 * malloc'ed to create/update the active list.
 */
void tfree() {
	Value *current = allocated;
	while(!isNull(current)){
		Value *next = current->c.cdr;
		free(current->c.car->p);
	  free(current->c.car);
		Value *old = current;
		free(old);
		current = next;
	}
	free(current);
	isMalloc = false;
}

/*
 * A simple two-line function to stand in the C function "exit", which calls
 * tfree() and then exit().  (You'll use this later to allow a clean exit from
 * your interpreter when you encounter an error: so memory can be automatically
 * cleaned up when exiting.)
 */
void texit(int status) {
	tfree();
	exit(status);
}

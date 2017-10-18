/*
*/

#include <stdlib.h>
#include "value.h"

static Value *allocated;

/* a malloc-like function that keeps track of allocated pointers in a list */
void *talloc(size_t size) {
	if(allocated is null) { /* not sure how to check */
	}
}

/* Free all pointers allocated by talloc */
void tfree() {
	Value *current = allocated;
	while(!isNull(current)){
		Value *next = current->c.cdr;
		free(current->c.car);
		Value *old = current;
		free(old);
		current = next;
	}
	free(current);
}

/* A replacement for exit using tfree*/
void texit(int status) {
	tfree();
	exit();
}

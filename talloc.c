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
/* My first thought for this was to just copy the clean-up code from
   LinkedList? That might work? */
}

/* A replacement for exit using tfree*/
void texit(int status) {
	tfree();
	exit();
}

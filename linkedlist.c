/* LinkedList
Right now, just function declarations with no code so we can build it.
*/

#include <stdbool.h>
#include "value.h"
#include <assert.h>

Value *makeNull() {
}

Value *cons(Value *car, Value *cdr) {
}

void display(Value *list) {
}

Value *car(Value *list) {
	assert((*list).type == CONS_TYPE);
	return (*list).c.car;
}

Value *cdr(Value *list) {
	assert((*list).type == CONS_TYPE);
        return (*list).c.cdr;

}

bool isNull(Value *value) {
}

int length(Value *value) {
}

Value *reverse(Value *list) {
}

void cleanup(Value *list) {
}

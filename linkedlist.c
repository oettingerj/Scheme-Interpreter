/* LinkedList
Right now, just function declarations with no code so we can build it.
*/

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "value.h"
#include <assert.h>

/*
 * Create an empty list (a new Value object of type NULL_TYPE).
 */
Value *makeNull() {
	Value *val = malloc(sizeof(Value));
	val->type = NULL_TYPE;
	return val;
}

/*
 * Create a nonempty list (a new Value object of type CONS_TYPE).
 */
Value *cons(Value *car, Value *cdr) {
	Value *consVal = malloc(sizeof(Value));
  consVal->type = CONS_TYPE;
  consVal->c.car = car;
  consVal->c.cdr = cdr;
  return consVal;
}

/*
 * Test if the given value is a NULL_TYPE value.
 * (Uses assertions to ensure that this is a legitimate operation.)
 */
bool isNull(Value *value) {
	if (value->type == NULL_TYPE){
		return true;
	}
	return false;
}

/*
 * Print a representation of the contents of a linked list.
 */
void display(Value *list) {
	printf("[");
  Value *current = list;
  while(!isNull(current->c.car)){
    switch(current->c.car->type){
      case INT_TYPE:
        printf("%i", current->c.car->i);
        break;
      case DOUBLE_TYPE:
        printf("%f", current->c.car->d);
        break;
      case STR_TYPE:
        printf("%s", current->c.car->s);
				break;
      default:
        printf("");
    }
    printf(", ");
    current = current->c.cdr;
  }
  printf("]");
}

/*
 * Get the car value of a given list.
 * (Uses assertions to ensure that this is a legitimate operation.)
 */
Value *car(Value *list) {
	assert((*list).type == CONS_TYPE);
	return (*list).c.car;
}

/*
 * Get the cdr value of a given list.
 * (Uses assertions to ensure that this is a legitimate operation.)
 */
Value *cdr(Value *list) {
	assert((*list).type == CONS_TYPE);
        return (*list).c.cdr;
}

/*
 * Compute the length of the given list.
 * (Uses assertions to ensure that this is a legitimate operation.)
 */
int length(Value *value) {;
}

/*
 * Create a new linked list whose entries correspond to the given list's
 * entries, but in reverse order.  The resulting list is a deep copy of the
 * original: that is, there should be no shared memory between the original
 * list and the new one.
 *
 * (Uses assertions to ensure that this is a legitimate operation.)
 *
 * FAQ: What if there are nested lists inside that list?
 * ANS: There won't be for this assignment. There will be later, but that will
 *      be after we've got an easier way of managing memory.
 */
Value *reverse(Value *list) {
	assert((*list).type==CONS_TYPE);
	return cons(reverse(cdr(list)), car(list));
}

/*
 * Frees up all memory directly or indirectly referred to by list.
 *
 * (Uses assertions to ensure that this is a legitimate operation.)
 *
 * FAQ: What if there are nested lists inside that list?
 * ANS: There won't be for this assignment. There will be later, but that will
 *      be after we've got an easier way of managing memory.
*/
void cleanup(Value *list) {
	Value *current = list;
	while(!isNull(current->c.car)){
		Value *next = current->c.cdr;
		free(current->c.car);
		free(current->c.cdr);
		Value *old = current;
		current = next;
		free(old);
	}
}

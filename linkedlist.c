/*
C implementation of a linked list
Authors: Josh Oettinger, Nathaniel Lovin, Tenzin Dolphen
*/

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "value.h"
#include <assert.h>
#include "talloc.h"

/*
 * Create an empty list (a new Value object of type NULL_TYPE).
 */
Value *makeNull() {
	Value *val = talloc(sizeof(Value));
	val->type = NULL_TYPE;
	return val;
}

/*
 * Create a nonempty list (a new Value object of type CONS_TYPE).
 */
Value *cons(Value *car, Value *cdr) {
	Value *consVal = talloc(sizeof(Value));
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
  while(!isNull(current)){
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
      case PTR_TYPE:
				printf("%p", current->c.car->p);
				break;
      default:
        printf("");
    }

		if(!isNull(current->c.cdr)){
			printf(", ");
		}

    current = current->c.cdr;
  }
  printf("]\n");
}

/*
 * Get the car value of a given list.
 * (Uses assertions to ensure that this is a legitimate operation.)
 */
Value *car(Value *list){
	assert(list != NULL);
	assert(list->type == CONS_TYPE);
	return list->c.car;
}

/*
 * Get the cdr value of a given list.
 * (Uses assertions to ensure that this is a legitimate operation.)
 */
Value *cdr(Value *list) {
	assert(list != NULL);
	assert(list->type == CONS_TYPE);
  return list->c.cdr;
}

/*
 * Compute the length of the given list.
 * (Uses assertions to ensure that this is a legitimate operation.)
 */
int length(Value *value) {
	int count = 0;
	if(isNull(value)){
		return 0;
	}
	assert(value->type == CONS_TYPE);
	Value *cur = value;
	while(!isNull(cur)){
		count++;
		cur = cur->c.cdr;
	}
	return count;
}

/*
 * Create a new linked list whose entries correspond to the given list's
 * entries, but in reverse order.  The resulting list is not a deep copy of the
 * original: that is, there will be shared memory between the original
 * list and the new one.
 *
 * (Uses assertions to ensure that this is a legitimate operation.)
 *
 * FAQ: What if there are nested lists inside that list?
 * ANS: There won't be for this assignment. There will be later, but that will
 *      be after we've got an easier way of managing memory.
 */
Value *reverse(Value *list) {
	assert(list != NULL);
	if(list->type == NULL_TYPE){
		return makeNull();
	} else{
		assert(list->type == CONS_TYPE);
		Value *prev = makeNull();
		Value *curr = list;
		Value *reversed;
		while(!isNull(curr)){
			Value *val = talloc(sizeof(Value));
			val->type = curr->type;
			val->c.car = curr->c.car;
			val->c.cdr = prev;
			prev = val;
			curr = curr->c.cdr;
			reversed = val;
		}
		return reversed;
	}
}

#include <stdio.h>
#include <stdlib.h>
#include "value.h"
#include "linkedlist.h"
#include "talloc.c"

int main() {
   Value *val1 = talloc(sizeof(Value));
   val1->type = INT_TYPE;
   val1->i = 12;

   Value *val2 = talloc(sizeof(Value));
   val2->type = DOUBLE_TYPE;
   val2->d = 4.3;

   Value *head = makeNull();
   head = cons(val1, head);
   head = cons(val2, head);

   display(head);
   printf("Length = %i\n", length(head));
   printf("Empty? %i\n", isNull(head));
   texit(1);
}

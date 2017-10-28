/*Nathaniel Lovin, Josh 
*/

#include <string.h>
#include "value.h"
#include "linkedlist.h"
#include "talloc.h"

struct Frame {
   Value *bindings;
   struct Frame *parent;
};
typedef struct Frame Frame;

void interpret(Value *tree);
Value *eval(Value *expr, Frame *frame);

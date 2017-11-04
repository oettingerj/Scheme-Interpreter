
#include <string.h>
#include "value.h"
#include "linkedlist.h"
#include "talloc.h"

struct Frame {
   Value *bindings;
   struct Frame *parent;
   int hasParent;
};
typedef struct Frame Frame;

void interpret(Value *tree);
Value *eval(Value *expr, Frame *frame);

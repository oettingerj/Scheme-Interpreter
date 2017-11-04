
#include <string.h>
#include "value.h"
#include "linkedlist.h"
#include "talloc.h"

void interpret(Value *tree);
Value *eval(Value *expr, Frame *frame);

#include "value.h"
#include "linkedlist.h"
#include "talloc.h"
#include "tokenizer.h"
#include "parser.h"
#include "interpreter.h"

int main(void) {
   Value *list = tokenize();
   Value *tree = parse(list);
   interpret(tree);
   tfree();
   return 0;
}

#include "value.h"
#include "linkedlist.h"
#include "talloc.h"
#include "tokenizer.h"
#include "parser.h"
#include "interpreter.h"

int main(int argc, char *argv[]) {
    Value *list = tokenize();
    Value *tree = parse(list);
    interpret(tree);
    tfree();
    return 0;
}

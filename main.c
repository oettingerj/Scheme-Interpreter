#include "value.h"
#include "linkedlist.h"
#include "talloc.h"
#include "tokenizer.h"
#include "parser.h"
#include "interpreter.h"

int main(int argc, char *argv[]) {
    Frame *parent = talloc(sizeof(Frame));
    parent->bindings = makeNull();
    parent->hasParent = 0;

    /*for(int i = 1; i < argc; i++){
        load(argv[i], parent);
    }
    freopen("/dev/stdin/", "r", stdin);*/

    Value *list = tokenize();
    Value *tree = parse(list);
    interpret(tree, parent);
    tfree();
    return 0;
}

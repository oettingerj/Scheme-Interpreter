#include "value.h"
#include "linkedlist.h"
#include "talloc.h"
#include "tokenizer.h"
#include "parser.h"
#include "interpreter.h"

int main(int argc, char *argv[]) {
    /*Value *list = makeNull();
    for(int x = 1; x < argc; x++){
    Value *load = talloc(sizeof(Value));
	load->type = SYMBOL_TYPE;
	load->s = "load";
	Value *file = talloc(sizeof(Value));
	file->type = STR_TYPE;
        file->s = argv[x];
	Value *expr = makeNull();
	expr = cons(load, expr);
	expr = cons(file, expr);
	expr = reverse(expr);
	tree = cons(expr, tree);
	list = cons(tokenize(argv[x]),list);
    }*/
    
   Value *list = tokenize();
   Value *tree = parse(list);
   interpret(tree);
   tfree();
   return 0;
}

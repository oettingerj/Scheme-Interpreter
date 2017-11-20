#include "value.h"
#include "linkedlist.h"
#include "talloc.h"
#include "tokenizer.h"
#include "parser.h"
#include "interpreter.h"

int main(int argc, char *argv[]) {
    printf("%i",argc);
    for(int x = 0; x < argc; x++){
        printf("%s", argv[x]);
        char* fileload = "(load ";
        strcat(fileload, argv[x]);
        strcat(fileload, ")");
        printf("%s", fileload);
    }
    
   Value *list = tokenize();
   Value *tree = parse(list);
   interpret(tree);
   tfree();
   return 0;
}

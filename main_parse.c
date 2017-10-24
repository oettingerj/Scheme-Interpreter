/*This is all on Jed
*/

#include "value.h"
#include "talloc.h"
#include "linkedlist.h" /*Not sure if we need this*/
#include "tokenizer.h"
#include "parser.h"

int main(void) {
	Value *list = tokenize();
	Value *tree = parse(list);
	printTree(tree);
	printf("\n");
	tfree();
	return 0;
}
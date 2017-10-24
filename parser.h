/*Nathaniel Lovin, Josh Oettinger, Tenzin Dolphen
*/

#include <stdio.h>
#include "value.h"
#include "talloc.h"
#include "linkedlist.h"
#include "tokenizer.h"

/*
*/
Value *parse(Value *tokens);

/*
*/
void printTree(Value *tree);

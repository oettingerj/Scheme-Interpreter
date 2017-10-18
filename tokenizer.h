/*Nathaniel Lovin, Josh Oettinger, Tenzin Dolphen
Header file for tokenizer
*/

#include <stdin.h>
#include "value.h"
#include "talloc.h"
#include "linkedlist.h"

/*Reads a line of input and returns a linkedlist of
all tokens found.
*/
Value *tokenize();

/*Takes a list of tokens, and prints them
and their types.
*/
void displayTokens(Value *list);
